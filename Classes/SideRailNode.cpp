//
//  SideRailNode.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#include "SideRailNode.h"
#include "Colors.h"
#include "Physics.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

namespace bg = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> GeoPoint;
typedef bg::model::box<GeoPoint> GeoBox;
typedef bg::model::polygon<GeoPoint> GeoPolygon;

USING_NS_CC;

#define DEBUG_DRAW 0

namespace flik
{
    struct BoxDesc
    {
        SideRailBox type;
        Vec2 anchor;
        Color3B startColor;
        Color3B endColor;
        Vec2 direction;
    };
    
    static const auto kBoxDimens = Size(80, 190);
    static const int kRailSize = 10;
    
    static const BoxDesc RedBoxDesc = { RedBox, Vec2(0, 1), kRedStartColor, kRedEndColor, Vec2(0.5, 0.5) };
    static const BoxDesc BlueBoxDesc = { BlueBox, Vec2(1, 1), kBlueStartColor, kBlueEndColor, Vec2(-0.5, 0.5) };
    static const BoxDesc GreenBoxDesc = { GreenBox, Vec2(0, 0), kGreenStartColor, kGreenEndColor, Vec2(0.5, -0.5) };
    static const BoxDesc YellowBoxDesc = { YellowBox, Vec2(1, 0), kYellowStartColor, kYellowEndColor, Vec2(-0.5, -0.5) };
    
    static const BoxDesc Boxes[] = { RedBoxDesc, BlueBoxDesc, GreenBoxDesc, YellowBoxDesc };
    static const int kNumBoxes = 4;
    
    bool SideRailNode::init()
    {
        if (!Node::init())
        {
            return false;
        }
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        //auto contentScale = Director::getInstance()->getContentScaleFactor();
        
        auto outerBox = LayerColor::create(Color4B(kBlackColor), visibleSize.width, visibleSize.height);
        outerBox->setPosition(Vec2(0, 0));
        outerBox->setAnchorPoint(Vec2(0, 0));
        addChild(outerBox);
        mOuterBox = outerBox;
        
        for (int i = 0; i < kNumBoxes; i++) {
            auto& box = Boxes[i];
            
            auto layer = LayerGradient::create(Color4B(box.startColor), Color4B(box.endColor), box.direction);
            layer->setContentSize(kBoxDimens);
            layer->setPosition(Vec2(box.anchor.x * visibleSize.width, box.anchor.y * visibleSize.height));
            layer->setAnchorPoint(box.anchor);
            layer->ignoreAnchorPointForPosition(false);
            
            addChild(layer);
            
            mBoxes[box.type] = layer;
        }
        
        auto innerBox = LayerColor::create(Color4B(kBlackColor), visibleSize.width - (kRailSize * 2), visibleSize.height - (kRailSize * 2));
        innerBox->setPosition(kRailSize, kRailSize);
        innerBox->setAnchorPoint(Vec2(0, 0));
        addChild(innerBox);
        mInnerBox = innerBox;
        
        calculateRails();
        
        return true;
    }
    
    void SideRailNode::calculateRails()
    {
        auto red = mBoxes[RedBox];
        auto blue = mBoxes[BlueBox];
        auto green = mBoxes[GreenBox];
        auto yellow = mBoxes[YellowBox];
        
        auto redBounds = red->getBoundingBox();
        auto blueBounds = blue->getBoundingBox();
        auto greenBounds = green->getBoundingBox();
        auto yellowBounds = yellow->getBoundingBox();
        
        double left, right, top, bottom;
        
        float buffer = 100;
        
        auto getBoxGeo = [](LayerColor* box, GeoPolygon& output) {
            auto bounds = box->getBoundingBox();
            auto boxGeo = GeoBox(GeoPoint(bounds.getMinX(), bounds.getMinY()), GeoPoint(bounds.getMaxX(), bounds.getMaxY()));
            bg::convert(boxGeo, output);
        };
        
        auto createRailNode = [&](double left, double bottom, double right, double top, int categoryMask, int contactMask, int collisionMask, Color4B debugColor = Color4B(0, 0, 0, 255)) {
            auto railNode = Node::create();
            railNode->setPosition(Vec2(left, bottom));
            railNode->setContentSize(Size(right - left, top - bottom));
            railNode->setAnchorPoint(Vec2(0, 0));
            railNode->ignoreAnchorPointForPosition(false);
           
            auto physicsBody = PhysicsBody::createBox(railNode->getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
            physicsBody->setDynamic(false);
            physicsBody->setCategoryBitmask(categoryMask);
            physicsBody->setContactTestBitmask(contactMask);
            physicsBody->setCollisionBitmask(collisionMask);
            railNode->setPhysicsBody(physicsBody);
            
#if DEBUG_DRAW
            auto debugLayer = LayerColor::create(debugColor, railNode->getContentSize().width, railNode->getContentSize().height);
            debugLayer->setPosition(0, 0);
            debugLayer->setAnchorPoint(Vec2(0, 0));
            debugLayer->ignoreAnchorPointForPosition(false);
            railNode->addChild(debugLayer);
#endif
            
            addChild(railNode);
        };
        
        // Top Rail
        {
            left = redBounds.getMaxX();
            right = blueBounds.getMinX();
            top = redBounds.getMaxY() + buffer;
            bottom = top - kRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Right Rail
        {
            right = blueBounds.getMaxX() + buffer;
            left = right - kRailSize - buffer;
            top = blueBounds.getMinY();
            bottom = yellowBounds.getMaxY();
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Bottom Rail
        {
            left = greenBounds.getMaxX();
            right = yellowBounds.getMinX();
            bottom = greenBounds.getMinY() - buffer;
            top = bottom + kRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Left Rail
        {
            left = redBounds.getMinX() - buffer;
            right = left + kRailSize + buffer;
            top = redBounds.getMinY();
            bottom = greenBounds.getMaxY();
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        GeoPolygon innerBoxGeo;
        getBoxGeo(mInnerBox, innerBoxGeo);
        
        // Red Box
        {

            left = redBounds.getMinX() - buffer;
            right = left + kRailSize + buffer;
            top = redBounds.getMaxY();
            bottom = redBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::RedRail, collision::AllButRedPiece, collision::AllButRedPiece, Color4B(255, 0, 0, 255));
            
            left = redBounds.getMinX();
            right = redBounds.getMaxX();
            top = redBounds.getMaxY() + buffer;
            bottom = top - kRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::RedRail, collision::AllButRedPiece, collision::AllButRedPiece, Color4B(255, 0, 0, 255));
        }
        
        // Blue Box
        {
            right = blueBounds.getMaxX() + buffer;
            left = right - kRailSize - buffer;
            top = blueBounds.getMaxY();
            bottom = blueBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::BlueRail, collision::AllButBluePiece, collision::AllButBluePiece, Color4B(0, 0, 255, 255));
            
            left = blueBounds.getMinX();
            right = blueBounds.getMaxX();
            top = blueBounds.getMaxY() + buffer;
            bottom = top - kRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::BlueRail, collision::AllButBluePiece, collision::AllButBluePiece, Color4B(0, 0, 255, 255));
        }
        
        // Green Box
        {
            left = greenBounds.getMinX() - buffer;
            right = left + kRailSize + buffer;
            top = greenBounds.getMaxY();
            bottom = greenBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::GreenRail, collision::AllButGreenPiece, collision::AllButGreenPiece, Color4B(0, 255, 0, 255));
            
            left = greenBounds.getMinX();
            right = greenBounds.getMaxX();
            bottom = greenBounds.getMinY() - buffer;
            top = bottom + kRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::GreenRail, collision::AllButGreenPiece, collision::AllButGreenPiece, Color4B(0, 255, 0, 255));
        }
        
        // Yellow Box
        {
            right = yellowBounds.getMaxX() + buffer;
            left = right - kRailSize - buffer;
            top = yellowBounds.getMaxY();
            bottom = yellowBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::YellowRail, collision::AllButYellowPiece, collision::AllButYellowPiece, Color4B(255, 255, 0, 255));
            
            left = yellowBounds.getMinX();
            right = yellowBounds.getMaxX();
            bottom = yellowBounds.getMinY() - buffer;
            top = bottom + kRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::YellowRail, collision::AllButYellowPiece, collision::AllButYellowPiece, Color4B(255, 255, 0, 255));
        }
    }
}
//
//  SideRailNode.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#include "SideRailNode.h"
#include "Styles.h"
#include "Physics.h"
#include "Literals.h"
#include "Util.h"

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
        Color3B color;
        Vec2 direction;
    };
    
    static const BoxDesc RedBoxDesc = { RedBox, Vec2(0, 1), kRedColor, Vec2(0.5, 0.5) };
    static const BoxDesc BlueBoxDesc = { BlueBox, Vec2(1, 1), kBlueColor, Vec2(-0.5, 0.5) };
    static const BoxDesc PinkBoxDesc = { PinkBox, Vec2(0, 0), kPinkColor, Vec2(0.5, -0.5) };
    static const BoxDesc YellowBoxDesc = { YellowBox, Vec2(1, 0), kYellowColor, Vec2(-0.5, -0.5) };
    
    static const BoxDesc Boxes[] = { RedBoxDesc, BlueBoxDesc, PinkBoxDesc, YellowBoxDesc };
    static const int kNumBoxes = 4;
    
    SideRailNode* SideRailNode::create(const Size& gameBoardSize)
    {
        return createWithParams<SideRailNode>(gameBoardSize);
    }
    
    bool SideRailNode::init(const Size& gameBoardSize)
    {
        if (!Node::init())
        {
            return false;
        }
        
        mBoxDimens = Size(100.0_dp, 100.0_dp);
        mRailSize = 10.0_dp;
    
        //auto contentScale = Director::getInstance()->getContentScaleFactor();
        
        auto outerBox = LayerColor::create(Color4B(kBlackColor), gameBoardSize.width, gameBoardSize.height);
        outerBox->setPosition(Vec2(0, 0));
        outerBox->setAnchorPoint(Vec2(0, 0));
        addChild(outerBox);
        mOuterBox = outerBox;
        
        for (int i = 0; i < kNumBoxes; i++) {
            auto& box = Boxes[i];
            
            auto layer = LayerColor::create(Color4B(box.color));
            layer->setContentSize(mBoxDimens);
            layer->setPosition(Vec2(box.anchor.x * gameBoardSize.width, box.anchor.y * gameBoardSize.height));
            layer->setAnchorPoint(box.anchor);
            layer->ignoreAnchorPointForPosition(false);
            
            addChild(layer);
            
            mBoxes[box.type] = layer;
        }
        
        auto innerBox = LayerColor::create(Color4B(kBlackColor), gameBoardSize.width - (mRailSize * 2), gameBoardSize.height - (mRailSize * 2));
        innerBox->setPosition(mRailSize, mRailSize);
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
        auto pink = mBoxes[PinkBox];
        auto yellow = mBoxes[YellowBox];
        
        auto redBounds = red->getBoundingBox();
        auto blueBounds = blue->getBoundingBox();
        auto pinkBounds = pink->getBoundingBox();
        auto yellowBounds = yellow->getBoundingBox();
        
        double left, right, top, bottom;
        
        float buffer = 100.0_dp;
        
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
            bottom = top - mRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Right Rail
        {
            right = blueBounds.getMaxX() + buffer;
            left = right - mRailSize - buffer;
            top = blueBounds.getMinY();
            bottom = yellowBounds.getMaxY();
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Bottom Rail
        {
            left = pinkBounds.getMaxX();
            right = yellowBounds.getMinX();
            bottom = pinkBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Left Rail
        {
            left = redBounds.getMinX() - buffer;
            right = left + mRailSize + buffer;
            top = redBounds.getMinY();
            bottom = pinkBounds.getMaxY();
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        GeoPolygon innerBoxGeo;
        getBoxGeo(mInnerBox, innerBoxGeo);
        
        // Red Box
        {

            left = redBounds.getMinX() - buffer;
            right = left + mRailSize + buffer;
            top = redBounds.getMaxY();
            bottom = redBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::RedRail, collision::AllButRedPiece, collision::AllButRedPiece, Color4B(255, 0, 0, 255));
            
            left = redBounds.getMinX();
            right = redBounds.getMaxX();
            top = redBounds.getMaxY() + buffer;
            bottom = top - mRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::RedRail, collision::AllButRedPiece, collision::AllButRedPiece, Color4B(255, 0, 0, 255));
        }
        
        // Blue Box
        {
            right = blueBounds.getMaxX() + buffer;
            left = right - mRailSize - buffer;
            top = blueBounds.getMaxY();
            bottom = blueBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::BlueRail, collision::AllButBluePiece, collision::AllButBluePiece, Color4B(0, 0, 255, 255));
            
            left = blueBounds.getMinX();
            right = blueBounds.getMaxX();
            top = blueBounds.getMaxY() + buffer;
            bottom = top - mRailSize - buffer;
            
            createRailNode(left, bottom, right, top, collision::BlueRail, collision::AllButBluePiece, collision::AllButBluePiece, Color4B(0, 0, 255, 255));
        }
        
        // Pink Box
        {
            left = pinkBounds.getMinX() - buffer;
            right = left + mRailSize + buffer;
            top = pinkBounds.getMaxY();
            bottom = pinkBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::PinkRail, collision::AllButPinkPiece, collision::AllButPinkPiece, Color4B(0, 255, 0, 255));
            
            left = pinkBounds.getMinX();
            right = pinkBounds.getMaxX();
            bottom = pinkBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::PinkRail, collision::AllButPinkPiece, collision::AllButPinkPiece, Color4B(0, 255, 0, 255));
        }
        
        // Yellow Box
        {
            right = yellowBounds.getMaxX() + buffer;
            left = right - mRailSize - buffer;
            top = yellowBounds.getMaxY();
            bottom = yellowBounds.getMinY();
            
            createRailNode(left, bottom, right, top, collision::YellowRail, collision::AllButYellowPiece, collision::AllButYellowPiece, Color4B(255, 255, 0, 255));
            
            left = yellowBounds.getMinX();
            right = yellowBounds.getMaxX();
            bottom = yellowBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::YellowRail, collision::AllButYellowPiece, collision::AllButYellowPiece, Color4B(255, 255, 0, 255));
        }
    }
}
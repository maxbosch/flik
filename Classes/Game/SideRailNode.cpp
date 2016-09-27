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
#include "GoalLayer.h"
#include "MainGameScene.h"
#include "PhysicsNode.h"

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
        GamePieceType type;
        Vec2 anchor;
        Color3B color;
        Vec2 direction;
    };
    
    static const BoxDesc RedBoxDesc = { GamePieceType::RedPiece, Vec2(0, 1), kRedColor, Vec2(1, 1) };
    static const BoxDesc BlueBoxDesc = { GamePieceType::BluePiece, Vec2(1, 1), kBlueColor, Vec2(0, 1) };
    static const BoxDesc GreenBoxDesc = { GamePieceType::GreenPiece, Vec2(0, 0), kGreenColor, Vec2(1, 0) };
    static const BoxDesc YellowBoxDesc = { GamePieceType::YellowPiece, Vec2(1, 0), kYellowColor, Vec2(0, 0) };
    
    static const BoxDesc Boxes[] = { RedBoxDesc, BlueBoxDesc, GreenBoxDesc, YellowBoxDesc };
    static const int kNumBoxes = 4;
    
    SideRailNode* SideRailNode::create(MainGameScene* mainGameScene, const Size& gameBoardSize)
    {
        return createWithParams<SideRailNode>(mainGameScene, gameBoardSize);
    }
    
    bool SideRailNode::init(MainGameScene* mainGameScene, const Size& gameBoardSize)
    {
        if (!Node::init())
        {
            return false;
        }
        
        mBoxDimens = Size(110.0_dp, 110.0_dp);
        mRailSize = 10.0_dp;
    
        //auto contentScale = Director::getInstance()->getContentScaleFactor();
        
        auto outerBox = LayerColor::create(Color4B(kBlackColor), gameBoardSize.width, gameBoardSize.height);
        outerBox->setPosition(Vec2(0, 0));
        outerBox->setAnchorPoint(Vec2(0, 0));
        addChild(outerBox);
        mOuterBox = outerBox;
        
        for (int i = 0; i < kNumBoxes; i++) {
            auto& box = Boxes[i];
            
            auto layer = GoalLayer::create(box.type, Color4B(box.color));
            layer->setContentSize(mBoxDimens);
            layer->setPosition(Vec2(box.anchor.x * gameBoardSize.width, box.anchor.y * gameBoardSize.height));
            layer->setAnchorPoint(box.anchor);
            layer->setDirection(box.direction);
            layer->ignoreAnchorPointForPosition(false);
            
            addChild(layer);
            
            mBoxes[box.type] = layer;
        }
        
        auto innerBox = LayerColor::create(Color4B(kBlackColor), gameBoardSize.width - (mRailSize * 2), gameBoardSize.height - (mRailSize * 2));
        innerBox->setPosition(mRailSize, mRailSize);
        innerBox->setAnchorPoint(Vec2(0, 0));
        addChild(innerBox);
        mInnerBox = innerBox;
        
        calculateRails(mainGameScene);
        
        return true;
    }
    
    void SideRailNode::calculateRails(MainGameScene* mainGameScene)
    {
        auto red = mBoxes[GamePieceType::RedPiece];
        auto blue = mBoxes[GamePieceType::BluePiece];
        auto green = mBoxes[GamePieceType::GreenPiece];
        auto yellow = mBoxes[GamePieceType::YellowPiece];
        
        auto redBounds = red->getBoundingBox();
        auto blueBounds = blue->getBoundingBox();
        auto greenBounds = green->getBoundingBox();
        auto yellowBounds = yellow->getBoundingBox();
        
        double left, right, top, bottom;
        
        float buffer = 0.0_dp;
        auto physicsWorld = mainGameScene->getPhysicsWorldBox2D();
        
        auto getBoxGeo = [](LayerColor* box, GeoPolygon& output) {
            auto bounds = box->getBoundingBox();
            auto boxGeo = GeoBox(GeoPoint(bounds.getMinX(), bounds.getMinY()), GeoPoint(bounds.getMaxX(), bounds.getMaxY()));
            bg::convert(boxGeo, output);
        };
        
        auto createRailNode = [&](double left, double bottom, double right, double top, int categoryMask, int contactMask, int collisionMask, Color4B debugColor = Color4B(0, 0, 0, 255)) {
            auto railNode = PhysicsNode::create();
            railNode->setPosition(Vec2(left, bottom));
            railNode->setContentSize(Size(right - left, top - bottom));
            railNode->setAnchorPoint(Vec2(0, 0));
            railNode->ignoreAnchorPointForPosition(false);
            addChild(railNode);
           
//            auto physicsBody = PhysicsBody::createBox(railNode->getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
//            physicsBody->setDynamic(false);
//            physicsBody->setCategoryBitmask(categoryMask);
//            physicsBody->setContactTestBitmask(contactMask);
//            physicsBody->setCollisionBitmask(collisionMask);
//            railNode->setPhysicsBody(physicsBody);
            
            b2BodyDef bodyDef;
            bodyDef.type = b2BodyType::b2_staticBody;
            bodyDef.fixedRotation = true;
            railNode->createPhysicsBody(physicsWorld, &bodyDef);
            railNode->addBoxFixture(railNode->getContentSize(), 1.0, 0.0, 0.5, categoryMask, collisionMask);
            
            
#if DEBUG_DRAW
            auto debugLayer = LayerColor::create(debugColor, railNode->getContentSize().width, railNode->getContentSize().height);
            debugLayer->setPosition(0, 0);
            debugLayer->setAnchorPoint(Vec2(0, 0));
            debugLayer->ignoreAnchorPointForPosition(false);
            railNode->addChild(debugLayer);
#endif
            
            
            
            return railNode;
        };
        
        // Top Rail
        {
            left = redBounds.getMaxX();
            right = blueBounds.getMinX();
            top = redBounds.getMaxY();
            bottom = top - mRailSize;
            
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
            left = greenBounds.getMaxX();
            right = yellowBounds.getMinX();
            bottom = greenBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            createRailNode(left, bottom, right, top, collision::BlackRail, collision::All, collision::All);
        }
        
        // Left Rail
        {
            left = redBounds.getMinX() - buffer;
            right = left + mRailSize + buffer;
            top = redBounds.getMinY();
            bottom = greenBounds.getMaxY();
            
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
            
            int categoryMask = collision::RedRail;
            int contactMask = collision::AllButRedPiece;
            int collisionMask = collision::AllButRedPiece;
            
            auto layer = mBoxes[GamePieceType::RedPiece];
            layer->setCollisionFlags(categoryMask, contactMask, collisionMask);
            
            auto node1 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(255, 0, 0, 255));
            layer->addCollisionNode(node1);
            
            left = redBounds.getMinX();
            right = redBounds.getMaxX();
            top = redBounds.getMaxY() + buffer;
            bottom = top - mRailSize - buffer;
            
            auto node2 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(255, 0, 0, 255));
            layer->addCollisionNode(node2);
        }
        
        // Blue Box
        {
            right = blueBounds.getMaxX() + buffer;
            left = right - mRailSize - buffer;
            top = blueBounds.getMaxY();
            bottom = blueBounds.getMinY();
            
            int categoryMask = collision::BlueRail;
            int contactMask = collision::AllButBluePiece;
            int collisionMask = collision::AllButBluePiece;
            
            auto layer = mBoxes[GamePieceType::BluePiece];
            layer->setCollisionFlags(categoryMask, contactMask, collisionMask);
            
            auto node1 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(0, 0, 255, 255));
            layer->addCollisionNode(node1);
            
            left = blueBounds.getMinX();
            right = blueBounds.getMaxX();
            top = blueBounds.getMaxY() + buffer;
            bottom = top - mRailSize - buffer;
            
            auto node2 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(0, 0, 255, 255));
            layer->addCollisionNode(node2);
        }
        
        // Green Box
        {
            left = greenBounds.getMinX() - buffer;
            right = left + mRailSize + buffer;
            top = greenBounds.getMaxY();
            bottom = greenBounds.getMinY();
            
            int categoryMask = collision::GreenRail;
            int contactMask = collision::AllButGreenPiece;
            int collisionMask = collision::AllButGreenPiece;
            
            auto layer = mBoxes[GamePieceType::GreenPiece];
            layer->setCollisionFlags(categoryMask, contactMask, collisionMask);
            
            auto node1 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(0, 255, 0, 255));
            layer->addCollisionNode(node1);
            
            left = greenBounds.getMinX();
            right = greenBounds.getMaxX();
            bottom = greenBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            auto node2 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(0, 255, 0, 255));
            layer->addCollisionNode(node2);
        }
        
        // Yellow Box
        {
            right = yellowBounds.getMaxX() + buffer;
            left = right - mRailSize - buffer;
            top = yellowBounds.getMaxY();
            bottom = yellowBounds.getMinY();
            
            int categoryMask = collision::YellowRail;
            int contactMask = collision::AllButYellowPiece;
            int collisionMask = collision::AllButYellowPiece;
            
            auto layer = mBoxes[GamePieceType::YellowPiece];
            layer->setCollisionFlags(categoryMask, contactMask, collisionMask);
            
            auto node1 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(255, 255, 0, 255));
            layer->addCollisionNode(node1);
            
            left = yellowBounds.getMinX();
            right = yellowBounds.getMaxX();
            bottom = yellowBounds.getMinY() - buffer;
            top = bottom + mRailSize + buffer;
            
            auto node2 = createRailNode(left, bottom, right, top, categoryMask, contactMask, collisionMask, Color4B(255, 255, 0, 255));
            layer->addCollisionNode(node2);
        }
    }
}

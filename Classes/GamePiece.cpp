//
//  GamePiece.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#include "GamePiece.h"
#include "SideRailNode.h"
#include "MainGameScene.h"
#include "Physics.h"
#include "Player.h"
#include "Events.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    static std::string PieceSprites[] = {
        "piece_red.png",
        "piece_blue.png",
        "piece_green.png",
        "piece_yellow.png"
    };
    
    static const float kVelocityDamping = 0.7;
    
    static const float kDeceleration = 0.5;
    
    static const float kVelocityEpsilon = 20.0f;
    
    GamePiece* GamePiece::create(const cocos2d::Vec2& position)
    {
        auto obj = create();
        if (obj) {
            obj->setPosition(position);
        }
        return obj;
    }
    
    bool GamePiece::init()
    {
        if (!Node::init())
        {
            return false;
        }
        
        //setGlobalZOrder(0);
        setContentSize(Size(50.0_dp, 50.0_dp));
        setAnchorPoint(Vec2(0.5, 0.5));
        ignoreAnchorPointForPosition(false);
        
        auto randomId = cocos2d::random(0, 3);
        auto sprite = Sprite::create(PieceSprites[randomId]);
        sprite->setScale(0.5, 0.5);
        sprite->setAnchorPoint(Vec2(0, 0));
        //sprite->setGlobalZOrder(0);
        
        addChild(sprite);
        
        auto touchListener = EventListenerTouchOneByOne::create();
        
        touchListener->onTouchBegan = CC_CALLBACK_2(GamePiece::onTouchBegan, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(GamePiece::onTouchEnded, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(GamePiece::onTouchMoved, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(GamePiece::onTouchCancelled, this);
        
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        auto physicsBody = PhysicsBody::createBox(getContentSize(), PhysicsMaterial(1.0f, 0.5f, 0.0f));
        physicsBody->setGravityEnable(false);
        physicsBody->setRotationEnable(false);

        physicsBody->setCollisionBitmask(collision::PieceCollisionMasks[randomId]);
        physicsBody->setContactTestBitmask(collision::PieceContactMasks[randomId]);
        physicsBody->setCategoryBitmask(collision::PieceCategoryMasks[randomId]);
        setPhysicsBody(physicsBody);
        mPhysicsBody = physicsBody;
        
        this->scheduleUpdate();

        return true;
    }
    
    void GamePiece::update(float delta)
    {
        Node::update(delta);
        
        auto velocity = mPhysicsBody->getVelocity();
        if (fabsf(velocity.x) < kVelocityEpsilon && fabsf(velocity.y) < kVelocityEpsilon) {
            mPhysicsBody->setVelocity(Vec2());
        } else {
            auto deltaVelocity = velocity * (delta * kDeceleration);
            mPhysicsBody->setVelocity(velocity - deltaVelocity);
        }
        
        auto visibleBounds = Rect(Vec2(), Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
        auto localBounds = getBoundingBox();
        if (!visibleBounds.intersectsRect(localBounds)) {
            EventCustom eventObj(kPieceRemovedEvent);
            eventObj.setUserData(this);
            
            getEventDispatcher()->dispatchEvent(&eventObj);
            
            removeFromParent();
        }
    }
    
    bool GamePiece::onContactBegin(PhysicsContact& contact)
    {
        return true;
    }
    
    void GamePiece::onPostContactSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    {
        if (contact.getShapeA() == mPhysicsBody->getShape(0) ||
            contact.getShapeB() == mPhysicsBody->getShape(0)) {
            mPhysicsBody->setVelocity(Vec2(0, 0));
        }
    }
    
    bool GamePiece::onTouchBegan(Touch *touch, Event *unused_event)
    {
        auto bb = getBoundingBox();
        double padding = 20.0_dp;
        bb.setRect(bb.origin.x - padding, bb.origin.y - padding, bb.size.width + (padding * 2), bb.size.height + (padding * 2));
        mPressed = bb.containsPoint(touch->getLocation());
        
        mVelocityTracker.Reset();
        mVelocityTracker.AddPoint(touch->getLocation());
        getPhysicsBody()->setVelocity(Vec2());
    
        return true;
    }
    
    void GamePiece::onTouchMoved(Touch *touch, Event *unused_event)
    {
        if (mPressed) {
            mVelocityTracker.AddPoint(touch->getLocation());
            setPosition(getPosition() + touch->getDelta());
            mGameScene->constrainPieceToGameBounds(this);
        }
    }
    
    void GamePiece::onTouchEnded(Touch *touch, Event *unused_event)
    {
        if (mPressed) {
            mVelocityTracker.AddPoint(touch->getLocation());
            getPhysicsBody()->setVelocity(mVelocityTracker.GetVelocity() * kVelocityDamping);
        }
        
        mPressed = false;
    }
    void GamePiece::onTouchCancelled(Touch *touch, Event *unused_event)
    {
        mPressed = false;
    }
}
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
#include "SpawnRandomizer.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    static std::string PieceSprites[] = {
        "piece_red.png",
        "piece_blue.png",
        "piece_pink.png",
        "piece_yellow.png"
    };
    
    static const float kDeceleration = 0.7;
    
    static const float kVelocityEpsilon = 20.0f * kInversePixelsToMeters;
    
    GamePiece* GamePiece::create(const cocos2d::Vec2& position, GamePieceType pieceType)
    {
        return createWithParams<GamePiece>(position, pieceType);
    }
    
    bool GamePiece::init(const Vec2& position, GamePieceType pieceType)
    {
        if (!Node::init())
        {
            return false;
        }
        
        //setGlobalZOrder(0);
        setContentSize(Size(50.0_dp, 50.0_dp));
        setPosition(position);
        setAnchorPoint(Vec2(0.5, 0.5));
        ignoreAnchorPointForPosition(false);
        
        if (pieceType == GamePieceType::RandomPiece) {
            pieceType = (GamePieceType) SpawnRandomizer::getInstance()->getRandomId();
        }
        
        auto sprite = Sprite::create(PieceSprites[(int)pieceType]);
        sprite->setAnchorPoint(Vec2(0, 0));
        mSprite = sprite;

        addChild(sprite);

        mType = (int) pieceType;
        mCategoryMask = collision::PieceCategoryMasks[mType];
        mCollisionMask = collision::PieceCollisionMasks[mType];
        
        this->scheduleUpdate();
        

        return true;
    }
    
    void GamePiece::setGameScene(MainGameScene* gameScene)
    {
        mGameScene = gameScene;
        
        
        b2BodyDef bodyDef;
        bodyDef.type = b2BodyType::b2_dynamicBody;
        bodyDef.fixedRotation = true;
        bodyDef.awake  = true;
        bodyDef.bullet = true;
        
        createPhysicsBody(gameScene->getPhysicsWorldBox2D(), &bodyDef);
        addBoxFixture(getContentSize(), 1.0f, 0.0f, 0.3f, mCategoryMask, mCollisionMask);
    }
    
    void GamePiece::update(float delta)
    {
        PhysicsNode::update(delta);
        auto physicsBody = getPhysicsBodyBox2D();
        
        auto velocity = physicsBody->GetLinearVelocity();
        if (isDecelerating()) {
            if (fabsf(velocity.x) < kVelocityEpsilon && fabsf(velocity.y) < kVelocityEpsilon) {
                physicsBody->SetLinearVelocity(b2Vec2(0, 0));
                setDecelerating(false);
            } else {
                auto deltaVelocity = ((delta * kDeceleration) * velocity);
                physicsBody->SetLinearVelocity(velocity - deltaVelocity);
            }
        }
    }
    
//    bool GamePiece::onContactBegin(PhysicsContact& contact)
//    {
//        return true;
//    }
//    
//    void GamePiece::onPostContactSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
//    {
//        if (contact.getShapeA() == mPhysicsBody->getShape(0) ||
//            contact.getShapeB() == mPhysicsBody->getShape(0)) {
//            mPhysicsBody->setVelocity(Vec2(0, 0));
//        }
//    }
    
    Rect GamePiece::getTouchBoundingBox()
    {
        auto bb = getBoundingBox();
        double padding = 20.0_dp;
        bb.setRect(bb.origin.x - padding, (bb.origin.y - padding) + getParent()->getPositionY(), bb.size.width + (padding * 2), bb.size.height + (padding * 2));
        return bb;
    }
    
    void GamePiece::setOpacity(float opacity)
    {
        Node::setOpacity(opacity);
        
        mSprite->setOpacity(opacity);
    }
    
    void GamePiece::setPieceCollisionEnabled(bool enabled)
    {
        auto piecePhysicsBody = getPhysicsBodyBox2D();
        auto& fixture = piecePhysicsBody->GetFixtureList()[0];
        
        auto filterData = fixture.GetFilterData();
        
        if (enabled) {
            filterData.maskBits = mCollisionMask;
        } else {
            filterData.maskBits = mCollisionMask ^ collision::AllPieces;
        }
        
        fixture.SetFilterData(filterData);
    }
}

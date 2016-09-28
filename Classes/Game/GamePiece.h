//
//  GamePiece.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#pragma once

#include "cocos2d.h"
#include "VelocityTracker.h"
#include "Physics.h"
#include "Enums.h"
#include "PhysicsNode.h"

USING_NS_CC;

namespace flik
{
    class MainGameScene;
    
    
    class GamePiece : public PhysicsNode
    {
    public:
        
        static const int Tag = 0xF0F0;
        
        static GamePiece* create(const Vec2& position, GamePieceType pieceType = GamePieceType::RandomPiece);
        
        bool init(const Vec2& position, GamePieceType pieceType);
        
        bool onContactBegin(PhysicsContact& contact);
        void onPostContactSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
        
        bool mPressed = false;
        
        void setGameScene(MainGameScene* gameScene);
        
        void update(float delta);
        
        Rect getTouchBoundingBox();
        
        int getType() { return mType; }
        
        void setOpacity(float opacity);
        
        void setPieceCollisionEnabled(bool enabled);
        
        bool isDragging() { return mDragging; }
        void setDragging(bool dragging) { mDragging = dragging; }
        
        bool isDecelerating() { return mDecelerating; }
        void setDecelerating(bool decelerating) { mDecelerating = decelerating; }
        
    private:
        
        EventListenerPhysicsContact* mContactListener;
//        PhysicsBody* mPhysicsBody;
        MainGameScene* mGameScene;
        bool mDragging = false;
        bool mDecelerating = false;
        int mType;
        cocos2d::Sprite* mSprite;
        
        int mCategoryMask;
        int mCollisionMask;
    };
}

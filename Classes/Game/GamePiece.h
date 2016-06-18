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

USING_NS_CC;

namespace flik
{
    class MainGameScene;
    
    
    class GamePiece : public Node
    {
    public:
        CREATE_FUNC(GamePiece);
        
        static const int Tag = 0xF0F0;
        
        static GamePiece* create(const Vec2& position);
        
        bool init();
        
        bool onContactBegin(PhysicsContact& contact);
        void onPostContactSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
        
        bool mPressed = false;
        
        void setGameScene(MainGameScene* gameScene) { mGameScene = gameScene; }
        
        void update(float delta);
        
        Rect getTouchBoundingBox();
        
        int getType() { return mType; }
        
    private:
        
        EventListenerPhysicsContact* mContactListener;
        PhysicsBody* mPhysicsBody;
        MainGameScene* mGameScene;
        int mType;
    };
}

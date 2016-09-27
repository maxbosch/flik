//
//  PhysicsNode.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/29/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Box2D.h"

namespace flik
{
    static const float kPixelsToMeters = 32.0f;
    static const float kInversePixelsToMeters = 1.0f / kPixelsToMeters;
    
    class PhysicsNode : public cocos2d::Node
    {
    public:
        CREATE_FUNC(PhysicsNode);
        ~PhysicsNode();
        
        void createPhysicsBody(std::shared_ptr<b2World> world, b2BodyDef* bodyDef);
        void createFixture(b2Shape* shape, float density, float friction, float restitution, int categoryMask, int collisionMask);
        void addBoxFixture(const cocos2d::Size& size, float density, float friction, float restitution, int categoryMask, int collisionMask);
        
        void update(float time);
    
        b2Body* getPhysicsBodyBox2D() { return mPhysicsBodyBox2D; }
        
        void setPosition(const cocos2d::Vec2& position);
        void setPosition(float x, float y);
        
        bool isImpenetrable() { return mImepentrable; }
        void setImpenetrable(bool b) { mImepentrable = b; }
        
        void setParent(Node* parent);
        
    private:
        std::shared_ptr<b2World> mWorld;
        b2Body* mPhysicsBodyBox2D = nullptr;
        bool mImepentrable = false;
        
        void updateBodyPosition();
    };
}

//
//  PhysicsNode.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/29/16.
//
//

#include "PhysicsNode.h"

USING_NS_CC;

namespace flik
{
    static const float kDeg2Rad = (3.14159 / 180.0);
    
    PhysicsNode::~PhysicsNode()
    {
        if (mWorld && mPhysicsBodyBox2D) {
            mWorld->DestroyBody(mPhysicsBodyBox2D);
        }
    }
    
    void PhysicsNode::createPhysicsBody(std::shared_ptr<b2World> world, b2BodyDef* bodyDef)
    {
        bodyDef->userData = this;
        
        mWorld = world;
        mPhysicsBodyBox2D = mWorld->CreateBody(bodyDef);
        mPhysicsBodyBox2D->SetLinearVelocity(b2Vec2(0, 0));
        
        updateBodyPosition();
        
        scheduleUpdate();
    }
    
    void PhysicsNode::createFixture(b2Shape* shape, float density, float friction, float restitution, int categoryMask, int collisionMask)
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        fixtureDef.filter.categoryBits = categoryMask;
        fixtureDef.filter.maskBits = collisionMask;
        mPhysicsBodyBox2D->CreateFixture(&fixtureDef);
    }
    
    void PhysicsNode::addBoxFixture(const cocos2d::Size& size, float density, float friction, float restitution, int categoryMask, int collisionMask)
    {
        b2PolygonShape shape;
        shape.SetAsBox((size.width * 0.5) * kInversePixelsToMeters, (size.height * 0.5) * kInversePixelsToMeters);
        createFixture(&shape, density, friction, restitution, categoryMask, collisionMask);
    }

    void PhysicsNode::update(float time)
    {
        Node::update(time);
        
        if (mPhysicsBodyBox2D && getParent() != nullptr) {
            if (mPhysicsBodyBox2D->IsAwake()) {
                auto x = (mPhysicsBodyBox2D->GetPosition().x * kPixelsToMeters) - (getContentSize().width * (0.5 - getAnchorPoint().x));
                auto y = (mPhysicsBodyBox2D->GetPosition().y * kPixelsToMeters) - (getContentSize().height * (0.5 - getAnchorPoint().y));
                Vec2 position = getParent()->convertToNodeSpace(Vec2(x, y));
                
                Node::setPosition(position.x, position.y);
            } else {
                updateBodyPosition();
            }
        }
    }
    
    void PhysicsNode::setPosition(const Vec2& position)
    {
        Node::setPosition(position);
        
        updateBodyPosition();
    }
    
    void PhysicsNode::setPosition(float x, float y)
    {
        Node::setPosition(x, y);
        
        updateBodyPosition();
    }
    
    void PhysicsNode::updateBodyPosition()
    {
        if (mPhysicsBodyBox2D && getParent() != nullptr) {
            Vec2 worldPosition = getParent()->convertToWorldSpace(getPosition());
            b2Vec2 position((worldPosition.x + (getContentSize().width * (0.5 - getAnchorPoint().x))) * kInversePixelsToMeters,
                            (worldPosition.y + (getContentSize().height * (0.5 - getAnchorPoint().y))) * kInversePixelsToMeters);

            mPhysicsBodyBox2D->SetTransform(position, -getRotation() * kDeg2Rad);
            
            mPhysicsBodyBox2D->SetAwake(false);
        }
    }
    
    void PhysicsNode::setParent(Node* parent)
    {
        Node::setParent(parent);
        
        updateBodyPosition();
    }
}

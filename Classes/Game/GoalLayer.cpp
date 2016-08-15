//
//  GoalBoxLayer.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#include "GoalLayer.h"
#include "Util.h"
#include "Styles.h"
#include "Physics.h"

USING_NS_CC;

namespace flik
{
    GoalLayer* GoalLayer::create(GamePieceType type, const cocos2d::Color4B& color)
    {
        return createWithParams<GoalLayer>(type, color);
    }
    
    bool GoalLayer::init(GamePieceType type, const cocos2d::Color4B& color)
    {
        if (!Node::init())
        {
            return false;
        }
        
        mColorLayer = LayerMultiGradient::create();
        addChild(mColorLayer);
        mColorLayer->setColor(Color3B(color));
        
        mColor = Color3B(color);
        mType = type;
        
        return true;
    }
    
    void GoalLayer::setContentSize(const Size& contentSize)
    {
        Node::setContentSize(contentSize);
        
        mColorLayer->setContentSize(contentSize);
    }
    
    void GoalLayer::addCollisionNode(Node* collisionNode)
    {
        mCollisionNodes.push_back(collisionNode);
    }
    
    void GoalLayer::setCollisionFlags(int categoryMask, int contactTestMask, int collisionMask)
    {
        mCategoryBitmask = categoryMask;
        mCollisionBitmask = collisionMask;
        mContactTestBitmask = contactTestMask;
    }
    
    void GoalLayer::setEnabled(bool enabled)
    {
        mEnabled = enabled;
        
        for (auto node : mCollisionNodes) {
            auto physicsBody = node->getPhysicsBody();
            if (enabled) {
                mColorLayer->setColor(mColor);
                physicsBody->setCategoryBitmask(mCategoryBitmask);
                physicsBody->setContactTestBitmask(mCollisionBitmask);
                physicsBody->setCollisionBitmask(mContactTestBitmask);
            } else {
                mColorLayer->setColor(kBlackColor);
                physicsBody->setCategoryBitmask(collision::BlackRail);
                physicsBody->setContactTestBitmask(collision::AllPieces);
                physicsBody->setCollisionBitmask(collision::AllPieces);
            }
        }
    }
    
    void GoalLayer::overrideCollisionFlags(int categoryMask, int contactTestMask, int collisionMask)
    {
        for (auto node : mCollisionNodes) {
            auto physicsBody = node->getPhysicsBody();
            physicsBody->setCategoryBitmask(categoryMask);
            physicsBody->setContactTestBitmask(collisionMask);
            physicsBody->setCollisionBitmask(contactTestMask);
        }
    }
    
    void GoalLayer::resetCollisionFlags()
    {
        for (auto node : mCollisionNodes) {
            auto physicsBody = node->getPhysicsBody();
            physicsBody->setCategoryBitmask(mCategoryBitmask);
            physicsBody->setContactTestBitmask(mCollisionBitmask);
            physicsBody->setCollisionBitmask(mContactTestBitmask);
        }
    }
    
    void GoalLayer::resetColor()
    {
        mColorLayer->setColor(mColor);
    }
    
    void GoalLayer::overrideColors(const std::vector<Color3B>& colors, const std::vector<float>& locations)
    {
        mColorLayer->setColors(colors, locations);
    }
    
    void GoalLayer::overrideColor(const Color3B& color)
    {
        mColorLayer->setColor(color);
    }
    
    void GoalLayer::setDirection(const cocos2d::Vec2& direction)
    {
        mColorLayer->setDirection(direction);
    }
}

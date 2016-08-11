//
//  GoalBoxLayer.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Enums.h"
#include "LayerMultiGradient.h"

namespace flik
{
    class GoalLayer : public cocos2d::Node
    {
    public:
        static GoalLayer* create(GamePieceType type, const cocos2d::Color4B& color);
        
        bool init(GamePieceType type, const cocos2d::Color4B& color);
        
        GamePieceType getType() { return mType; }
        
        void setEnabled(bool enabled);
        
        void addCollisionNode(cocos2d::Node* collisionNode);
        
        void setCollisionFlags(int categoryMask, int contactTestMask, int collisionMask);
        void overrideCollisionFlags(int categoryMask, int contactTestMask, int collisionMask);
        void resetCollisionFlags();
        
        void overrideColors(const std::vector<cocos2d::Color3B>& colors, const std::vector<float>& locations);
        void overrideColor(const cocos2d::Color3B& color);
        void overrideBackgroundSprite(const std::string& sprite);
        void resetColor();
        
        void setContentSize(const cocos2d::Size& contentSize);
        void setDirection(const cocos2d::Vec2& direction);
        
    private:
        GamePieceType mType;
        cocos2d::Color3B mColor;
        bool mEnabled;
        
        int mCategoryBitmask;
        int mCollisionBitmask;
        int mContactTestBitmask;
        
        std::vector<cocos2d::Node*> mCollisionNodes;
        
        LayerMultiGradient* mColorLayer;
        cocos2d::Sprite* mSprite;
    };
}
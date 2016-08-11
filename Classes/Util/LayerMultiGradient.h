//
//  LayerMultiGradient.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/8/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class LayerMultiGradient : public cocos2d::LayerColor
    {
    public:
        CREATE_FUNC(LayerMultiGradient);

        bool init() override;
        
        void setColors(std::vector<cocos2d::Color3B> colors, std::vector<float> locations);
        void setColor(const cocos2d::Color3B& color) override;
        
        void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
        void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
        
        void setDirection(const cocos2d::Vec2& direction) { mDirection = direction; }
        
    private:
        std::vector<cocos2d::Vec4> mColors;
        std::vector<float> mLocations;
        cocos2d::Vec2 mDirection;
        
        float _squareTexCoords[8];
    };
}
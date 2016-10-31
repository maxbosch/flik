//
//  GLShaderLayer.hpp
//  Flik
//
//  Created by Adam Eskreis on 10/31/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class PercentBubbleLayer : public cocos2d::LayerColor
    {
    public:
        CREATE_FUNC(PercentBubbleLayer)
        
        bool init() override;
        
        void setPercent(float percent);
        
        void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
        void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
        
    private:
        cocos2d::GLProgram* mProgram;
    
        float _squareTexCoords[8];
        cocos2d::Vec4 mColor;
        float mPercent;
    };
}

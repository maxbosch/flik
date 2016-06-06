//
//  Util.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class Util {
    public:
        static cocos2d::Vec2 getRandomPositionInRect(const cocos2d::Rect& rect)
        {
            return cocos2d::Vec2(rect.size.width * cocos2d::random(0.0, 1.0), rect.size.height * cocos2d::random(0.0, 1.0));
        }
    };
}
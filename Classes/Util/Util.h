//
//  Util.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#pragma once

#include "cocos2d.h"
#include <boost/lexical_cast.hpp>

namespace flik
{
    class Util {
    public:
        static cocos2d::Vec2 getRandomPositionInRect(const cocos2d::Rect& rect)
        {
            return cocos2d::Vec2(rect.size.width * cocos2d::random(0.0, 1.0), rect.size.height * cocos2d::random(0.0, 1.0));
        }
        
        static cocos2d::Color3B getColorFromHex(const std::string& hex)
        {
            if (hex.length() != 6) {
                return cocos2d::Color3B();
            }
            
            std::string redstr = hex.substr(0, 2);
            std::string greenstr = hex.substr(2, 2);
            std::string bluestr = hex.substr(4, 2);
            
            int redByte, greenByte, blueByte;
            sscanf(redstr.c_str(), "%x", &redByte);
            sscanf(greenstr.c_str(), "%x", &greenByte);
            sscanf(bluestr.c_str(), "%x", &blueByte);
            
            return cocos2d::Color3B(redByte, greenByte, blueByte);
        }
    };
}
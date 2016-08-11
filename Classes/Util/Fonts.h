//
//  Fonts.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/6/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class Fonts
    {
    public:
        static void load();
        
        static std::string getFontForString(const std::string& str);
        
        static cocos2d::ui::Text* createLocalizedText(const std::string& content, float size);
        static void updateLocalizedText(cocos2d::ui::Text* text, const std::string& content);
        static void updateLocalizedText(cocos2d::ui::Button* button, const std::string& content);
    };
}

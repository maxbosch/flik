//
//  GameSelectRowWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class GameSelectRowWidget : public cocos2d::ui::RelativeBox
    {
    public:
        static GameSelectRowWidget* create(int level, const std::string& name);
        
        bool init(int level, const std::string& name);
        
        std::function<void(int)> onTapped;
    };
}

//
//  GameOverWidget.hpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class GameOverWidget : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(GameOverWidget);
        
        bool init();
        
        std::function<void()> onRestartClick;
    };
}
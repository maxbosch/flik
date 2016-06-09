//
//  MainMenuHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"

namespace flik
{
    class MainMenuHUD : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(MainMenuHUD);
        
        virtual ~MainMenuHUD();
        
        bool init();
        
        std::function<void(GameModeType type)> onGameModeSelected;
        std::function<void()> onShowStoreTapped;
    };
}

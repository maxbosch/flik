//
//  MainMenuHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/2/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"

namespace flik
{
    class MainMenuScene : public cocos2d::Scene
    {
    public:
        CREATE_FUNC(MainMenuScene);
    
        bool init();
        
    private:
        void onGameModeSelected(GameModeType type);
    };
}

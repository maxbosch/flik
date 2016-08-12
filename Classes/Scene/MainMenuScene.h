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
#include "SceneEx.h"

namespace flik
{
    class MainMenuScene : public SceneEx
    {
    public:
        CREATE_FUNC(MainMenuScene);
    
        bool init();
        
        void onBackPressed();
        
    private:
        void onGameModeSelected(GameModeType type);
    };
}

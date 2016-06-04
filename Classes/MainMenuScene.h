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

namespace flik
{
    class MainMenuScene : public cocos2d::Layer
    {
    public:
        static cocos2d::Scene* createScene();
        
        CREATE_FUNC(MainMenuScene);
    
        bool init();
    };
}

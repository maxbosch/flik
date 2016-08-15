//
//  SettingsScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/23/16.
//
//

#pragma once

#include "cocos2d.h"
#include "SceneEx.h"

namespace flik
{
    class SettingsScene : public SceneEx
    {
    public:
        CREATE_FUNC(SettingsScene);
        
        bool init();
        
        void onBackPressed();
    };
}

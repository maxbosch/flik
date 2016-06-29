//
//  SettingsScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/23/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class SettingsScene : public cocos2d::Scene
    {
    public:
        CREATE_FUNC(SettingsScene);
        
        bool init();
    };
}

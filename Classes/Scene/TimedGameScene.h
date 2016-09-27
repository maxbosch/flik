//
//  TimedGameScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#pragma once

#include "MainGameScene.h"

namespace flik
{
    class TimedGameScene : public MainGameScene
    {
    public:
        CREATE_FUNC(TimedGameScene);
        
        bool init();
        
        void reloadScene();
    };
}

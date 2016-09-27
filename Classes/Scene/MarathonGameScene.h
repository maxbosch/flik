//
//  MarathonGameScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#pragma once

#include "MainGameScene.h"

namespace flik
{
    class MarathonGameScene : public MainGameScene
    {
    public:
        CREATE_FUNC(MarathonGameScene);
        
        bool init();
        
        void reloadScene();
    };
}

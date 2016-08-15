//
//  GameSelectScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#pragma once

#include "cocos2d.h"
#include "SceneEx.h"

namespace flik
{
    class GameSelectScene : public SceneEx
    {
    public:
        CREATE_FUNC(GameSelectScene);
        
        bool init();
        
        void onBackPressed();
    };
}

//
//  LevelSelectScene.hpp
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
    class LevelSelectScene : public SceneEx
    {
    public:
        CREATE_FUNC(LevelSelectScene);
        
        bool init();
        
        void onBackPressed();
    };
}

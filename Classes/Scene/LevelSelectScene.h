//
//  LevelSelectScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class LevelSelectScene : public cocos2d::Scene
    {
    public:
        CREATE_FUNC(LevelSelectScene);
        
        bool init();
    };
}

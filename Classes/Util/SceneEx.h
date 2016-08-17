//
//  SceneEx.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/11/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class SceneEx : public cocos2d::Scene
    {
    public:
        virtual void onBackPressed();
        
        virtual void onAppear();
    };
}
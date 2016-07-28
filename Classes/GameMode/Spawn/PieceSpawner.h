//
//  PieceSpawner.h
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#pragma once

#include "cocos2d.h"

namespace flik
{
    class MainGameScene;
    
    class PieceSpawner : public cocos2d::Node
    {
    public:
        virtual void start(MainGameScene* scene) = 0;
        virtual void stop(MainGameScene* scene) = 0;
    };
}

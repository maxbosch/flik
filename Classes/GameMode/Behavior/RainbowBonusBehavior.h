//
//  GhostBonusBehavior.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#pragma once

#include "Behavior.h"

namespace flik
{
    class RainbowBonusBehavior : public Behavior
    {
    public:
        static RainbowBonusBehavior* create(MainGameScene* scene, float duration);
        
        bool init(MainGameScene* scene, float duration);
        
    protected:
        void onExpire(MainGameScene* scene);
    };
}

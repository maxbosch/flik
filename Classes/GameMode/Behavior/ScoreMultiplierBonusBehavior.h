//
//  ScoreMultiplierBehavior.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/13/16.
//
//

#pragma once

#include "Behavior.h"

namespace flik
{
    class ScoreMultiplierBonusBehavior : public Behavior
    {
    public:
        static ScoreMultiplierBonusBehavior* create(MainGameScene* scene, float duration, int multiplier);
        
        bool init(MainGameScene* scene, float duration, int multiplier);
        
        void onExpire(MainGameScene* scene);
    };
}

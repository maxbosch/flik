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
    class GhostBonusBehavior : public Behavior
    {
    public:
        static GhostBonusBehavior* create(MainGameScene* scene, float duration);
        
        bool init(MainGameScene* scene, float duration);
    };
}

//
//  GravityBonusBehavior.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/13/16.
//
//

#pragma once

#pragma once

#include "Behavior.h"

namespace flik
{
    class GamePiece;
    
    class GravityBonusBehavior : public Behavior
    {
    public:
        static GravityBonusBehavior* create(MainGameScene* scene, float duration);
        
        bool init(MainGameScene* scene, float duration);
        
        void onExpire(MainGameScene* scene);
        
    private:
        void applyGravity(GamePiece* piece);
    };
}


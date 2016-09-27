//
//  ScoreMultiplierBehavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/13/16.
//
//

#include "ScoreMultiplierBonusBehavior.h"
#include "Util.h"
#include "Events.h"
#include "GamePiece.h"
#include "Physics.h"
#include "MainGameScene.h"
#include "GameBoard.h"
#include "GameMode.h"

USING_NS_CC;

namespace flik
{
    ScoreMultiplierBonusBehavior* ScoreMultiplierBonusBehavior::create(MainGameScene* scene, float duration, int multiplier)
    {
        return createWithParams<ScoreMultiplierBonusBehavior>(scene, duration, multiplier);
    }
    
    bool ScoreMultiplierBonusBehavior::init(MainGameScene* scene, float duration, int multiplier)
    {
        if (!Behavior::init(scene, duration))
        {
            return false;
        }
        
        scene->getGameMode()->setScoreMultiplier(multiplier);
        
        return true;
    }
    
    void ScoreMultiplierBonusBehavior::onExpire(MainGameScene* scene)
    {
        scene->getGameMode()->setScoreMultiplier(1);
    }
}


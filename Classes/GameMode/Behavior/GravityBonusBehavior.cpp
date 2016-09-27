//
//  GravityBonusBehavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/13/16.
//
//

#include "GravityBonusBehavior.h"
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
    GravityBonusBehavior* GravityBonusBehavior::create(MainGameScene* scene, float duration)
    {
        return createWithParams<GravityBonusBehavior>(scene, duration);
    }
    
    bool GravityBonusBehavior::init(MainGameScene* scene, float duration)
    {
        if (!Behavior::init(scene, duration))
        {
            return false;
        }
        
        auto gameBoard = scene->getGameBoard();
        auto pieces = gameBoard->getPieces();
        
        for (auto piece : pieces) {
 
        }
        
        return true;
    }
                
    void GravityBonusBehavior::applyGravity(GamePiece* piece)
    {
        
    }
    
    void GravityBonusBehavior::onExpire(MainGameScene* scene)
    {
        scene->getGameMode()->setScoreMultiplier(1);
    }
}

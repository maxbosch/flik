//
//  GameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#include "GameMode.h"

namespace flik {
    void GameMode::setGameState(GameState newState)
    {
        mGameState = newState;
        
        if (onGameStateChanged) {
            onGameStateChanged(newState);
        }
    }
}
//
//  MarathonGameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#pragma once

#include "cocos2d.h"
#include "GameMode.h"

namespace flik
{
    class MarathonGameMode : public GameMode
    {
    public:
        CREATE_FUNC(MarathonGameMode);
        
        ~MarathonGameMode() {}
        
        bool init();
        
        void restartGame();
        
        int getTopScore();
        
        void handlePowerUp(PowerUpType type);
        
        GameModeType getGameModeType() { return GameModeType::Unlimited; }
        
        void update(float seconds);
        
    protected:
        void setGameState(GameState newState);
        
    private:
        int mIterations;
        int mSpawnCount;
        int mLastSpawnIteration;
        float mSpawnInterval;
        float mTimeSinceSpawn;
    };
}

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
        
        void update(float seconds);
        
        void handlePowerUp(PowerUpType type);
        
    protected:
        void setGameState(GameState newState);
        
    private:
        int mIterations;
        int mSpawnCount;
        int mLastSpawnIteration;
        float mSpawnInterval;
        float mTimeSinceSpawn;
        
        void spawnPieces(int count);
        cocos2d::Vec2 findOpenSpawnPosition();
    };
}

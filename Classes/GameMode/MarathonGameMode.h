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
        
        bool init();
        
        void restartGame();
        
        int getTopScore();
        
    protected:
        void setGameState(GameState newState);
        
    private:
        int mIterations;
        int mSpawnCount;
        int mLastSpawnIteration;
        float mSpawnInterval;
        
        void spawnPieces(int count);
        cocos2d::Vec2 findOpenSpawnPosition();
    };
}

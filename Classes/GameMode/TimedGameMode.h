//
//  TimedGameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#pragma once

#include "cocos2d.h"
#include "GameMode.h"

namespace flik
{
    class TimedGameMode : public GameMode
    {
    public:
        CREATE_FUNC(TimedGameMode);
        
        ~TimedGameMode() {}
        
        static TimedGameMode* createWithTime(float seconds);
        
        void setGameTime(float seconds) { mGameTime = seconds; }
        
        void restartGame();
        
        bool init();
        
        void update(float seconds);
        
        float getTimeRemaining() { return mTimeRemaining; }
        float getGameTime() { return mGameTime; }
        
        int getTopScore();
        
    protected:
        void setGameState(GameState newState);
        
    private:
        float mTimeRemaining;
        float mGameTime;
    };
}


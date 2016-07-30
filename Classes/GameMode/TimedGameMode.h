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
        
        bool init();

        int getTopScore();
        
        GameModeType getGameModeType() { return GameModeType::Timed; }
        
    protected:
        void setGameState(GameState newState);
    
    };
}


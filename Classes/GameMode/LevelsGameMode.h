//
//  LevelGameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#pragma once

#include "cocos2d.h"
#include "TimedGameMode.h"
#include "LevelTypes.h"

namespace flik
{
    class LevelsGameMode : public TimedGameMode
    {
    public:
        CREATE_FUNC(LevelsGameMode);
        
        virtual void restartGame();
        
        virtual int getTopScore();
        
        virtual GameModeType getGameModeType();
    };
}

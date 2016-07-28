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
    class LevelsGameMode : public GameMode
    {
    public:
        static LevelsGameMode* create(const LevelDescription* levelDesc);
        
        bool init(const LevelDescription* levelDesc);
        
        virtual void restartGame();
        
        virtual int getTopScore();
        
        virtual GameModeType getGameModeType();
        
        bool isObjectiveCompleted() { return mProgress.isCompleted(); }
        
    private:
        const LevelDescription* mLevelDesc;
        LevelProgress mProgress;
    };
}

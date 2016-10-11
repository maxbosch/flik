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
    class ObjectiveTracker;
    
    class LevelsGameMode : public GameMode
    {
    public:
        static LevelsGameMode* create(const LevelDescription* levelDesc, int sublevel);
        
        bool init(const LevelDescription* levelDesc, int sublevel);
        
        virtual void restartGame();
        
        virtual int getTopScore();
        
        virtual GameModeType getGameModeType();
        
        bool isObjectiveCompleted();
    
        void update(float seconds);
        
        void setGameScene(MainGameScene* scene);
        void setGameState(GameState state);
        
        std::vector<ObjectiveTracker*> getObjectives() { return mObjectives; }
        
        int getSublevel() { return mSublevel; }
        
        int getScore() { return mScore; }
        int getPointsEarned() { return mPointsEarned; }
        
        void onBackPressed();
        
    private:
        const LevelDescription* mLevelDesc;
        int mSublevel;
        std::vector<ObjectiveTracker*> mObjectives;
        LevelProgress mProgress;
        int mScore;
        int mPointsEarned;
    };
}

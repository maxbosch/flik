//
//  TimedSpawner.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#include "TimedSpawner.h"
#include "MainGameScene.h"
#include "GameMode.h"
#include "Events.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    TimedSpawner* TimedSpawner::create(int initialCount, float interval)
    {
        return createWithParams<TimedSpawner>(initialCount, interval);
    }
    
    bool TimedSpawner::init(int initialCount, float interval)
    {
        if (!PieceSpawner::init())
        {
            return false;
        }
        
        mCount = initialCount;
        mInterval = interval;
        
        return true;
    }
    
    void TimedSpawner::start(MainGameScene* scene)
    {
        for (int i = 0; i < mCount; i++) {
            scene->spawnPiece(Util::getRandomPositionInRect(scene->getGameBoardBounds()));
        }
        
        mTimeSinceSpawn = 0;
        
        mScene = scene;
        
        scheduleUpdate();
    }
    
    void TimedSpawner::stop(MainGameScene* scene)
    {
        unscheduleUpdate();
    }
    
    void TimedSpawner::update(float seconds)
    {
        auto gameMode = mScene->getGameMode();
        if (gameMode->getGameState() == GameState::InProgress && !gameMode->isTimeStopped()) {
            mTimeSinceSpawn += seconds;
            
            if (mTimeSinceSpawn >= mInterval) {
                mTimeSinceSpawn -= mInterval;
                
                for (int i = 0; i < mCount; i++) {
                    mScene->spawnPiece(Util::getRandomPositionInRect(mScene->getGameBoardBounds()));
                }
            }
        }
    }
}

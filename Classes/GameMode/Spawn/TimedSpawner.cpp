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
#include "GameBoard.h"

USING_NS_CC;

namespace flik
{
    TimedSpawner* TimedSpawner::create(int initialCount, float interval, int count, bool spawnWhenIdle)
    {
        return createWithParams<TimedSpawner>(initialCount, interval, count, spawnWhenIdle);
    }
    
    bool TimedSpawner::init(int initialCount, float interval, int count, bool spawnWhenIdle)
    {
        if (!PieceSpawner::init())
        {
            return false;
        }
        
        mCount = count;
        mInitialCount = initialCount;
        mInterval = interval;
        mSpawnWhenIdle = spawnWhenIdle;
        
        return true;
    }
    
    void TimedSpawner::start(MainGameScene* scene)
    {
        for (int i = 0; i < mInitialCount; i++) {
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
            bool spawnMore = false;
            if (mScene->getGameBoard()->getPieces().size() == 0) {
                spawnMore = true;
                mTimeSinceSpawn = 0;
            } else {
                mTimeSinceSpawn += seconds;
                
                if (mTimeSinceSpawn >= mInterval) {
                    mTimeSinceSpawn -= mInterval;
                    spawnMore = true;
                }
            }
            
            if (spawnMore) {
                for (int i = 0; i < mCount; i++) {
                    mScene->spawnPiece(Util::getRandomPositionInRect(mScene->getGameBoardBounds()));
                }
            }
        }
    }
}

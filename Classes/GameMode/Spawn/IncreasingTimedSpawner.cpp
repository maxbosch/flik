//
//  RampingTimedSpawner.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#include "IncreasingTimedSpawner.h"
#include "MainGameScene.h"
#include "GameMode.h"
#include "Util.h"


namespace flik
{
    IncreasingTimedSpawner* IncreasingTimedSpawner::create(int initialCount, float interval, int count,
                                                           float increaseInterval, int increaseAmount)
    {
        return createWithParams<IncreasingTimedSpawner>(initialCount, interval, count, increaseInterval, increaseAmount);
    }
    
    bool IncreasingTimedSpawner::init(int initialCount, float interval, int count,
                                      float increaseInterval, int increaseAmount)
    {
        if (!TimedSpawner::init(initialCount, interval, count))
        {
            return false;
        }
        
        mIncreaseAmount = increaseAmount;
        mIncreaseInterval = increaseInterval;
        
        return true;
    }
    
    void IncreasingTimedSpawner::update(float seconds)
    {
        TimedSpawner::update(seconds);
        
        auto gameMode = getGameScene()->getGameMode();
        if (gameMode->getGameState() == GameState::InProgress && !gameMode->isTimeStopped()) {
            mTimeSinceIntervalIncrease += seconds;
            
            if (mTimeSinceIntervalIncrease >= mIncreaseInterval) {
                mTimeSinceIntervalIncrease -= mIncreaseInterval;
                
                setCount(getCount() + mIncreaseAmount);
            }
        }
    }
    
    void IncreasingTimedSpawner::start(MainGameScene* scene)
    {
        TimedSpawner::start(scene);
        
        mTimeSinceIntervalIncrease = 0;
    }
}

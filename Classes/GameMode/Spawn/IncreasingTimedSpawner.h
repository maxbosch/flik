//
//  RampingTimedSpawner.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#pragma once

#include "TimedSpawner.h"

namespace flik
{
    class IncreasingTimedSpawner : public TimedSpawner
    {
    public:
        static IncreasingTimedSpawner* create(int initialCount, float interval, int count, bool spawnWhenIdle,
                                           float increaseInterval, int increaseAmount);
        
        bool init(int initialCount, float interval, int count, bool spawnWhenIdle,
                  float increaseInterval, int increaseAmount);
        
        void setIncreaseAmount(int amount) { mIncreaseAmount = amount; }
        void setIncreaseInterval(float interval) { mIncreaseInterval = interval; }
        
        int getIncreaseAmount() { return mIncreaseAmount; }
        float getIncreaseInterval() { return mIncreaseInterval; }
        
        void update(float seconds);
        
        void start(MainGameScene* scene);
        
    private:
        float mIncreaseInterval;
        int mIncreaseAmount;
        
        float mTimeSinceIntervalIncrease = 0;
    };
}

//
//  TimedSpawner.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#pragma once

#include "PieceSpawner.h"
#include "cocos2d.h"

namespace flik
{
    class MainGameScene;
    
    class TimedSpawner : public PieceSpawner
    {
    public:
        static TimedSpawner* create(int initialCount, float interval);
        
        bool init(int initialCount, float interval);
        
        void setCount(int count) { mCount = count; }
        void setInterval(float interval) { mInterval = interval; }
        
        int getCount() { return mCount; }
        float getInterval() { return mInterval; }
        
        virtual void start(MainGameScene* scene);
        void stop(MainGameScene* scene);
        
        virtual void update(float seconds);
        
    protected:
        MainGameScene* getGameScene() { return mScene; }
        
    private:
        int mCount = 0;
        float mInterval = 0;
        float mTimeSinceSpawn = 0;
        MainGameScene* mScene;
        
        cocos2d::EventListenerCustom* mPieceRemovedListener;
    };
}
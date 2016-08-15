//
//  MaxOnBoardObjectiveTracker.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#pragma once

#include "ObjectiveTracker.h"

namespace flik
{
    class MainGameScene;
    
    class MaxOnBoardObjectiveTracker : public ObjectiveTracker
    {
    public:
        static MaxOnBoardObjectiveTracker* create(MainGameScene* scene, int required);
        
        bool init(MainGameScene* scene, int maximum);
        
        virtual int getCurrentValue()
        {
            return mCurrent;
        }
        
        virtual int getTotalValue()
        {
            return mMaximum;
        }
        
        virtual bool isCompleted()
        {
            return mMaximum > mCurrent;
        }
        
        virtual bool isFailed()
        {
            return mMaximum <= mCurrent;
        }
        
        void update(float seconds);
        
        virtual bool finishWhenComplete()
        {
            return false;
        }
        
        void reset()
        {
            mCurrent = 0;
        }
        
    private:
        int mMaximum;
        int mCurrent;
        
        MainGameScene* mScene;
    };
}
//
//  PiecesClearedObjectiveTracker.hpp
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
    
    class PiecesClearedObjectiveTracker : public ObjectiveTracker
    {
    public:
        static PiecesClearedObjectiveTracker* create(MainGameScene* scene, int required);
        
        bool init(MainGameScene* scene, int required);
        
        virtual int getCurrentValue()
        {
            return mCurrent;
        }
        
        virtual int getTotalValue()
        {
            return mRequired;
        }
        
        virtual bool isCompleted()
        {
            return mRequired <= mCurrent;
        }
        
        virtual bool isFailed()
        {
            return false;
        }
        
        virtual bool finishWhenComplete()
        {
            return true;
        }
        
        void reset()
        {
            mCurrent = 0;
        }
        
    private:
        int mRequired;
        int mCurrent;
    };
}

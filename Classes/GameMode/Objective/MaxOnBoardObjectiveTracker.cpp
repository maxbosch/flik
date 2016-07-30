//
//  MaxOnBoardObjectiveTracker.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#include "MaxOnBoardObjectiveTracker.h"
#include "MainGameScene.h"
#include "GameBoard.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    MaxOnBoardObjectiveTracker* MaxOnBoardObjectiveTracker::create(MainGameScene* scene, int required)
    {
        return createWithParams<MaxOnBoardObjectiveTracker>(scene, required);
    }
    
    bool MaxOnBoardObjectiveTracker::init(MainGameScene* scene, int maximum)
    {
        if (!ObjectiveTracker::init())
        {
            return false;
        }
        
        mScene = scene;
        mMaximum = maximum;
        
        this->scheduleUpdate();
    
        return true;
    }
    
    void MaxOnBoardObjectiveTracker::update(float seconds)
    {
        ObjectiveTracker::update(seconds);
        
        mCurrent = (int) mScene->getGameBoard()->getPieces().size();
    }
}

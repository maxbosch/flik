//
//  PiecesClearedObjectiveTracker.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#include "PiecesClearedObjectiveTracker.h"
#include "Events.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    PiecesClearedObjectiveTracker* PiecesClearedObjectiveTracker::create(int required)
    {
        return createWithParams<PiecesClearedObjectiveTracker>(required);
    }
    
    bool PiecesClearedObjectiveTracker::init(int required)
    {
        if (!ObjectiveTracker::init())
        {
            return false;
        }
        
        mCurrent = 0;
        mRequired = required;
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            mCurrent += 1;
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
}
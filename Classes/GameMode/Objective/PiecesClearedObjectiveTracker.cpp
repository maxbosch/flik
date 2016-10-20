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
#include "MainGameScene.h"
#include "GameMode.h"

USING_NS_CC;

namespace flik
{
    PiecesClearedObjectiveTracker* PiecesClearedObjectiveTracker::create(MainGameScene* scene, int required)
    {
        return createWithParams<PiecesClearedObjectiveTracker>(scene, required);
    }
    
    bool PiecesClearedObjectiveTracker::init(MainGameScene* scene, int required)
    {
        if (!ObjectiveTracker::init())
        {
            return false;
        }
        
        mCurrent = 0;
        mRequired = required;
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this, scene](EventCustom* event) {
            mCurrent += scene->getGameMode()->getScoreMultiplier();
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
}

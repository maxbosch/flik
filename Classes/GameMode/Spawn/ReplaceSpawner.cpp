//
//  ReplaceSpawner.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/27/16.
//
//

#include "ReplaceSpawner.h"
#include "MainGameScene.h"
#include "Events.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    ReplaceSpawner* ReplaceSpawner::create(int initialCount)
    {
        return createWithParams<ReplaceSpawner>(initialCount);
    }
    
    bool ReplaceSpawner::init(int initialCount)
    {
        if (!PieceSpawner::init())
        {
            return false;
        }
        
        mCount = initialCount;
        
        return true;
    }
    
    void ReplaceSpawner::start(MainGameScene* scene)
    {
        mPieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this, scene](EventCustom* event) {
            scene->spawnPiece(Util::getRandomPositionInRect(scene->getGameBoardBounds()));
        });
        
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(mPieceRemovedListener, this);
        
        for (int i = 0; i < mCount; i++) {
            scene->spawnPiece(Util::getRandomPositionInRect(scene->getGameBoardBounds()));
        }
    }
    
    void ReplaceSpawner::stop(MainGameScene* scene)
    {
        getEventDispatcher()->removeEventListener(mPieceRemovedListener);
    }
}

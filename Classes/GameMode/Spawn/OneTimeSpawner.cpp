//
//  OneTimeSpawner.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#include "OneTimeSpawner.h"
#include "MainGameScene.h"
#include "Events.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    OneTimeSpawner* OneTimeSpawner::create(int initialCount)
    {
        return createWithParams<OneTimeSpawner>(initialCount);
    }
    
    bool OneTimeSpawner::init(int initialCount)
    {
        if (!PieceSpawner::init())
        {
            return false;
        }
        
        mCount = initialCount;
        
        return true;
    }
    
    void OneTimeSpawner::start(MainGameScene* scene)
    {
        for (int i = 0; i < mCount; i++) {
            scene->spawnPiece(Util::getRandomPositionInRect(scene->getGameBoardBounds()));
        }
    }
    
    void OneTimeSpawner::stop(MainGameScene* scene)
    {
    }
}

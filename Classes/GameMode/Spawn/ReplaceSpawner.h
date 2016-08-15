//
//  ReplaceSpawner.hpp
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
    
    class ReplaceSpawner : public PieceSpawner
    {
    public:
        static ReplaceSpawner* create(int initialCount);
        
        bool init(int initialCount);
        
        void setCount(int count) { mCount = count; }
        
        void start(MainGameScene* scene);
        void stop(MainGameScene* scene);
        
    private:
        int mCount = 0;
        
        cocos2d::EventListenerCustom* mPieceRemovedListener;
    };
}

//
//  OneTimeSpawner.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/28/16.
//
//

#pragma once

#include "PieceSpawner.h"

namespace flik
{
    class MainGameScene;
    
    class OneTimeSpawner : public PieceSpawner
    {
    public:
        static OneTimeSpawner* create(int initialCount);
        
        bool init(int initialCount);
        
        void setCount(int count) { mCount = count; }
        
        void start(MainGameScene* scene);
        void stop(MainGameScene* scene);
        
    private:
        int mCount = 0;
    };
}

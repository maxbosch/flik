//
//  LevelGameScene.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/27/16.
//
//

#pragma once

#include "MainGameScene.h"

namespace flik
{
    class LevelDescription;
    
    class LevelGameScene : public MainGameScene
    {
    public:
        static LevelGameScene* create(const LevelDescription* levelDesc, int sublevel);
        
        bool init(const LevelDescription* levelDesc, int sublevel);
        
        void reloadScene();
        
    private:
        const LevelDescription* mLevelDesc;
        int mSublevel;
    };
}

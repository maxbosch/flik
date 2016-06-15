//
//  LevelsGameHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#include "LevelsGameHUD.h"
#include "Util.h"

namespace flik
{
    LevelsGameHUD* LevelsGameHUD::create(const LevelDescription& levelDesc)
    {
        return createWithParams<LevelsGameHUD>(levelDesc);
    }
    
    bool LevelsGameHUD::init(const LevelDescription& levelDesc)
    {
        if (!TimedGameHUD::init())
        {
            return false;
        }
        
        
        
        return true;
    }
}

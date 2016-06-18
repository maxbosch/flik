//
//  LevelsGameHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#pragma once

#include "cocos2d.h"
#include "TimedGameHUD.h"
#include "LevelTypes.h"

USING_NS_CC;

namespace flik
{
    class LevelsGameHUD : public TimedGameHUD
    {
    public:
        static LevelsGameHUD* create(const LevelDescription* levelDesc);
        
        bool init(const LevelDescription* levelDesc);
        
        virtual GameObjectiveOverlay* createObjectiveOverlay();
        
    private:
        const LevelDescription* mLevelDesc;
        
        virtual cocos2d::ui::Widget* createGameOverOverlay();
        virtual void onShowGameOverScreen();
    };
}

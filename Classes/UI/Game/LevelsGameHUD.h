//
//  LevelsGameHUD.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#pragma once

#include "cocos2d.h"
#include "MainGameHUD.h"
#include "LevelTypes.h"

USING_NS_CC;

namespace flik
{
    class LevelsGameHUD : public MainGameHUD
    {
    public:
        static LevelsGameHUD* create(const LevelDescription* levelDesc);
        
        bool init(const LevelDescription* levelDesc);
        
        virtual GameObjectiveOverlay* createObjectiveOverlay();
        
        void update(float seconds);
        
    private:
        const LevelDescription* mLevelDesc;
        
        virtual cocos2d::ui::Widget* createGameOverOverlay();
        virtual void onShowGameOverScreen();
        
        int mObjectiveProgress;
        
        cocos2d::ui::Text* mObjectiveText;
    };
}

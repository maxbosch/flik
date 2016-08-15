//
//  LevelObjectiveOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/16/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameObjectiveOverlay.h"

namespace flik
{
    class LevelDescription;
    
    class LevelObjectiveOverlay : public GameObjectiveOverlay
    {
    public:
        static LevelObjectiveOverlay* create(const std::string& title, const LevelDescription* levelDesc, int sublevel);
        
        bool init(const std::string& title, const LevelDescription* levelDesc, int sublevel);
        
        cocos2d::ui::Widget* createTitleWidget(const std::string& title);
        cocos2d::ui::Widget* createObjectiveWidget();
        
    private:
        int mLevel;
        int mSublevel;
        const LevelDescription* mLevelDesc;
    };
}

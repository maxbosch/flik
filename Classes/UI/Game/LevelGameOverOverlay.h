//
//  LevelGameOverOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/18/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class ScoreWidget;
    
    class LevelGameOverOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(LevelGameOverOverlay);
        
        bool init();
        
        void setTitle(const std::string& title);
        void setNextLevel(bool success, int level);
        
        std::function<void()> onRestartTapped;
        std::function<void()> onHomeTapped;
        std::function<void()> onAchievementsTapped;
        std::function<void()> onNextLevelTapped;
        std::function<void()> onShowLevelListTapped;
        
    private:
        cocos2d::ui::Text* mTitleLabel;
        cocos2d::ui::Button* mAchievementsButton;
        cocos2d::ui::Button* mNextLevelButton;
    };
}
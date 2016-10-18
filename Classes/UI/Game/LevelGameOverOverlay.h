//
//  LevelSuccessGameOverOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 8/17/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class LevelGameOverOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(LevelGameOverOverlay);
        
        bool init();
        
        void show(int level, bool success, int score, int pointsEarned, bool hasNext);
        
        std::function<void()> onRestartTapped;
        std::function<void()> onNextLevelTapped;
        std::function<void()> onShowLevelListTapped;
        
    private:
        std::vector<cocos2d::ui::ImageView*> mStarWidgets;
        cocos2d::ui::Text* mPointsLabel;
        cocos2d::ui::RelativeBox* mContentContainer;
        
        void animateStar(int maxStar, int star = 1);
        void animatePoints(int points);
        
        void createSuccessWidget(int level, int score, int pointsEarned, bool hasNext);
        void createFailureWidget(int level);
    };
}

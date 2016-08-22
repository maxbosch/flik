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
    class LevelSuccessGameOverOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(LevelSuccessGameOverOverlay);
        
        bool init();
        
        void show(int score, int pointsEarned);
        
        std::function<void()> onRestartTapped;
        std::function<void()> onNextLevelTapped;
        std::function<void()> onShowLevelListTapped;
        
    private:
        std::vector<cocos2d::ui::ImageView*> mStarWidgets;
        cocos2d::ui::Text* mPointsLabel;
        int mNextStar;
        
        void animateStar(int maxStar, int star = 1);
        void animatePoints(int points);
    };
}

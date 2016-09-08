//
//  AchievementOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 9/7/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class AchievementOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        static AchievementOverlay* create(const std::string& achievementName);
        
        bool init(const std::string& achievementName);
        
        std::function<void()> onNextLevelTapped;
    };
}

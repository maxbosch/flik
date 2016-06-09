//
//  PauseOverlayWidget.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class PauseOverlayWidget : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(PauseOverlayWidget);
        
        bool init();
        
        std::function<void()> onHomeTapped;
        std::function<void()> onAchievementsTapped;
        std::function<void()> onSettingsTapped;
        std::function<void()> onBackTapped;
        std::function<void()> onRestartTapped;
    };
}

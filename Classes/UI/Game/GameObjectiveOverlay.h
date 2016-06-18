//
//  GameObjectiveOverlay.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class GameObjectiveOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        bool init(const std::string& title);
        
        virtual cocos2d::ui::Widget* createObjectiveWidget() = 0;
        
        std::function<void()> onStartButtonTapped;
        std::function<void()> onExitButtonTapped;
        
    private:
        cocos2d::ui::Text* mTitleLabel;
    };
}

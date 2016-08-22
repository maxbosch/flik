//
//  DefaultGameOverOverlay.hpp
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
    
    class DefaultGameOverOverlay : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(DefaultGameOverOverlay);
        
        bool init();
        
        void show(int gameScore, int topScore);
        
        std::function<void()> onRestartTapped;
        std::function<void()> onHomeTapped;
        
        
    private:
        cocos2d::ui::VBox* mContentContainer;
        
        void createDefaulteWidget(int gameScore, int topScore);
        void createNewTopScoreWidget(int gameScore, int topScore);
    };
}

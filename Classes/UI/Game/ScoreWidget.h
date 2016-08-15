//
//  ScoreWidget.hpp
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
    class ScoreWidget : public cocos2d::ui::VBox
    {
    public:
        static ScoreWidget* create(const std::string& title);
        
        bool init(const std::string& title);
        
        void setScore(int score);
        
    private:
        cocos2d::ui::Text* mScoreLabel;
    };
}

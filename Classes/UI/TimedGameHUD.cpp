//
//  TimedGameHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#include "TimedGameHUD.h"
#include "ui/CocosGUI.h"
#include "TimedGameMode.h"
#include "MainGameScene.h"
#include <boost/lexical_cast.hpp>

USING_NS_CC;

using RelativeAlign = cocos2d::ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    bool TimedGameHUD::init()
    {
        if (!MainGameHUD::init())
        {
            return false;
        }
        
        auto timerLabel = ui::Text::create("0", "GothamRnd-Bold.otf", 16);
        timerLabel->setTextColor(Color4B(255, 255, 255, 255));
        addChild(timerLabel);
        auto timerLabelLayout = ui::RelativeLayoutParameter::create();
        timerLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        timerLabelLayout->setMargin(ui::Margin(0, 20, 0, 0));
        timerLabel->setLayoutParameter(timerLabelLayout);
        mTimerLabel = timerLabel;
        
        return true;
    }
    
    void TimedGameHUD::update(float time)
    {
        MainGameHUD::update(time);
        
        auto gameMode = dynamic_cast<TimedGameMode*>(getGameScene()->getGameMode());
        mTimerLabel->setString(boost::lexical_cast<std::string>(std::floor(gameMode->getTimeRemaining())));
    }
}
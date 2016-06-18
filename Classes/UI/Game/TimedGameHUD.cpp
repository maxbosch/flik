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
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "TextObjectiveOverlay.h"

USING_NS_CC;

using RelativeAlign = cocos2d::ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    TimedGameHUD::~TimedGameHUD()
    {
        
    }
    
    bool TimedGameHUD::init()
    {
        if (!MainGameHUD::init())
        {
            return false;
        }
        
        auto timerBar = ui::RelativeBox::create(Size(getContentSize().width, 5.0_dp));
        timerBar->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        timerBar->setBackGroundColor(Util::getColorFromHex("FACC89"));
        auto timerBarLayout = ui::RelativeLayoutParameter::create();
        timerBarLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        timerBar->setLayoutParameter(timerBarLayout);
        addChild(timerBar, 2);
        mTimerBar = timerBar;
        
        return true;
    }
    
    void TimedGameHUD::update(float time)
    {
        MainGameHUD::update(time);
        
        auto gameMode = dynamic_cast<TimedGameMode*>(getGameScene()->getGameMode());
        auto ratio = gameMode->getTimeRemaining() / gameMode->getGameTime();
        mTimerBar->setContentSize(Size(getContentSize().width * ratio, mTimerBar->getContentSize().height));
    }
    
    GameObjectiveOverlay* TimedGameHUD::createObjectiveOverlay()
    {
        return TextObjectiveOverlay::create("Timed Mode", "Score as many points as you can before time runs out");
    }
}
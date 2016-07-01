//
//  MainGameHeader.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#include <boost/lexical_cast.hpp>

#include "MainGameHeader.h"
#include "Styles.h"
#include "PowerUpButton.h"
#include "Literals.h"
#include "Player.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool MainGameHeader::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(Size(uiSize.width, 70.0_dp));
        setBackGroundColor(Color3B::BLACK);
        setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        auto timestopPowerUpButton = PowerUpButton::create(PowerUpType::Timestop);
        auto timestopPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
        timestopPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        timestopPowerUpButtonLayout->setMargin(ui::Margin(30.0_dp, 16.0_dp, 0, 0));
        timestopPowerUpButton->setLayoutParameter(timestopPowerUpButtonLayout);
        timestopPowerUpButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onPowerUpTapped) {
                onPowerUpTapped(PowerUpType::Timestop);
            }
        });
        addChild(timestopPowerUpButton);
        
        auto targetPowerUpButton = PowerUpButton::create(PowerUpType::Target);
        auto targetPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
        targetPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        targetPowerUpButtonLayout->setMargin(ui::Margin(0, 16.0_dp, 30.0_dp, 0));
        targetPowerUpButton->setLayoutParameter(targetPowerUpButtonLayout);
        addChild(targetPowerUpButton);
        targetPowerUpButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onPowerUpTapped) {
                onPowerUpTapped(PowerUpType::Target);
            }
        });
        
        auto scoreLabel = ui::Text::create("0", kDefaultFont, 25.0_dp);
        auto scoreLabelLayout = ui::RelativeLayoutParameter::create();
        scoreLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        scoreLabelLayout->setMargin(ui::Margin(0, 27.0_dp, 0, 0));
        scoreLabel->setLayoutParameter(scoreLabelLayout);
        addChild(scoreLabel);
        mScoreLabel = scoreLabel;
        
        setScoreVisible(true);
        
        return true;
    }
    
    void MainGameHeader::setScore(int score)
    {
        mScoreLabel->setString(boost::lexical_cast<std::string>(score));
    }
    
    void MainGameHeader::setScoreVisible(bool visible)
    {
        mScoreLabel->setVisible(visible);
    }
}
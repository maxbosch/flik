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
        
        auto pauseButton = ui::RelativeBox::create(Size(70.0_dp, 70.0_dp));
        pauseButton->setTouchEnabled(true);
        auto pauseButtonLayout = ui::RelativeLayoutParameter::create();
        pauseButtonLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        pauseButtonLayout->setMargin(ui::Margin(0, 0, 0, 0));
        pauseButton->setLayoutParameter(pauseButtonLayout);
        pauseButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onPauseTapped) {
                onPauseTapped();
            }
        });
        addChild(pauseButton);
        
        auto pauseButtonImage = ui::ImageView::create("pause_icon.png");
        auto pauseButtonImageLayout = ui::RelativeLayoutParameter::create();
        pauseButtonImageLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        pauseButtonImage->setLayoutParameter(pauseButtonImageLayout);
        pauseButton->addChild(pauseButtonImage);
        
        auto scoreLabel = Fonts::createLocalizedText("0", 25.0_dp);
        auto scoreLabelLayout = ui::RelativeLayoutParameter::create();
        scoreLabelLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        scoreLabelLayout->setMargin(ui::Margin(0, 27.0_dp, 30.0_dp, 0));
        scoreLabel->setLayoutParameter(scoreLabelLayout);
        addChild(scoreLabel);
        mScoreLabel = scoreLabel;
        
        setScoreVisible(true);
        
        return true;
    }
    
    void MainGameHeader::setScore(int score)
    {
        Fonts::updateLocalizedText(mScoreLabel, boost::lexical_cast<std::string>(score));
    }
    
    void MainGameHeader::setScoreVisible(bool visible)
    {
        mScoreLabel->setVisible(visible);
    }
}

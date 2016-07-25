//
//  DefaultGameOverOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/18/16.
//
//

#include <boost/lexical_cast.hpp>

#include "DefaultGameOverOverlay.h"
#include "Styles.h"
#include "Literals.h"
#include "ScoreWidget.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool DefaultGameOverOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.7 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto innerContainer = ui::RelativeBox::create(Size(305.0_dp, 455.0_dp));
        innerContainer->ignoreContentAdaptWithSize(false);
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto backgroundImage = ui::Scale9Sprite::create(Rect(34.0_dp, 34.0_dp, 32.0_dp, 32.0_dp), "blue_border_9.png");
        backgroundImage->setAnchorPoint(Vec2());
        innerContainer->addChild(backgroundImage);
        
        auto titleLabel = Fonts::createLocalizedText("", 18.0_dp);
        titleLabel->setColor(Color3B::WHITE);
        auto titleLabelLayout = ui::RelativeLayoutParameter::create();
        titleLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        titleLabelLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        titleLabelLayout->setRelativeName("title");
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        mTitleLabel = titleLabel;
        
        auto border1 = ui::HBox::create(Size(210.0_dp, 3.0_dp));
        border1->setBackGroundColor(kBlueBorderColor);
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::RelativeLayoutParameter::create();
        borderLayout1->setRelativeToWidgetName("title");
        borderLayout1->setRelativeName("border");
        borderLayout1->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        borderLayout1->setMargin(ui::Margin(0, 45.0_dp, 0, 0));
        border1->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border1);
        
        auto restartButton = ui::Button::create("pause_restart.png");
        auto restartButtonLayout = ui::RelativeLayoutParameter::create();
        restartButtonLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
        restartButtonLayout->setMargin(ui::Margin(30.0_dp, 0, 0, 35.0_dp));
        restartButton->setLayoutParameter(restartButtonLayout);
        restartButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onRestartTapped) {
                onRestartTapped();
            }
        });
        innerContainer->addChild(restartButton);
        
        auto homeButton = ui::Button::create("pause_home.png");
        auto homeButtonLayout = ui::RelativeLayoutParameter::create();
        homeButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
        homeButtonLayout->setMargin(ui::Margin(0, 0, 30.0_dp, 35.0_dp));
        homeButton->setLayoutParameter(homeButtonLayout);
        homeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onHomeTapped) {
                onHomeTapped();
            }
        });
        innerContainer->addChild(homeButton);
        
        auto score = ScoreWidget::create("Current");
        auto scoreLayout = ui::RelativeLayoutParameter::create();
        scoreLayout->setAlign(RelativeAlign::LOCATION_BELOW_LEFTALIGN);
        scoreLayout->setRelativeToWidgetName("border");
        scoreLayout->setMargin(ui::Margin(20.0_dp, 75.0_dp, 0, 0));
        score->setLayoutParameter(scoreLayout);
        innerContainer->addChild(score);
        mScore = score;
        
        auto topscore = ScoreWidget::create("Best");
        auto topscoreLayout = ui::RelativeLayoutParameter::create();
        topscoreLayout->setAlign(RelativeAlign::LOCATION_BELOW_RIGHTALIGN);
        topscoreLayout->setRelativeToWidgetName("border");
        topscoreLayout->setMargin(ui::Margin(0, 75.0_dp, 20.0_dp, 0));
        topscore->setLayoutParameter(topscoreLayout);
        innerContainer->addChild(topscore);
        mTopScore = topscore;
        
        innerContainer->forceDoLayout();
        //innerContainer->setContentSize(Size(305.0_dp, startButton->getBoundingBox().getMaxY() + 30.0_dp));
        backgroundImage->setContentSize(innerContainer->getContentSize());
        
        return true;
    }
    
    void DefaultGameOverOverlay::setTitle(const std::string& title)
    {
        mTitleLabel->setString(title);
    }
    
    void DefaultGameOverOverlay::setTopScore(int score)
    {
        mTopScore->setScore(score);
    }
    
    void DefaultGameOverOverlay::setCurrentScore(int score)
    {
        mScore->setScore(score);
    }
}
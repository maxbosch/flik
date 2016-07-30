//
//  LevelGameOverOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/18/16.
//
//

#include "LevelGameOverOverlay.h"
#include "Styles.h"
#include "Literals.h"
#include "ScoreWidget.h"
#include "LevelTypes.h"
#include "LocalizedString.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool LevelGameOverOverlay::init()
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
        backgroundImage->setContentSize(innerContainer->getContentSize());
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
        
        auto achievementsButton = ui::Button::create("pause_achievements.png");
        auto achievementsButtonLayout = ui::RelativeLayoutParameter::create();
        achievementsButtonLayout->setAlign(RelativeAlign::LOCATION_BELOW_RIGHTALIGN);
        achievementsButtonLayout->setRelativeToWidgetName("border");
        achievementsButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 30.0_dp, 0));
        achievementsButton->setLayoutParameter(achievementsButtonLayout);
        achievementsButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onAchievementsTapped) {
                onAchievementsTapped();
            }
        });
        innerContainer->addChild(achievementsButton);
        mAchievementsButton = achievementsButton;
        
        auto nextLevelButton = ui::Button::create("pink_button_fill_large.png");
        nextLevelButton->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
        nextLevelButton->setTitleFontSize(15.0_dp);
        nextLevelButton->setTitleColor(Color3B::WHITE);
        
        auto nextLevelButtonLayout = ui::RelativeLayoutParameter::create();
        nextLevelButtonLayout->setAlign(RelativeAlign::LOCATION_BELOW_RIGHTALIGN);
        nextLevelButtonLayout->setRelativeToWidgetName("border");
        nextLevelButtonLayout->setMargin(ui::Margin(0, 35.0_dp, -20.0_dp, 0));
        nextLevelButton->setLayoutParameter(nextLevelButtonLayout);
        nextLevelButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onNextLevelTapped) {
                onNextLevelTapped();
            }
        });
        innerContainer->addChild(nextLevelButton);
        mNextLevelButton = nextLevelButton;
        
        auto levelListButton = ui::Button::create("pink_button_fill_large.png");
        levelListButton->setTitleAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
        levelListButton->setTitleFontSize(15.0_dp);
        levelListButton->setTitleColor(Color3B::WHITE);
        levelListButton->setTitleText("Back To\n List");
        levelListButton->setTitleFontName(Fonts::getFontForString(levelListButton->getTitleText()));
        auto levelListButtonLayout = ui::RelativeLayoutParameter::create();
        levelListButtonLayout->setAlign(RelativeAlign::LOCATION_BELOW_LEFTALIGN);
        levelListButtonLayout->setRelativeToWidgetName("border");
        levelListButtonLayout->setMargin(ui::Margin(-20.0_dp, 35.0_dp, 0, 0));
        levelListButton->setLayoutParameter(levelListButtonLayout);
        levelListButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onShowLevelListTapped) {
                onShowLevelListTapped();
            }
        });
        innerContainer->addChild(levelListButton);
        
        innerContainer->forceDoLayout();
        //innerContainer->setContentSize(Size(305.0_dp, startButton->getBoundingBox().getMaxY() + 30.0_dp));
        
        return true;
    }
    
    void LevelGameOverOverlay::setTitle(const std::string& title)
    {
        mTitleLabel->setString(title);
    }
    
    void LevelGameOverOverlay::setNextLevel(bool success, int level)
    {
        int sublevel = LevelInfo::getInstance()->getSublevel(level);
        
        if (success && level <= LevelInfo::getInstance()->getMaxLevel()) {
            mNextLevelButton->setTitleText(LocalizedString::getString("game_over_try_next", level, sublevel + 2));
            
            mNextLevelButton->setVisible(true);
            mAchievementsButton->setVisible(false);
        } else {
            mAchievementsButton->setVisible(true);
            mNextLevelButton->setVisible(false);
        }
        
        if (success) {
            mTitleLabel->setString(LocalizedString::getString("level_success"));
        } else {
            mTitleLabel->setString(LocalizedString::getString("level_failed", level - 1, sublevel + 1));
        }
        
        mNextLevelButton->setTitleFontName(Fonts::getFontForString(mNextLevelButton->getTitleText()));
    }
}

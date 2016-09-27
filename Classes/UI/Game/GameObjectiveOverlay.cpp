//
//  GameObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#include <boost/algorithm/string.hpp>

#include "GameObjectiveOverlay.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "BlurredBackgroundWidget.h"
#include "Animations.h"
#include "LocalizedString.h"
#include "BonusBar.h"
#include "ChoosePowerupScene.h"
#include "SceneManager.h"
#include "Player.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool GameObjectiveOverlay::init(const std::string& title)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        //setBackGroundColor(Color3B::BLACK);
        //setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        //auto overlayBackground = BlurredBackgroundWidget::create();
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.8 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto innerContainer = ui::VBox::create(Size(305.0_dp, 475.0_dp));
        innerContainer->ignoreContentAdaptWithSize(false);
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto backgroundImage = ui::Scale9Sprite::create(Rect(34.0_dp, 34.0_dp, 32.0_dp, 32.0_dp), "blue_border_9.png");
        backgroundImage->setAnchorPoint(Vec2());
        innerContainer->addChild(backgroundImage);
        mContentContainer = innerContainer;
    
        innerContainer->addChild(createTitleWidget(title));
        
        /*auto objectiveTextLabel = Fonts::createLocalizedText(LocalizedString::getString("objective"), 15.0_dp);
        auto objectiveTextLabelLayout = ui::LinearLayoutParameter::create();
        objectiveTextLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        objectiveTextLabelLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 20.0_dp));
        objectiveTextLabel->setLayoutParameter(objectiveTextLabelLayout);
        innerContainer->addChild(objectiveTextLabel);*/
        
        auto objectiveWidget = createObjectiveWidget();
        auto objectiveContainerLayout = ui::LinearLayoutParameter::create();
        objectiveContainerLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        objectiveContainerLayout->setMargin(ui::Margin(0, 23.0_dp, 0, 30.0_dp));
        objectiveWidget->setLayoutParameter(objectiveContainerLayout);
        innerContainer->addChild(objectiveWidget);
        
        auto border2 = ui::HBox::create(Size(210.0_dp, 3.0_dp));
        border2->setBackGroundColor(kBlueBorderColor);
        border2->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout2 = ui::LinearLayoutParameter::create();
        borderLayout2->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border2->setLayoutParameter(borderLayout2);
        innerContainer->addChild(border2);
        
        auto bonusContainer = ui::VBox::create(Size(250.0_dp, 85.0_dp));
        auto bonusContainerLayout = ui::LinearLayoutParameter::create();
        bonusContainerLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        bonusContainerLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 30.0_dp));
        bonusContainer->setLayoutParameter(bonusContainerLayout);
        innerContainer->addChild(bonusContainer);
        
        auto chooseBonusText = Fonts::createLocalizedText(LocalizedString::getString("choose_bonus"), 15.0_dp);
        chooseBonusText->setColor(kPinkColor);
        auto chooseBonusTextLayout = ui::LinearLayoutParameter::create();
        chooseBonusTextLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        chooseBonusText->setLayoutParameter(chooseBonusTextLayout);
        bonusContainer->addChild(chooseBonusText);
        
        auto bonusBar = BonusBar::create(Size(bonusContainer->getContentSize().width, 47.5_dp));
        auto bonusBarLayout = ui::LinearLayoutParameter::create();
        bonusBarLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        bonusBarLayout->setMargin(ui::Margin(0, 15.0_dp, 0, 0));
        bonusBar->setLayoutParameter(bonusBarLayout);
        bonusContainer->addChild(bonusBar);
        
        mCurrentBonuses = Player::getMainPlayer()->getLastBonusChoices();
        
        auto openChooseScene = [this]() {
            auto scene = ChoosePowerupScene::create(mCurrentBonuses);
            scene->onPowerupsChosen = [this](const std::vector<BonusType>& bonuses) {
                mBonusBar->setBonuses(bonuses);
                mCurrentBonuses = bonuses;
            };
            SceneManager::pushSceneWithTransition<TransitionSlideInR>(scene, kTransitionDuration);
        };
        
        bonusBar->onBonusTapped = [this, openChooseScene](BonusType bonus) {
            openChooseScene();
        };
        bonusBar->onAddBonusTapped = openChooseScene;
        bonusBar->setTouchEnabled(true);
        bonusBar->setBonuses(mCurrentBonuses);
        mBonusBar = bonusBar;
        
        auto startButton = ui::Button::create("pink_button_fill_large.png");
        startButton->setTitleFontSize(18.0_dp);
        Fonts::updateLocalizedText(startButton, LocalizedString::getString("button_start"));
        startButton->setTitleColor(Color3B::WHITE);
        auto startButtonLayout = ui::LinearLayoutParameter::create();
        startButtonLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        startButtonLayout->setMargin(ui::Margin(0, 0, 0, 30.0_dp));
        startButton->setLayoutParameter(startButtonLayout);
        innerContainer->addChild(startButton);
        
        startButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onStartButtonTapped) {
                onStartButtonTapped(mCurrentBonuses);
            }
        });
        
        auto startButtonBox = startButton->getBoundingBox();
        innerContainer->forceDoLayout();
        //innerContainer->setContentSize(Size(305.0_dp, startButton->getBoundingBox().getMaxY() + 30.0_dp));
        backgroundImage->setContentSize(innerContainer->getContentSize());
        
        auto exitButton = ui::Button::create("red_x_close.png");
        auto exitButtonLayout = ui::RelativeLayoutParameter::create();
        exitButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        exitButtonLayout->setMargin(ui::Margin(0, 0, 0, 20.0_dp));
        exitButton->setLayoutParameter(exitButtonLayout);
        addChild(exitButton);
        
        exitButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onExitButtonTapped) {
                onExitButtonTapped();
            }
        });
        
        innerContainer->setAnchorPoint(Vec2(0.5, 0.5));
        innerContainer->setScale(0);
        
        performIntroAnimation();
        
        return true;
    }

    void GameObjectiveOverlay::performIntroAnimation()
    {
        Animations::animate(kTransitionDuration, [this](float t) {
            mContentContainer->setScale(t);
        }, nullptr, OvershootCurve);
    }
    
    cocos2d::ui::Widget* GameObjectiveOverlay::createTitleWidget(const std::string& title)
    {
        auto titleLabel = Fonts::createLocalizedText(title, 25.0_dp);
        titleLabel->setColor(kGoldColor);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 45.0_dp, 0, 0));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        return titleLabel;
    }
}

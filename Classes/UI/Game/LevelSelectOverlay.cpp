//
//  LevelSelectOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include "LevelSelectOverlay.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "LevelTypes.h"
#include "LevelSelectRowWidget.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "MainGameScene.h"
#include "SceneManager.h"
#include "LocalizedString.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;

    
    bool LevelSelectOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.7 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto innerContainer = ui::VBox::create(Size(305.0_dp, 525.0_dp));
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        innerContainerLayout->setMargin(ui::Margin(0, 40.0_dp, 0, 0));
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto backgroundImage = ui::Scale9Sprite::create(Rect(34.0_dp, 34.0_dp, 32.0_dp, 32.0_dp), "blue_border_9.png");
        backgroundImage->setAnchorPoint(Vec2());
        backgroundImage->setContentSize(innerContainer->getContentSize());
        innerContainer->addChild(backgroundImage);
        
        auto titleLabel = Fonts::createLocalizedText(LocalizedString::getString("levels_list_title"), 18.0_dp);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 45.0_dp, 0, 45.0_dp));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        
        auto border1 = ui::HBox::create(Size(210.0_dp, 3.0_dp));
        border1->setBackGroundColor(kBlueBorderColor);
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::LinearLayoutParameter::create();
        borderLayout1->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border1->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border1);
        
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
        
        
        double rowHeight = 65.0_dp;
        auto levelInfo = LevelInfo::getInstance();
        
        auto scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(295.0_dp, 390.0_dp));
        scrollView->setInnerContainerSize(Size(305.0_dp, rowHeight * levelInfo->getMaxLevel()));
        scrollView->setLayoutType(ui::Layout::Type::VERTICAL);
        scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        scrollView->setTouchEnabled(true);
        scrollView->setScrollBarAutoHideEnabled(true);
        scrollView->setScrollBarEnabled(true);
        scrollView->setScrollBarWidth(9.0_dp);
        scrollView->setScrollBarColor(kBlueBorderColor);
        scrollView->setScrollBarOpacity(255);
        auto scrollViewLayout = ui::LinearLayoutParameter::create();
        scrollViewLayout->setMargin(ui::Margin(5.0_dp, 16.0_dp, 5.0_dp, 0));
        scrollView->setLayoutParameter(scrollViewLayout);
        
        for (int i = 1; i <= levelInfo->getMaxLevel(); i++) {
            auto row = LevelSelectRowWidget::create(i);
            row->setContentSize(Size(305.0_dp, rowHeight));
            row->onTapped = [this, levelInfo](int level) {
                auto levelInfo = LevelInfo::getInstance();
                auto levelDesc = levelInfo->getLevelDescription(level);
                auto gameScene = MainGameScene::create({LevelsGameMode::create(levelDesc), LevelsGameHUD::create(levelDesc)});
                SceneManager::pushSceneWithTransition<TransitionSlideInR>(gameScene, kTransitionDuration);
            };
            scrollView->addChild(row);
        }
        
        innerContainer->addChild(scrollView);
       
        return true;
    }
}
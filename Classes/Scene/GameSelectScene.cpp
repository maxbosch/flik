//
//  GameSelectScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include "GameSelectScene.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "LevelTypes.h"
#include "GameSelectRowWidget.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "MainGameScene.h"
#include "SceneManager.h"
#include "LocalizedString.h"
#include "LevelSelectScene.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool GameSelectScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto container = ui::RelativeBox::create(uiSize);
        addChild(container);
        
        auto innerContainer = ui::VBox::create(Size(uiSize.width - 30, uiSize.height));
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        innerContainerLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        innerContainer->setLayoutParameter(innerContainerLayout);
        container->addChild(innerContainer);
        
        auto titleLabel = Fonts::createLocalizedText(LocalizedString::getString("levels_list_title"), 25.0_dp);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 0, 0, 25.0_dp));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        
        auto border1 = ui::HBox::create(Size(260.0_dp, 3.0_dp));
        border1->setBackGroundColor(kBlueBorderColor);
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::LinearLayoutParameter::create();
        borderLayout1->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border1->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border1);
        
        auto exitButton = ui::Button::create("red_x_close.png");
        auto exitButtonLayout = ui::RelativeLayoutParameter::create();
        exitButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        exitButtonLayout->setMargin(ui::Margin(20.0_dp, 20.0_dp, 0, 0));
        exitButton->setLayoutParameter(exitButtonLayout);
        container->addChild(exitButton);
        exitButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                onBackPressed();
            }
        });
        
        
        double rowHeight = 80.0_dp;
        auto levelInfo = LevelInfo::getInstance();
        
        auto scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(uiSize.width - 50, 470.0_dp));
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
        scrollViewLayout->setMargin(ui::Margin(5.0_dp, 25.0_dp, 5.0_dp, 0));
        scrollView->setLayoutParameter(scrollViewLayout);
        
        for (int i = 1; i <= levelInfo->getMaxLevel(); i++) {
            auto level = levelInfo->getLevelDescription(i);
            auto row = GameSelectRowWidget::create(i, level->data["name"].GetString());
            row->setContentSize(Size(scrollView->getContentSize().width, rowHeight));
            row->onTapped = [this, levelInfo](int level) {
                auto levelsScene = LevelSelectScene::create(level);
                SceneManager::pushSceneWithTransition<TransitionSlideInR>(levelsScene, kTransitionDuration);
            };
            scrollView->addChild(row);
        }
        
        innerContainer->addChild(scrollView);
        
        return true;
    }
    
    void GameSelectScene::onBackPressed()
    {
        SceneManager::popToRootSceneWithTransition<TransitionSlideInB>(kTransitionDuration);
    }
}
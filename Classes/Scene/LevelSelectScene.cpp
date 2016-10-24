//
//  GameSelectScene.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/20/16.
//
//

#include <boost/algorithm/string/case_conv.hpp>

#include "LevelSelectScene.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "LevelTypes.h"
#include "LevelSelectRowWidget.h"
#include "LevelsGameMode.h"
#include "LevelsGameHUD.h"
#include "LevelGameScene.h"
#include "SceneManager.h"
#include "LocalizedString.h"
#include "LevelTypes.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    static const double kRowHeight = 80.0_dp;
    
    LevelSelectScene* LevelSelectScene::create(int level)
    {
        return createWithParams<LevelSelectScene>(level);
    }
    
    bool LevelSelectScene::init(int level)
    {
        if (!Scene::init())
        {
            return false;
        }
        
        auto levelDesc = LevelInfo::getInstance()->getLevelDescription(level);
        mLevelDesc = levelDesc;
        
        std::string levelName = levelDesc->data["name"].GetString();
        
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
        
        auto titleLabel = Fonts::createLocalizedText(boost::to_upper_copy(LocalizedString::getString("level_name_" + levelName)), 25.0_dp);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 0, 0, 25.0_dp));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        
        auto border1 = ui::HBox::create(Size(uiSize.width, 3.0_dp));
        border1->setBackGroundColor(kBlueBorderColor);
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::LinearLayoutParameter::create();
        borderLayout1->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border1->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border1);
        
        auto exitButton = ui::Button::create("arrow_left.png");
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
       
        auto scrollView = ui::ScrollView::create();
        scrollView->setContentSize(Size(uiSize.width - 50, 545.0_dp));
        scrollView->setLayoutType(ui::Layout::Type::VERTICAL);
        scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        scrollView->setTouchEnabled(true);
        scrollView->setScrollBarEnabled(true);
        scrollView->setScrollBarOpacity(255);
        scrollView->setScrollBarAutoHideEnabled(false);
        scrollView->setScrollBarWidth(9.0_dp);
        scrollView->setScrollBarColor(kMaroonColor);
        
        auto scrollViewLayout = ui::LinearLayoutParameter::create();
        scrollViewLayout->setMargin(ui::Margin(5.0_dp, 0, 5.0_dp, 0));
        scrollView->setLayoutParameter(scrollViewLayout);
        
        mScrollView = scrollView;
        
        innerContainer->addChild(scrollView);
        
        return true;
    }
    
    void LevelSelectScene::onBackPressed()
    {
        SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
    }
    
    void LevelSelectScene::onAppear()
    {
        mScrollView->removeAllChildren();
        
        auto& sublevels = mLevelDesc->data["sublevels"];
        for (int i = 0; i < sublevels.Size(); i++) {
            auto row = LevelSelectRowWidget::create(mLevelDesc->levelNum, i);
            row->setContentSize(Size(mScrollView->getContentSize().width, kRowHeight));
            row->onTapped = [this](int sublevel) {
                int status = LevelInfo::getInstance()->getLevelStatus(mLevelDesc->levelNum, sublevel);
                if (status >= 0) {
                    auto gameScene = LevelGameScene::create(mLevelDesc, sublevel);
                    SceneManager::pushSceneWithTransition<TransitionSlideInR>(gameScene, kTransitionDuration);
                }
            };
            mScrollView->addChild(row);
        }

        mScrollView->setInnerContainerSize(Size(305.0_dp, kRowHeight * sublevels.Size()));
    }
}

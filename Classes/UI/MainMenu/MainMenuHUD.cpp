//
//  MainMenuHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#include "MainMenuHUD.h"
#include "MainMenuHeader.h"
#include "MainMenuButtons.h"
#include "MainMenuFooter.h"
#include "Literals.h"
#include "Animations.h"
#include "CCSwipeGestureRecognizer.h"
#include "SettingsScene.h"
#include "AchievementsScene.h"
#include "SceneManager.h"
#include "Styles.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    MainMenuHUD::~MainMenuHUD()
    {
    }
    
    bool MainMenuHUD::init()
    {
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(uiSize);
        
        double headerHeight = 62.0_dp;
        double footerHeight = 75.0_dp;
        
        auto header = MainMenuHeader::create();
        header->setContentSize(Size(uiSize.width, headerHeight));
        auto headerLayout = ui::RelativeLayoutParameter::create();
        headerLayout->setRelativeName("header");
        headerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        header->setLayoutParameter(headerLayout);
        addChild(header);
        mHeader = header;
        
        auto buttons = MainMenuButtons::create();
        buttons->setContentSize(Size(uiSize.width, uiSize.height - headerHeight - footerHeight));
        auto buttonsLayout = ui::RelativeLayoutParameter::create();
        buttonsLayout->setRelativeToWidgetName("header");
        buttonsLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        buttons->setLayoutParameter(buttonsLayout);
        buttons->onGameModeSelected = [this](GameModeType type) {
            if (onGameModeSelected) {
                onGameModeSelected(type);
            }
        };
        addChild(buttons);
        mButtonsContainer = buttons;
        
        auto footer = MainMenuFooter::create();
        footer->setContentSize(Size(uiSize.width, footerHeight));
        auto footerLayout = ui::RelativeLayoutParameter::create();
        footerLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
        footer->setLayoutParameter(footerLayout);
        footer->onShowStoreTapped = [this]() {
            if (onShowStoreTapped) {
                onShowStoreTapped();
            }
        };
        footer->setBackGroundColor(Color3B::BLACK);
        footer->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        addChild(footer);
        mFooter = footer;
        
        auto swipeGesture = SwipeGestureRecognizer::create();
        swipeGesture->setTarget(this, static_cast<SEL_CallFuncO>(&MainMenuHUD::onSwipe));
        swipeGesture->setDirection(kSwipeGestureRecognizerDirectionRight | kSwipeGestureRecognizerDirectionLeft);
        addChild(swipeGesture);
        
        return true;
    }
    
    void MainMenuHUD::onSwipe(Ref* gesture)
    {
        Swipe* swipeGesture = dynamic_cast<Swipe*>(gesture);
        if (swipeGesture) {
            if (swipeGesture->direction == kSwipeGestureRecognizerDirectionLeft) {
                auto settingsScene = SettingsScene::create();
                SceneManager::pushSceneWithTransition<TransitionSlideInR>(settingsScene, kTransitionDuration);
            } else {
                SceneManager::pushSceneWithTransition<TransitionSlideInL>(AchievementsScene::create(), kTransitionDuration);
            }
        }
    }
    
    void MainMenuHUD::animateElements()
    {
        mButtonsContainer->animateButtons();
        
//        Mat4 transform;
//        
//        Mat4::createTranslation(Vec3(0, mHeader->getContentSize().height, 0), &transform);
//        mHeader->setAdditionalTransform(transform);
//        
//        Mat4::createTranslation(Vec3(0, -mFooter->getContentSize().height, 0), &transform);
//        mFooter->setAdditionalTransform(transform);
//        
//        Animations::animate(0.35, [this](float t) {
//            Mat4 transform;
//            
//            Mat4::createTranslation(Vec3(0, mHeader->getContentSize().height * (1.0 - t), 0), &transform);
//            mHeader->setAdditionalTransform(transform);
//            
//            Mat4::createTranslation(Vec3(0, -mFooter->getContentSize().height * (1.0 - t), 0), &transform);
//            mFooter->setAdditionalTransform(transform);
//        }, [this](bool finished) {
//            mHeader->setAdditionalTransform(Mat4());
//            mFooter->setAdditionalTransform(Mat4());
//        }, QuadraticEaseInCurve);
    }
}

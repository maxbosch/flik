//
//  MainMenuButtons.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#include "MainMenuButtons.h"
#include "Styles.h"
#include "Literals.h"
#include "Enums.h"
#include "LocalizedString.h"
#include "Fonts.h"
#include "LevelTypes.h"
#include "Animations.h"

#include <boost/lexical_cast.hpp>

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool MainMenuButtons::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto innerContainer = RelativeBox::create();
        innerContainer->setContentSize(Size(255.0_dp, 300.0_dp));
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto createButton = [this](const std::string& image, const std::string& title, GameModeType gameType) -> ui::Button* {
            auto button = ui::Button::create(image);
            Fonts::updateLocalizedText(button, title);
            button->setTitleColor(Color3B::WHITE);
            button->setTitleFontSize(23.0_dp);
            button->addTouchEventListener([this, gameType](Ref* sender, ui::Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED) {
                    if (onGameModeSelected) {
                        onGameModeSelected(gameType);
                    }
                }
            });
            
            auto label = button->getTitleRenderer();
            auto buttonSize = button->getContentSize();
            auto labelSize = label->getContentSize();
            label->setPosition(Vec2(buttonSize.width * 0.5, buttonSize.height + 20.0_dp));
            
            return button;
        };
        
        auto levelsButton = createButton("games_home.png", LocalizedString::getString("main_menu_mode_levels"), GameModeType::Levels);
        auto levelsButtonLayout = ui::RelativeLayoutParameter::create();
        levelsButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        //levelsButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        levelsButton->setLayoutParameter(levelsButtonLayout);
        innerContainer->addChild(levelsButton);
        levelsButton->setVisible(false);
        mGamesButton = levelsButton;
        
        auto timedButton = createButton("timer_home.png", LocalizedString::getString("main_menu_mode_timed"), GameModeType::Timed);
        auto timedButtonLayout = ui::RelativeLayoutParameter::create();
        timedButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        timedButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        timedButton->setLayoutParameter(timedButtonLayout);
        innerContainer->addChild(timedButton);
        timedButton->setVisible(false);
        mTimedButton = timedButton;
        
        auto unlimitedButton = createButton("unlimited_home.png", LocalizedString::getString("main_menu_mode_unlimited"), GameModeType::Unlimited);
        auto unlimitedButtonLayout = ui::RelativeLayoutParameter::create();
        unlimitedButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        unlimitedButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        unlimitedButton->setLayoutParameter(unlimitedButtonLayout);
        unlimitedButton->setVisible(false);
        innerContainer->addChild(unlimitedButton);
        mUnlimitedButton = unlimitedButton;
        
        return true;
    }
    
    void MainMenuButtons::animateButtons()
    {
        mTimedButton->setVisible(true);
        mUnlimitedButton->setVisible(true);
        mGamesButton->setVisible(true);
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        Mat4 transform;
        
        Mat4::createTranslation(Vec3(-uiSize.width, 0, 0), &transform);
        mTimedButton->setAdditionalTransform(transform);
        
        Mat4::createTranslation(Vec3(uiSize.width, 0, 0), &transform);
        mUnlimitedButton->setAdditionalTransform(transform);
        
        Mat4::createTranslation(Vec3(0, uiSize.height, 0), &transform);
        mGamesButton->setAdditionalTransform(transform);
        
        Animations::animate(0.5, [this, uiSize](float t) {
            Mat4 transform;
            
            Mat4::createTranslation(Vec3(-uiSize.width * (1.0 - t), 0, 0), &transform);
            mTimedButton->setAdditionalTransform(transform);
            
            Mat4::createTranslation(Vec3(uiSize.width * (1.0 - t), 0, 0), &transform);
            mUnlimitedButton->setAdditionalTransform(transform);
            
            Mat4::createTranslation(Vec3(0, -uiSize.height * (1.0 - t), 0), &transform);
            mGamesButton->setAdditionalTransform(transform);
        }, [this](bool finished) {
            mTimedButton->setAdditionalTransform(Mat4());
            mUnlimitedButton->setAdditionalTransform(Mat4());
            mGamesButton->setAdditionalTransform(Mat4());
        }, QuadraticEaseInCurve);
    }
}

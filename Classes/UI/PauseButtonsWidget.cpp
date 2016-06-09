//
//  PauseButtonsWIdget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#include "PauseButtonsWidget.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool PauseButtonsWidget::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(Size(227.0_dp, 227.0_dp));
        
        auto backButton = ui::Button::create("pause_back.png");
        auto backButtonLayout = ui::RelativeLayoutParameter::create();
        backButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        backButton->setLayoutParameter(backButtonLayout);
        backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onBackTapped) {
                onBackTapped();
            }
        });
        addChild(backButton);
        
        auto homeButton = ui::Button::create("pause_home.png");
        auto homeButtonLayout = ui::RelativeLayoutParameter::create();
        homeButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        homeButton->setLayoutParameter(homeButtonLayout);
        homeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onHomeTapped) {
                onHomeTapped();
            }
        });
        addChild(homeButton);
        
        auto achievementsButton = ui::Button::create("pause_achievements.png");
        auto achievementsButtonLayout = ui::RelativeLayoutParameter::create();
        achievementsButtonLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
        achievementsButton->setLayoutParameter(achievementsButtonLayout);
        achievementsButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onAchievementsTapped) {
                onAchievementsTapped();
            }
        });
        addChild(achievementsButton);
        
        auto settingsButton = ui::Button::create("pause_settings.png");
        auto settingsButtonLayout = ui::RelativeLayoutParameter::create();
        settingsButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
        settingsButton->setLayoutParameter(settingsButtonLayout);
        settingsButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onSettingsTapped) {
                onSettingsTapped();
            }
        });
        addChild(settingsButton);
        
        return true;
        
    }
}

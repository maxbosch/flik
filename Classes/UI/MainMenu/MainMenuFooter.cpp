//
//  MainMenuFooter.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/9/16.
//
//

#include "MainMenuFooter.h"
#include "PowerUpButton.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool MainMenuFooter::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto timestopPowerUpButton = PowerUpButton::create(PowerUpType::Timestop);
        auto timestopPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
        timestopPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        timestopPowerUpButtonLayout->setMargin(ui::Margin(30.0_dp, 14.0_dp, 0, 0));
        timestopPowerUpButton->setLayoutParameter(timestopPowerUpButtonLayout);
        addChild(timestopPowerUpButton);
        
        auto targetPowerUpButton = PowerUpButton::create(PowerUpType::Target);
        auto targetPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
        targetPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        targetPowerUpButtonLayout->setMargin(ui::Margin(0, 14.0_dp, 30.0_dp, 0));
        targetPowerUpButton->setLayoutParameter(targetPowerUpButtonLayout);
        addChild(targetPowerUpButton);
        
        auto storeButton = ui::Button::create("store.png");
        auto storeButtonLayout = ui::RelativeLayoutParameter::create();
        storeButtonLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        storeButtonLayout->setMargin(ui::Margin(0, 0, 0, 0));
        storeButton->setLayoutParameter(storeButtonLayout);
        addChild(storeButton);
        
        storeButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onShowStoreTapped) {
                onShowStoreTapped();
            }
        });
        
        return true;
    }
}
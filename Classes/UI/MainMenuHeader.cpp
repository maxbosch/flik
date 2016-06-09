//
//  MainMenuHeader.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/6/16.
//
//

#include "MainMenuHeader.h"
#include "Literals.h"

USING_NS_CC;

using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    bool MainMenuHeader::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setBackGroundColor(Color3B::BLACK);
        setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        auto logoButton = ui::Button::create("flik_small.png");
        //logoButton->setContentSize(Size(147, 42));
        auto logoButtonLayout = ui::RelativeLayoutParameter::create();
        logoButtonLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        logoButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        logoButton->setLayoutParameter(logoButtonLayout);
        addChild(logoButton);
        
        auto achievementsButton = ui::Button::create("achievements_home.png");
        auto achievementsButtonLayout = ui::RelativeLayoutParameter::create();
        achievementsButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        achievementsButtonLayout->setMargin(ui::Margin(12.5_dp, 20.0_dp, 0, 0));
        achievementsButton->setLayoutParameter(achievementsButtonLayout);
        addChild(achievementsButton);
        
        auto settingsButton = ui::Button::create("settings_home.png");
        auto settingsButtonLayout = ui::RelativeLayoutParameter::create();
        settingsButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        settingsButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 12.5_dp, 0));
        settingsButton->setLayoutParameter(settingsButtonLayout);
        addChild(settingsButton);
                
        return true;
    }
}
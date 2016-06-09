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
            button->setTitleText(title);
            button->setTitleFontName(kDefaultFont);
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
        
        auto levelsButton = createButton("pink_button_fill.png", "Levels", GameModeType::Levels);
        auto levelsButtonLayout = ui::RelativeLayoutParameter::create();
        levelsButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        levelsButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        levelsButton->setLayoutParameter(levelsButtonLayout);
        innerContainer->addChild(levelsButton);
        
        auto timedButton = createButton("timer_home.png", "Timed", GameModeType::Timed);
        auto timedButtonLayout = ui::RelativeLayoutParameter::create();
        timedButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        timedButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 0));
        timedButton->setLayoutParameter(timedButtonLayout);
        innerContainer->addChild(timedButton);
        
        auto unlimitedButton = createButton("unlimited_home.png", "Unlimited", GameModeType::Unlimited);
        auto unlimitedButtonLayout = ui::RelativeLayoutParameter::create();
        unlimitedButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        unlimitedButton->setLayoutParameter(unlimitedButtonLayout);
        innerContainer->addChild(unlimitedButton);
        
        return true;
    }
}
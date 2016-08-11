//
//  PauseOverlayWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#include "PauseOverlayWidget.h"
#include "PauseButtonsWidget.h"
#include "Literals.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool PauseOverlayWidget::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.8 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto pauseButtons = PauseButtonsWidget::create();
        auto pauseButtonsLayout = ui::RelativeLayoutParameter::create();
        pauseButtonsLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        pauseButtons->setLayoutParameter(pauseButtonsLayout);
        pauseButtons->onRestartTapped = [this]() {
            if (onRestartTapped) {
                onRestartTapped();
            }
        };
        pauseButtons->onSettingsTapped = [this]() {
            if (onSettingsTapped) {
                onSettingsTapped();
            }
        };
        pauseButtons->onAchievementsTapped = [this]() {
            if (onAchievementsTapped) {
                onAchievementsTapped();
            }
        };
        pauseButtons->onHomeTapped = [this]() {
            if (onHomeTapped) {
                onHomeTapped();
            }
        };
        addChild(pauseButtons);
        
        auto restartButton = ui::Button::create("arrow_up.png");
        auto restartButtonLayout = ui::RelativeLayoutParameter::create();
        restartButtonLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        restartButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        restartButton->setLayoutParameter(restartButtonLayout);
        restartButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onBackTapped) {
                onBackTapped();
            }
        });
        addChild(restartButton);
        
        return true;
    }
}

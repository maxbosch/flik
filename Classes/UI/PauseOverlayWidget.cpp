//
//  PauseOverlayWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#include "PauseOverlayWidget.h"
#include "PauseButtonsWidget.h"

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
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.7 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto pauseButtons = PauseButtonsWidget::create();
        auto pauseButtonsLayout = ui::RelativeLayoutParameter::create();
        pauseButtonsLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        pauseButtons->setLayoutParameter(pauseButtonsLayout);
        pauseButtons->onBackTapped = [this]() {
            if (onBackTapped) {
                onBackTapped();
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
        
        return true;
    }
}

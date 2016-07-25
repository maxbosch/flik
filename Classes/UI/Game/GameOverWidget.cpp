//
//  GameOverWidget.cpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#include "GameOverWidget.h"
#include "Literals.h"
#include "Styles.h"
#include "LocalizedString.h"

USING_NS_CC;

using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    bool GameOverWidget::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto gameOverTextLabel = Fonts::createLocalizedText(LocalizedString::getString("game_over"), 20.0_dp);
        gameOverTextLabel->setTextColor(Color4B(0, 0, 0, 255));
        auto gameOverTextLabelLayout = ui::RelativeLayoutParameter::create();
        gameOverTextLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        gameOverTextLabelLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        gameOverTextLabel->setLayoutParameter(gameOverTextLabelLayout);
        addChild(gameOverTextLabel);
        
        auto restartButton = ui::Button::create();
        restartButton->setContentSize(Size(200.0_dp, 30.0_dp));
        restartButton->ignoreContentAdaptWithSize(false);
        restartButton->setTitleText(LocalizedString::getString("restart"));
        restartButton->setTitleFontName(Fonts::getFontForString(restartButton->getTitleText()));
        restartButton->setTitleFontSize(16.0_dp);
        restartButton->setTitleColor(Color3B(0, 0, 0));
        restartButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (onRestartClick) {
                    onRestartClick();
                }
            }
        });
        auto buttonColor = LayerColor::create(Color4B(200, 200, 200, 255), 200.0_dp, 30.0_dp);
        buttonColor->setLocalZOrder(-1);
        restartButton->addChild(buttonColor);
        
        auto restartButtonLayout = ui::RelativeLayoutParameter::create();
        restartButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        restartButtonLayout->setMargin(ui::Margin(0, 0, 0, 20.0_dp));
        restartButton->setLayoutParameter(restartButtonLayout);
        addChild(restartButton);
        
        return true;
    }
}
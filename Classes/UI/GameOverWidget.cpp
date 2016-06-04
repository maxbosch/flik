//
//  GameOverWidget.cpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#include "GameOverWidget.h"

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
        
        auto gameOverTextLabel = ui::Text::create("Game Over", "HelveticaNeue", 20);
        gameOverTextLabel->setTextColor(Color4B(0, 0, 0, 255));
        auto gameOverTextLabelLayout = ui::RelativeLayoutParameter::create();
        gameOverTextLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        gameOverTextLabelLayout->setMargin(ui::Margin(0, 20, 0, 0));
        gameOverTextLabel->setLayoutParameter(gameOverTextLabelLayout);
        addChild(gameOverTextLabel);
        
        auto restartButton = ui::Button::create();
        restartButton->setContentSize(Size(200, 30));
        restartButton->ignoreContentAdaptWithSize(false);
        restartButton->setTitleText("Restart");
        restartButton->setTitleFontName("HelveticaNeue");
        restartButton->setTitleFontSize(16);
        restartButton->setTitleColor(Color3B(0, 0, 0));
        restartButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (onRestartClick) {
                    onRestartClick();
                }
            }
        });
        auto buttonColor = LayerColor::create(Color4B(200, 200, 200, 255), 200, 30);
        buttonColor->setLocalZOrder(-1);
        restartButton->addChild(buttonColor);
        
        auto restartButtonLayout = ui::RelativeLayoutParameter::create();
        restartButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        restartButtonLayout->setMargin(ui::Margin(0, 0, 0, 20));
        restartButton->setLayoutParameter(restartButtonLayout);
        addChild(restartButton);
        
        return true;
    }
}
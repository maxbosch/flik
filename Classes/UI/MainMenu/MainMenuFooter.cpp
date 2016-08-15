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
#include "Fonts.h"
#include "Util.h"
#include "Styles.h"
#include "LocalizedString.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool MainMenuFooter::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
//        auto timestopPowerUpButton = PowerUpButton::create(PowerUpType::Timestop);
//        auto timestopPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
//        timestopPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
//        timestopPowerUpButtonLayout->setMargin(ui::Margin(30.0_dp, 14.0_dp, 0, 0));
//        timestopPowerUpButton->setLayoutParameter(timestopPowerUpButtonLayout);
//        addChild(timestopPowerUpButton);
//        
//        auto targetPowerUpButton = PowerUpButton::create(PowerUpType::Target);
//        auto targetPowerUpButtonLayout = ui::RelativeLayoutParameter::create();
//        targetPowerUpButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
//        targetPowerUpButtonLayout->setMargin(ui::Margin(0, 14.0_dp, 30.0_dp, 0));
//        targetPowerUpButton->setLayoutParameter(targetPowerUpButtonLayout);
//        addChild(targetPowerUpButton);
        
        auto storeButtonContainer = ui::HBox::create();
        storeButtonContainer->setAnchorPoint(Vec2(0.5, 0.5));
        auto storeButtonContainerLayout = ui::RelativeLayoutParameter::create();
        storeButtonContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        storeButtonContainerLayout->setMargin(ui::Margin(0, 0, 0, 0));
        storeButtonContainer->setLayoutParameter(storeButtonContainerLayout);
        storeButtonContainer->setTouchEnabled(true);
        addChild(storeButtonContainer);
        
        auto storeButton = ui::Button::create();
        Fonts::updateLocalizedText(storeButton, LocalizedString::getString("title_store"));
        storeButton->setTitleColor(kGoldColor);
        storeButton->setTitleFontName(Fonts::getFontForString(storeButton->getTitleText()));
        storeButton->setTitleFontSize(25.0_dp);
        storeButton->setTouchEnabled(false);
        auto storeButtonLayout = ui::LinearLayoutParameter::create();
        storeButtonLayout->setGravity(LinearGravity::CENTER_VERTICAL);
        storeButton->setLayoutParameter(storeButtonLayout);
        storeButtonContainer->addChild(storeButton);
        
        auto image = ui::ImageView::create("store.png");
        image->setScale(0.6);
        auto imageLayout = ui::LinearLayoutParameter::create();
        imageLayout->setMargin(ui::Margin(0, -7.0_dp, 0, 0));
        imageLayout->setGravity(LinearGravity::TOP);
        image->setLayoutParameter(imageLayout);
        storeButtonContainer->addChild(image);
        
        storeButtonContainer->setContentSize(Size(storeButton->getContentSize().width + (image->getContentSize().width * 0.6),
                                                  storeButton->getContentSize().height));
        
        storeButtonContainer->addTouchEventListener([this, storeButtonContainer](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::BEGAN) {
                storeButtonContainer->setScale(1.1);
            } else if ((type == TouchEventType::ENDED || type == TouchEventType::CANCELED)) {
                if (type == TouchEventType::ENDED && onShowStoreTapped) {
                    onShowStoreTapped();
                }
                
                storeButtonContainer->setScale(1.0);
            }
        });
        
        return true;
    }
}
//
//  BonusBar.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/12/16.
//
//

#include "BonusBar.h"
#include "Literals.h"
#include "Util.h"
#include "Enums.h"

USING_NS_CC;

namespace flik
{
    static const int kMaxBonuses = 3;
    
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    BonusBar* BonusBar::create(const cocos2d::Size& size)
    {
        return createWithParams<BonusBar>(size);
    }
    
    bool BonusBar::init(const cocos2d::Size& size)
    {
        if (!HBox::init())
        {
            return false;
        }

        setContentSize(Size(size.width, size.height));
        
        for (int i = 0; i < kMaxBonuses; i++) {
            auto buttonContainer = ui::RelativeBox::create(Size(size.width / kMaxBonuses, 47.5_dp));
            auto buttonContainerLayout = ui::LinearLayoutParameter::create();
            buttonContainerLayout->setGravity(LinearGravity::CENTER_VERTICAL);
            buttonContainer->setLayoutParameter(buttonContainerLayout);
            addChild(buttonContainer);
            
            auto button = ui::Button::create("powerup_choose_button.png");
            auto buttonLayout = ui::RelativeLayoutParameter::create();
            buttonLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
            button->setLayoutParameter(buttonLayout);
            buttonContainer->addChild(button);
            mButtons.push_back(button);
            
            button->addTouchEventListener([this, i](Ref* sender, TouchEventType type) {
                if (type == TouchEventType::ENDED && onBonusTapped) {
                    auto button = dynamic_cast<ui::Button*>(sender);
                    if (button->getTag() >= 0) {
                        onBonusTapped(static_cast<BonusType>(button->getTag()));
                        button->setEnabled(false);
                    } else {
                        onAddBonusTapped();
                    }
                }
            });
        }
        
        return true;
    }
    
    void BonusBar::reset()
    {
        for (int i = 0; i < kMaxBonuses; i++) {
            auto button = mButtons[i];
            button->setEnabled(true);
        }
    }
    
    void BonusBar::setBonuses(const std::vector<BonusType>& bonuses)
    {
        for (int i = 0; i < kMaxBonuses; i++) {
            auto button = mButtons[i];
            if (i < bonuses.size()) {
                // This is where we would set the bonus-specific icon
                button->loadTextureNormal("powerup_" + kBonusStrings[bonuses[i]] + ".png");
                button->setTag(static_cast<int>(bonuses[i]));
            } else {
                button->loadTextureNormal("powerup_choose_button.png");
                button->setTag(-1);
            }
        }
        
        mBonuses = bonuses;
    }
    
    void BonusBar::disableBonus(int bonus)
    {
        mButtons[bonus]->setEnabled(false);
    }
}

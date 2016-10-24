//
//  ChoosePowerupRowWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/21/16.
//
//

#include "ChoosePowerupRowWidget.h"
#include "ui/CocosGUI.h"
#include "Literals.h"
#include "Styles.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "Player.h"

#include <boost/algorithm/string/case_conv.hpp>

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    float ChoosePowerupRowWidget::getCellHeight()
    {
        return 130.0_dp;
    }
    
    bool ChoosePowerupRowWidget::init()
    {
        if (!TableViewCell::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        auto container = ui::RelativeBox::create(Size(uiSize.width, getCellHeight()));
        addChild(container);
        
        auto image = ui::ImageView::create("powerup_ghost_white.png");
        auto imageLayout = ui::RelativeLayoutParameter::create();
        imageLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        imageLayout->setRelativeName("image");
        imageLayout->setMargin(ui::Margin(35.0_dp, 0, 0, 0));
        image->setLayoutParameter(imageLayout);
        container->addChild(image);
        mImage = image;
        
        auto countLabel = Fonts::createLocalizedText("x0", 15.0_dp);
        countLabel->setColor(Color3B::WHITE);
        auto countLabelLayout = ui::RelativeLayoutParameter::create();
        countLabelLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN);
        countLabelLayout->setRelativeToWidgetName("image");
        countLabelLayout->setMargin(ui::Margin(3.0_dp, 20.0_dp, 0, 0));
        countLabel->setLayoutParameter(countLabelLayout);
        container->addChild(countLabel);
        mCountLabel = countLabel;
        
        auto addButton = ui::Button::create("powerup_add_button.png");
        //Fonts::updateLocalizedText(addButton, boost::to_upper_copy(LocalizedString::getString("word_add")));
        addButton->setTitleColor(Color3B::WHITE);
        addButton->setTitleFontSize(15.0_dp);
        auto addButtonLayout = ui::RelativeLayoutParameter::create();
        addButtonLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_CENTER);
        addButtonLayout->setRelativeToWidgetName("image");
        addButtonLayout->setMargin(ui::Margin(50.0_dp, 0, 0, 0));
        addButton->setLayoutParameter(addButtonLayout);
        container->addChild(addButton);
        mAddButton = addButton;
        
        addButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (mCount > 0) {
                    //mSelected = !mSelected;
                    //setData(mBonusType, mSelected);
                    
                    if (onAddButtonTapped) {
                        onAddButtonTapped(mBonusType, mSelected);
                    }
                } else {
                    if (onBuyButtonTapped) {
                        onBuyButtonTapped();
                    }
                }
                
            }
        });
        
        auto nameLabel = Fonts::createLocalizedText("Ghost", 15.0_dp);
        nameLabel->setColor(Color3B::WHITE);
        auto nameLabelLayout = ui::RelativeLayoutParameter::create();
        nameLabelLayout->setRelativeToWidgetName("image");
        nameLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_LEFTALIGN);
        nameLabelLayout->setMargin(ui::Margin(0, 5.0_dp, 0, 0));
        nameLabelLayout->setRelativeName("name");
        nameLabel->setLayoutParameter(nameLabelLayout);
        container->addChild(nameLabel);
        mNameLabel = nameLabel;
        
        auto descriptionLabel = Fonts::createLocalizedText("Causes pieces to no longer collide with eachother for 10 seconds", 11.0_dp);
        descriptionLabel->setColor(Color3B::WHITE);
        descriptionLabel->setTextAreaSize(Size(290.0_dp, 40.0_dp));
        auto descriptionLabelLayout = ui::RelativeLayoutParameter::create();
        descriptionLabelLayout->setRelativeToWidgetName("name");
        descriptionLabelLayout->setAlign(RelativeAlign::LOCATION_BELOW_LEFTALIGN);
        descriptionLabelLayout->setMargin(ui::Margin(0, 5.0_dp, 0, 0));
        descriptionLabel->setLayoutParameter(descriptionLabelLayout);
        container->addChild(descriptionLabel);
        mDescriptionLabel = descriptionLabel;
        
        return true;
    }
    
    void ChoosePowerupRowWidget::setLocked(bool locked)
    {
        mAddButton->setEnabled(!locked);
    }
    
    void ChoosePowerupRowWidget::setData(BonusType type, bool selected)
    {
        mBonusType = type;
        mSelected = selected;
        
        const std::string& name = kBonusStrings[type];
        
        int bonusCount = Player::getMainPlayer()->getPowerUpCount(type);
        Fonts::updateLocalizedText(mCountLabel, StringUtils::format("x%d", bonusCount));

        if (selected) {
            mAddButton->loadTextureNormal("powerup_add_button_selected.png");
            mAddButton->setTitleText("");
            
            mImage->loadTexture("powerup_" + name + ".png");
            
            mNameLabel->setColor(kPinkColor);
            mDescriptionLabel->setColor(kPinkColor);
            mCountLabel->setColor(kPinkColor);
        } else {
            mAddButton->loadTextureNormal("powerup_add_button.png");
            //Fonts::updateLocalizedText(mAddButton, boost::to_upper_copy(LocalizedString::getString("word_add")));
            
            mImage->loadTexture("powerup_" + name + "_white.png");
            
            mNameLabel->setColor(Color3B::WHITE);
            mDescriptionLabel->setColor(Color3B::WHITE);
            mCountLabel->setColor(Color3B::WHITE);
        }
        
        Fonts::updateLocalizedText(mNameLabel, LocalizedString::getString("bonus_name_" + name));
        Fonts::updateLocalizedText(mDescriptionLabel, LocalizedString::getString("bonus_description_" + name));
        
        mCount = bonusCount;
    }
}

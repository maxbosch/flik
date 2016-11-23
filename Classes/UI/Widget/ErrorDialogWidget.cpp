//
//  ErrorDialogWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 11/22/16.
//
//

#include "ErrorDialogWidget.h"

#include "Util.h"
#include "Literals.h"
#include "Styles.h"
#include "OverlayBackgroundWidget.h"

USING_NS_CC;

namespace flik
{
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    ErrorDialogWidget* ErrorDialogWidget::create(const std::string& title, const std::string& description)
    {
        return createWithParams<ErrorDialogWidget>(title, description);
    }
    
    bool ErrorDialogWidget::init(const std::string& title, const std::string& description)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto background = OverlayBackgroundWidget::create();
        background->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED) {
                this->removeFromParent();
            }
        });
        addChild(background);
        
        auto backgroundImage = ui::Scale9Sprite::create(Rect(34.0_dp, 34.0_dp, 32.0_dp, 32.0_dp), "blue_border_9.png");
        backgroundImage->setAnchorPoint(Vec2());
        
        auto innerContainer = ui::VBox::create();
        innerContainer->addChild(backgroundImage);
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto titleLabel = Fonts::createLocalizedText(title, 21.0_dp);
        titleLabel->setTextAreaSize(Size(250.0_dp, 0));
        titleLabel->setColor(kGoldColor);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabelLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 20.0_dp));
        titleLabel->setLayoutParameter(titleLabelLayout);
        titleLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
        innerContainer->addChild(titleLabel);
        
        auto descriptionLabel = Fonts::createLocalizedText(description, 18.0_dp);
        descriptionLabel->setColor(Color3B::WHITE);
        descriptionLabel->setTextAreaSize(Size(250.0_dp, 0));
        descriptionLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
        auto descriptionLabelLayout = ui::LinearLayoutParameter::create();
        descriptionLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        descriptionLabelLayout->setMargin(ui::Margin(0, 0, 0, 30.0_dp));
        descriptionLabel->setLayoutParameter(descriptionLabelLayout);
        innerContainer->addChild(descriptionLabel);
        
        Size titleLabelSize = titleLabel->getContentSize();
        Size descriptionLabelSize = descriptionLabel->getContentSize();
        
        Size finalSize(300.0_dp, titleLabelSize.height + descriptionLabelSize.height + 80.0_dp);
        innerContainer->setContentSize(finalSize);
        backgroundImage->setContentSize(finalSize);
        
        auto exitButton = ui::Button::create("red_x_close.png");
        auto exitButtonLayout = ui::RelativeLayoutParameter::create();
        exitButtonLayout->setAlign(ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        exitButtonLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        exitButton->setLayoutParameter(exitButtonLayout);
        addChild(exitButton);
        
        exitButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED) {
                this->removeFromParent();
            }
        });
        
        return true;
    }
    
    void ErrorDialogWidget::show()
    {
        auto parent = Director::getInstance()->getRunningScene();
        parent->addChild(this);
    }
}

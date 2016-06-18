//
//  GameObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#include <boost/algorithm/string.hpp>

#include "GameObjectiveOverlay.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool GameObjectiveOverlay::init(const std::string& title)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.7 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        auto innerContainer = ui::VBox::create(Size(305.0_dp, 475.0_dp));
        innerContainer->ignoreContentAdaptWithSize(false);
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto backgroundImage = ui::Scale9Sprite::create(Rect(34.0_dp, 34.0_dp, 32.0_dp, 32.0_dp), "blue_border_9.png");
        backgroundImage->setAnchorPoint(Vec2());
        innerContainer->addChild(backgroundImage);
        
        auto titleLabel = ui::Text::create(boost::to_upper_copy(title), kDefaultFont, 18.0_dp);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 45.0_dp, 0, 45.0_dp));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        mTitleLabel = titleLabel;
    
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        
        auto border1 = ui::HBox::create(Size(210.0_dp, 3.0_dp));
        border1->setBackGroundColor(Util::getColorFromHex("2086E4"));
        border1->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout1 = ui::LinearLayoutParameter::create();
        borderLayout1->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border1->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border1);
        
        auto objectiveTextLabel = ui::Text::create("Objective", kDefaultFont, 15.0_dp);
        auto objectiveTextLabelLayout = ui::LinearLayoutParameter::create();
        objectiveTextLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        objectiveTextLabelLayout->setMargin(ui::Margin(0, 45.0_dp, 0, 20.0_dp));
        objectiveTextLabel->setLayoutParameter(objectiveTextLabelLayout);
        innerContainer->addChild(objectiveTextLabel);
        
        auto objectiveWidget = createObjectiveWidget();
        auto objectiveContainerLayout = ui::LinearLayoutParameter::create();
        objectiveContainerLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        objectiveWidget->setLayoutParameter(objectiveContainerLayout);
        innerContainer->addChild(objectiveWidget);
        
        auto border2 = ui::HBox::create(Size(210.0_dp, 3.0_dp));
        border2->setBackGroundColor(Util::getColorFromHex("2086E4"));
        border2->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        auto borderLayout2 = ui::LinearLayoutParameter::create();
        borderLayout2->setGravity(LinearGravity::CENTER_HORIZONTAL);
        border2->setLayoutParameter(borderLayout1);
        innerContainer->addChild(border2);
        
        auto startButton = ui::Button::create("pink_button_fill_large.png");
        startButton->setTitleFontName(kDefaultFont);
        startButton->setTitleFontSize(18.0_dp);
        startButton->setTitleText("START!");
        startButton->setTitleColor(Color3B::WHITE);
        auto startButtonLayout = ui::LinearLayoutParameter::create();
        startButtonLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        startButtonLayout->setMargin(ui::Margin(0, 35.0_dp, 0, 30.0_dp));
        startButton->setLayoutParameter(startButtonLayout);
        innerContainer->addChild(startButton);
        
        startButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onStartButtonTapped) {
                onStartButtonTapped();
            }
        });
        
        auto startButtonBox = startButton->getBoundingBox();
        innerContainer->forceDoLayout();
        //innerContainer->setContentSize(Size(305.0_dp, startButton->getBoundingBox().getMaxY() + 30.0_dp));
        backgroundImage->setContentSize(innerContainer->getContentSize());
        
        auto exitButton = ui::Button::create("red_x_close.png");
        auto exitButtonLayout = ui::RelativeLayoutParameter::create();
        exitButtonLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        exitButtonLayout->setMargin(ui::Margin(0, 0, 0, 20.0_dp));
        exitButton->setLayoutParameter(exitButtonLayout);
        addChild(exitButton);
        
        exitButton->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED && onExitButtonTapped) {
                onExitButtonTapped();
            }
        });
        
        return true;
    }

}

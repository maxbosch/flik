//
//  GameObjectiveOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/15/16.
//
//

#include "GameObjectiveOverlay.h"
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool GameObjectiveOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        setContentSize(Director::getInstance()->getVisibleSize());
        setBackGroundColor(Color3B(0, 0, 0));
        setOpacity(0.5);
        setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        
        auto innerContainer = ui::VBox::create(Size(305.0_dp, 478.5_dp));
        auto innerContainerLayout = ui::RelativeLayoutParameter::create();
        innerContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        innerContainer->setLayoutParameter(innerContainerLayout);
        addChild(innerContainer);
        
        auto titleLabel = ui::Text::create("", kDefaultFont, 18.0_dp);
        auto titleLabelLayout = ui::LinearLayoutParameter::create();
        titleLabelLayout->setMargin(ui::Margin(0, 45.0_dp, 0, 45.0_dp));
        titleLabelLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        titleLabel->setLayoutParameter(titleLabelLayout);
        innerContainer->addChild(titleLabel);
        mTitleLabel = titleLabel;
        
        
        auto borderLayout = ui::LinearLayoutParameter::create();
        borderLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        
        auto border1 = ui::HBox::create(Size(293.0_dp, 3.0_dp));
        border1->setBackGroundColor(Util::getColorFromHex("2086E4"));
        border1->setLayoutParameter(borderLayout->createCloneInstance());
        innerContainer->addChild(border1);
        
        return true;
    }
}

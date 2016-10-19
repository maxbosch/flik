//
//  AchievementOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/7/16.
//
//

#include "AchievementOverlay.h"
#include "Util.h"
#include "Literals.h"
#include "Styles.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "Animations.h"
#include "OverlayBackgroundWidget.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    AchievementOverlay* AchievementOverlay::create(const std::string& achievementName)
    {
        return createWithParams<AchievementOverlay>(achievementName);
    }
    
    bool AchievementOverlay::init(const std::string& achievementName)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);

        addChild(OverlayBackgroundWidget::create());
        
        auto container = ui::RelativeBox::create(uiSize);
        addChild(container);
        mContainer = container;
        
        auto achievementNameText = Fonts::createLocalizedText(LocalizedString::getString("achievement_" + achievementName), 30.0_dp);
        achievementNameText->setColor(Color3B::WHITE);
        achievementNameText->setTextAreaSize(Size(uiSize.width - 40.0_dp, 100.0_dp));
        achievementNameText->setTextHorizontalAlignment(TextHAlignment::CENTER);
        auto achievementNameTextLayout = ui::RelativeLayoutParameter::create();
        achievementNameTextLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        achievementNameTextLayout->setMargin(ui::Margin(20.0_dp, 60.0_dp, 20.0_dp, 0));
        achievementNameText->setLayoutParameter(achievementNameTextLayout);
        container->addChild(achievementNameText);
        
        auto achievementRibbon = ui::ImageView::create("success_ribbon.png");
        auto achievementRibbonLayout = ui::RelativeLayoutParameter::create();
        achievementRibbonLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        achievementRibbon->setLayoutParameter(achievementRibbonLayout);
        container->addChild(achievementRibbon);
        
        auto achievementLabel = Fonts::createLocalizedText(LocalizedString::getString("achievement_text"), 25.0_dp);
        achievementLabel->setColor(kYellowColor);
        achievementLabel->setAnchorPoint(Vec2(0.5, 0.0));
        achievementLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
        achievementLabel->setPosition(Vec2(achievementRibbon->getContentSize().width * 0.5, 157.5_dp));
        achievementRibbon->addChild(achievementLabel);
        
        auto nextButton = ui::RelativeBox::create(Size(125.0_dp, 48.0_dp));
        auto nextButtonLayout = ui::RelativeLayoutParameter::create();
        nextButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
        nextButtonLayout->setMargin(ui::Margin(0, 0, 30.0_dp, 30.0_dp));
        nextButton->setLayoutParameter(nextButtonLayout);
        container->addChild(nextButton);
        nextButton->setTouchEnabled(true);
        nextButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onNextLevelTapped) {
                onNextLevelTapped();
            }
        });
        
        auto nextButtonImage = ui::ImageView::create("next_arrow.png");
        auto nextButtonImageLayout = ui::RelativeLayoutParameter::create();
        nextButtonImageLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        nextButtonImage->setLayoutParameter(nextButtonImageLayout);
        nextButton->addChild(nextButtonImage);
        
        auto nextButtonLabel = Fonts::createLocalizedText(LocalizedString::getString("game_over_try_next"), 25.0_dp);
        nextButtonLabel->setColor(Color3B::WHITE);
        auto nextButtonLabelLayout = ui::RelativeLayoutParameter::create();
        nextButtonLabelLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
        nextButtonLabel->setLayoutParameter(nextButtonLabelLayout);
        nextButton->addChild(nextButtonLabel);
        
        return true;
    }
    
    void AchievementOverlay::animateIn()
    {
        Animations::animate(kTransitionDuration, [this](float t) {
            Mat4 transform;
            Mat4::createTranslation(Vec3(getContentSize().width * (1.0f - t), 0, 0), &transform);
            
            mContainer->setAdditionalTransform(&transform);
        }, nullptr, QuadraticEaseOutCurve);
    }
    
    void AchievementOverlay::animateOut()
    {
        Animations::animate(kTransitionDuration, [this](float t) {
            Mat4 transform;
            Mat4::createTranslation(Vec3(-getContentSize().width * t, 0, 0), &transform);
            
            mContainer->setAdditionalTransform(&transform);
        }, [this](bool finished) {
            this->removeFromParent();
        }, QuadraticEaseInCurve);
    }
}

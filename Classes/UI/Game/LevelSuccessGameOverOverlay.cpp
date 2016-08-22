//
//  LevelSuccessGameOverOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/17/16.
//
//

#include "LevelSuccessGameOverOverlay.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "Animations.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool LevelSuccessGameOverOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto overlayBackground = LayerColor::create(Color4B(0, 0, 0, 0.8 * 255), uiSize.width, uiSize.height);
        addChild(overlayBackground);
        
        // Buttons
        auto replayButton = ui::Button::create("level_success_replay.png");
        auto replayButtonLayout = ui::RelativeLayoutParameter::create();
        replayButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        replayButtonLayout->setMargin(ui::Margin(45.0_dp, 60.0_dp, 0, 0));
        replayButton->setLayoutParameter(replayButtonLayout);
        addChild(replayButton);
        replayButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onRestartTapped) {
                onRestartTapped();
            }
        });
        
        auto listButton = ui::Button::create("level_success_list.png");
        auto listButtonLayout = ui::RelativeLayoutParameter::create();
        listButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        listButtonLayout->setMargin(ui::Margin(0, 60.0_dp, 45.0_dp, 0));
        listButton->setLayoutParameter(listButtonLayout);
        addChild(listButton);
        listButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onShowLevelListTapped) {
                onShowLevelListTapped();
            }
        });
        
        auto nextButton = ui::RelativeBox::create(Size(125.0_dp, 48.0_dp));
        auto nextButtonLayout = ui::RelativeLayoutParameter::create();
        nextButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
        nextButtonLayout->setMargin(ui::Margin(0, 0, 30.0_dp, 30.0_dp));
        nextButton->setLayoutParameter(nextButtonLayout);
        addChild(nextButton);
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
        
        // Middle Container
        auto middleContainer = ui::RelativeBox::create(Size(305.0_dp, 271.0_dp));
        auto middleContainerLayout = ui::RelativeLayoutParameter::create();
        middleContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        middleContainer->setLayoutParameter(middleContainerLayout);
        addChild(middleContainer);
        
        auto starsContainer = ui::RelativeBox::create(Size(305.0_dp, 195.5_dp));
        starsContainer->setBackGroundImage("level_success_star_box.png");
        auto starsContainerLayout = ui::RelativeLayoutParameter::create();
        starsContainerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        starsContainerLayout->setMargin(ui::Margin(0, 75.0_dp, 0, 0));
        starsContainer->setLayoutParameter(starsContainerLayout);
        middleContainer->addChild(starsContainer);
        
        for (int i = 0; i < 3; i++) {
            auto starEmpty = ui::ImageView::create("star_large_empty.png");
            auto starEmptyLayout = ui::RelativeLayoutParameter::create();
            starEmptyLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
            starEmptyLayout->setMargin(ui::Margin(67.0_dp + (i * 65.0_dp), 0, 0, 47.5_dp));
            starEmpty->setLayoutParameter(starEmptyLayout);
            starsContainer->addChild(starEmpty);
            
            auto starFull = ui::ImageView::create("star_large.png");
            starFull->setScale(0.0f);
            auto starFullLayout = ui::RelativeLayoutParameter::create();
            starFullLayout->setAlign(RelativeAlign::PARENT_LEFT_BOTTOM);
            starFullLayout->setMargin(ui::Margin(67.0_dp + (i * 65.0_dp), 0, 0, 47.5_dp));
            starFull->setLayoutParameter(starFullLayout);
            starsContainer->addChild(starFull);
            mStarWidgets.push_back(starFull);
        }
        
        auto pointsBubble = ui::RelativeBox::create(Size(152.5_dp, 152.5_dp));
        pointsBubble->setBackGroundImage("game_over_points_container.png");
        auto pointsBubbleLayout = ui::RelativeLayoutParameter::create();
        pointsBubbleLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        pointsBubble->setLayoutParameter(pointsBubbleLayout);
        middleContainer->addChild(pointsBubble);
        
        auto pointsLabel = Fonts::createLocalizedText("+123", 48.0_dp);
        pointsLabel->setTextColor(Color4B(kStarColor));
        auto pointsLabelLayout = ui::RelativeLayoutParameter::create();
        pointsLabelLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        pointsLabel->setLayoutParameter(pointsLabelLayout);
        pointsBubble->addChild(pointsLabel);
        mPointsLabel = pointsLabel;
        
        return true;
    }
    
    void LevelSuccessGameOverOverlay::show(int score, int pointsEarned)
    {
        animateStar(score);
        animatePoints(pointsEarned);
    }
    
    void LevelSuccessGameOverOverlay::animateStar(int maxStar, int star)
    {
        if (star <= maxStar) {
            scheduleOnce([this, star, maxStar](float t) {
                Animations::animate(0.5, [this, star, maxStar](float t) {
                    auto widget = mStarWidgets[star - 1];
                    widget->setScale(t);
                }, [this, star, maxStar](bool complete) {
                    animateStar(maxStar, star + 1);
                }, OvershootCurve);
            }, 0.3, "star_animation_delay");
        }
    }
    
    void LevelSuccessGameOverOverlay::animatePoints(int points)
    {
        mPointsLabel->setString("+0");
        
        scheduleOnce([this, points](float t) {
            float duration = ((float)points / 10.0f) * 0.1;
            Animations::animate(duration, [this, points](float t) {
                int pointsAdjusted = (t * points);
                mPointsLabel->setString("+" + boost::lexical_cast<std::string>(pointsAdjusted));
            }, [this, points](bool complete) {
                mPointsLabel->setString("+" + boost::lexical_cast<std::string>(points));
            }, OvershootCurve);
        }, 0.3, "points_animation_delay");
    }
}

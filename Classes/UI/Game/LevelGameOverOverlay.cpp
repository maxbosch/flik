//
//  LevelSuccessGameOverOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/17/16.
//
//

#include "LevelGameOverOverlay.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "Animations.h"
#include "OverlayBackgroundWidget.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    bool LevelGameOverOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        addChild(OverlayBackgroundWidget::create());
        
        // Buttons
        auto replayButton = ui::Button::create("game_over_replay.png");
        auto replayButtonLayout = ui::RelativeLayoutParameter::create();
        replayButtonLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        replayButtonLayout->setMargin(ui::Margin(35.0_dp, 60.0_dp, 0, 0));
        replayButtonLayout->setRelativeName("replay_button");
        replayButton->setLayoutParameter(replayButtonLayout);
        addChild(replayButton);
        replayButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onRestartTapped) {
                onRestartTapped();
            }
        });
        
        auto replayText = Fonts::createLocalizedText(LocalizedString::getString("game_over_play_again"), 25.0_dp);
        replayText->setColor(Color3B::WHITE);
        auto replayTextLayout = ui::RelativeLayoutParameter::create();
        replayTextLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_CENTER);
        replayTextLayout->setMargin(ui::Margin(15.0_dp, 0, 0, 0));
        replayTextLayout->setRelativeToWidgetName("replay_button");
        replayText->setLayoutParameter(replayTextLayout);
        addChild(replayText);
        replayText->setTouchEnabled(true);
        replayText->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
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
        
        auto contentContainer = ui::RelativeBox::create(uiSize);
        auto contentContainerLayout = ui::RelativeLayoutParameter::create();
        contentContainerLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        contentContainer->setLayoutParameter(contentContainerLayout);
        addChild(contentContainer);
        mContentContainer = contentContainer;
        
        return true;
    }
    
    void LevelGameOverOverlay::show(int level, bool success, int score, int pointsEarned, bool hasNext)
    {
        mContentContainer->removeAllChildren();
        
        if (success) {
            createSuccessWidget(level, score, pointsEarned, hasNext);
            animateStar(score);
            //animatePoints(pointsEarned);
        } else {
            createFailureWidget(level);
        }
    }
    
    void LevelGameOverOverlay::animateStar(int maxStar, int star)
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
    
    void LevelGameOverOverlay::animatePoints(int points)
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
    
    void LevelGameOverOverlay::createSuccessWidget(int level, int score, int pointsEarned, bool hasNext)
    {
        if (hasNext) {
            auto nextButton = ui::RelativeBox::create(Size(125.0_dp, 48.0_dp));
            auto nextButtonLayout = ui::RelativeLayoutParameter::create();
            nextButtonLayout->setAlign(RelativeAlign::PARENT_RIGHT_BOTTOM);
            nextButtonLayout->setMargin(ui::Margin(0, 0, 30.0_dp, 30.0_dp));
            nextButton->setLayoutParameter(nextButtonLayout);
            mContentContainer->addChild(nextButton);
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
        }
        // Middle Container
        auto levelCompleteLabel = Fonts::createLocalizedText(LocalizedString::getString("game_over_level_complete", level + 1), 30.0_dp);
        levelCompleteLabel->setColor(kYellowColor);
        auto levelCompleteLabelLayout = ui::RelativeLayoutParameter::create();
        levelCompleteLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        levelCompleteLabelLayout->setRelativeName("level_complete");
        levelCompleteLabelLayout->setMargin(ui::Margin(0, 175.0_dp, 0, 0));
        levelCompleteLabel->setLayoutParameter(levelCompleteLabelLayout);
        mContentContainer->addChild(levelCompleteLabel);
        
        auto middleContainer = ui::RelativeBox::create(Size(305.0_dp, 270.0_dp));
        auto middleContainerLayout = ui::RelativeLayoutParameter::create();
        middleContainerLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        middleContainerLayout->setRelativeToWidgetName("level_complete");
        middleContainerLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        middleContainer->setLayoutParameter(middleContainerLayout);
        mContentContainer->addChild(middleContainer);
        
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
            starEmptyLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
            starEmptyLayout->setMargin(ui::Margin(67.0_dp + (i * 65.0_dp), 0, 0, 47.5_dp));
            starEmpty->setLayoutParameter(starEmptyLayout);
            starsContainer->addChild(starEmpty);
            
            auto starFull = ui::ImageView::create("star_large.png");
            starFull->setScale(0.0f);
            auto starFullLayout = ui::RelativeLayoutParameter::create();
            starFullLayout->setAlign(RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
            starFullLayout->setMargin(ui::Margin(67.0_dp + (i * 65.0_dp), 0, 0, 47.5_dp));
            starFull->setLayoutParameter(starFullLayout);
            starsContainer->addChild(starFull);
            mStarWidgets.push_back(starFull);
        }
    }
    
    void LevelGameOverOverlay::createFailureWidget(int level)
    {
        auto levelCompleteLabel = Fonts::createLocalizedText(LocalizedString::getString("game_over_level_failed", level + 1), 30.0_dp);
        levelCompleteLabel->setColor(kPinkColor);
        auto levelCompleteLabelLayout = ui::RelativeLayoutParameter::create();
        levelCompleteLabelLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        levelCompleteLabelLayout->setRelativeName("level_failed");
        levelCompleteLabelLayout->setMargin(ui::Margin(0, 200.0_dp, 0, 0));
        levelCompleteLabel->setLayoutParameter(levelCompleteLabelLayout);
        mContentContainer->addChild(levelCompleteLabel);
        
        auto image = ui::ImageView::create("game_over_fail.png");
        auto imageLayout = ui::RelativeLayoutParameter::create();
        imageLayout->setAlign(RelativeAlign::LOCATION_BELOW_CENTER);
        imageLayout->setRelativeToWidgetName("level_failed");
        imageLayout->setMargin(ui::Margin(0, 20.0_dp, 0, 0));
        image->setLayoutParameter(imageLayout);
        mContentContainer->addChild(image);
        
        
    }
}

//
//  DefaultGameOverOverlay.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/18/16.
//
//

#include <boost/lexical_cast.hpp>

#include "DefaultGameOverOverlay.h"
#include "Styles.h"
#include "Literals.h"
#include "ScoreWidget.h"
#include "Fonts.h"
#include "LocalizedString.h"
#include "OverlayBackgroundWidget.h"
#include "Analytics.h"
#include "MainGameScene.h"
#include "GameMode.h"
#include "Enums.h"

USING_NS_CC;

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    using LinearGravity = ui::LinearLayoutParameter::LinearGravity;
    
    bool DefaultGameOverOverlay::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
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
        
        auto listButton = ui::Button::create("game_over_home.png");
        auto listButtonLayout = ui::RelativeLayoutParameter::create();
        listButtonLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        listButtonLayout->setMargin(ui::Margin(0, 60.0_dp, 35.0_dp, 0));
        listButton->setLayoutParameter(listButtonLayout);
        addChild(listButton);
        listButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED && onHomeTapped) {
                onHomeTapped();
            }
        });
        
        auto contentContainer = ui::VBox::create(Size(uiSize.width, uiSize.height - 190.0_dp));
        auto contentContainerLayout = ui::RelativeLayoutParameter::create();
        contentContainerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        contentContainerLayout->setMargin(ui::Margin(0, 190.0_dp, 0, 0));
        contentContainer->setLayoutParameter(contentContainerLayout);
        addChild(contentContainer);
        mContentContainer = contentContainer;
        
        return true;
    }
    
    void DefaultGameOverOverlay::show(int gameScore, int topScore)
    {
        mContentContainer->removeAllChildren();
        
        if (gameScore > topScore) {
            createNewTopScoreWidget(gameScore, topScore);
        } else {
            createDefaulteWidget(gameScore, topScore);
        }
        
        auto gameScene = dynamic_cast<MainGameScene*>(Director::getInstance()->getRunningScene());
        if (gameScene) {
            PTree attributes;
            attributes.add("mode", kGameModeStrings[gameScene->getGameMode()->getGameModeType()]);
            attributes.add("score", gameScore);
            attributes.add("rating", 0);
            attributes.add("new_high_score", (int)(gameScore > topScore));
            Analytics::logEvent("game_end", attributes);
        }
    }
    
    void DefaultGameOverOverlay::createDefaulteWidget(int gameScore, int topScore)
    {
        auto image = ui::ImageView::create("game_over_fail.png");
        auto imageLayout = ui::LinearLayoutParameter::create();
        imageLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        imageLayout->setMargin(ui::Margin(0, 15.0_dp, 0, 0));
        image->setLayoutParameter(imageLayout);
        mContentContainer->addChild(image);
        
        auto newScoreCopy = Fonts::createLocalizedText(LocalizedString::getString("game_over_your_score"), 25.0_dp);
        newScoreCopy->setColor(kPinkColor);
        auto newScoreCopyLayout = ui::LinearLayoutParameter::create();
        newScoreCopyLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        newScoreCopyLayout->setMargin(ui::Margin(0, 25.0_dp, 0, 0));
        newScoreCopy->setLayoutParameter(newScoreCopyLayout);
        mContentContainer->addChild(newScoreCopy);
        
        auto newScoreValue = Fonts::createLocalizedText(boost::lexical_cast<std::string>(gameScore), 36.0_dp);
        newScoreValue->setColor(kPinkColor);
        auto newScoreValueLayout = ui::LinearLayoutParameter::create();
        newScoreValueLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        newScoreValueLayout->setMargin(ui::Margin(0, 10.0_dp, 0, 0));
        newScoreValue->setLayoutParameter(newScoreValueLayout);
        mContentContainer->addChild(newScoreValue);
        
        auto oldScoreCopy = Fonts::createLocalizedText(LocalizedString::getString("game_over_high_score"), 18.0_dp);
        oldScoreCopy->setColor(kOrangeColor);
        auto oldScoreCopyLayout = ui::LinearLayoutParameter::create();
        oldScoreCopyLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        oldScoreCopyLayout->setMargin(ui::Margin(0, 130.0_dp, 0, 0));
        oldScoreCopy->setLayoutParameter(oldScoreCopyLayout);
        mContentContainer->addChild(oldScoreCopy);
        
        auto oldScoreValue = Fonts::createLocalizedText(boost::lexical_cast<std::string>(topScore), 25.0_dp);
        oldScoreValue->setColor(kOrangeColor);
        auto oldScoreValueLayout = ui::LinearLayoutParameter::create();
        oldScoreValueLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        oldScoreValueLayout->setMargin(ui::Margin(0, 8.0_dp, 0, 0));
        oldScoreValue->setLayoutParameter(oldScoreValueLayout);
        mContentContainer->addChild(oldScoreValue);
    }
    
    void DefaultGameOverOverlay::createNewTopScoreWidget(int gameScore, int topScore)
    {
        auto newScoreCopy = Fonts::createLocalizedText(LocalizedString::getString("game_over_new_high_score"), 25.0_dp);
        newScoreCopy->setColor(kStarColor);
        auto newScoreCopyLayout = ui::LinearLayoutParameter::create();
        newScoreCopyLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        newScoreCopy->setLayoutParameter(newScoreCopyLayout);
        mContentContainer->addChild(newScoreCopy);
        
        auto newScoreValue = Fonts::createLocalizedText(boost::lexical_cast<std::string>(gameScore), 36.0_dp);
        newScoreValue->setColor(kStarColor);
        auto newScoreValueLayout = ui::LinearLayoutParameter::create();
        newScoreValueLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        newScoreValueLayout->setMargin(ui::Margin(0, 15.0_dp, 0, 0));
        newScoreValue->setLayoutParameter(newScoreValueLayout);
        mContentContainer->addChild(newScoreValue);
        
        auto trophyImage = ui::ImageView::create("trophy.png");
        auto trophyImageLayout = ui::LinearLayoutParameter::create();
        trophyImageLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        trophyImageLayout->setMargin(ui::Margin(0, 15.0_dp, 0, 0));
        trophyImage->setLayoutParameter(trophyImageLayout);
        mContentContainer->addChild(trophyImage);
        
        auto oldScoreCopy = Fonts::createLocalizedText(LocalizedString::getString("game_over_previous_best"), 18.0_dp);
        oldScoreCopy->setColor(kOrangeColor);
        auto oldScoreCopyLayout = ui::LinearLayoutParameter::create();
        oldScoreCopyLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        oldScoreCopyLayout->setMargin(ui::Margin(0, 54.0_dp, 0, 0));
        oldScoreCopy->setLayoutParameter(oldScoreCopyLayout);
        mContentContainer->addChild(oldScoreCopy);
        
        auto oldScoreValue = Fonts::createLocalizedText(boost::lexical_cast<std::string>(topScore), 25.0_dp);
        oldScoreValue->setColor(kOrangeColor);
        auto oldScoreValueLayout = ui::LinearLayoutParameter::create();
        oldScoreValueLayout->setGravity(LinearGravity::CENTER_HORIZONTAL);
        oldScoreValueLayout->setMargin(ui::Margin(0, 8.0_dp, 0, 0));
        oldScoreValue->setLayoutParameter(oldScoreValueLayout);
        mContentContainer->addChild(oldScoreValue);
        
    }
}

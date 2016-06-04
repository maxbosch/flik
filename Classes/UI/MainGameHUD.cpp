//
//  MainGameHUD.cpp
//  Fling
//
//  Created by Adam Eskreis on 6/1/16.
//
//

#include "MainGameHUD.h"
#include "GameOverWidget.h"
#include "MainGameScene.h"
#include "Player.h"
#include "GameMode.h"
#include "Events.h"

#include <boost/lexical_cast.hpp>

USING_NS_CC;

using RelativeAlign = cocos2d::ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    bool MainGameHUD::init()
    {
        if (!GameHUD::init())
        {
            return false;
        }
        
        this->setTouchEnabled(false);
        this->setLayoutComponentEnabled(true);
        
        auto uiSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        
        auto scoreValueLabel = ui::Text::create("0", "HelveticaNeue", 16);
        scoreValueLabel->setTextColor(Color4B(255, 255, 255, 255));
        addChild(scoreValueLabel);
        auto scoreValueLabelLayout = ui::RelativeLayoutParameter::create();
        scoreValueLabelLayout->setRelativeName("score_value_label");
        scoreValueLabelLayout->setAlign(RelativeAlign::PARENT_TOP_RIGHT);
        scoreValueLabelLayout->setMargin(ui::Margin(0, 20, 20, 0));
        scoreValueLabel->setLayoutParameter(scoreValueLabelLayout);
        mScoreValueLabel = scoreValueLabel;
        
        auto scoreLabel = ui::Text::create("Score", "HelveticaNeue", 16);
        scoreLabel->setTextColor(Color4B(255, 255, 255, 255));
        addChild(scoreLabel);
        auto scoreLabelLayout = ui::RelativeLayoutParameter::create();
        scoreLabelLayout->setRelativeToWidgetName("score_value_label");
        scoreLabelLayout->setAlign(RelativeAlign::LOCATION_LEFT_OF_TOPALIGN);
        scoreLabelLayout->setMargin(ui::Margin(0, 0, 10, 0));
        scoreLabel->setLayoutParameter(scoreLabelLayout);
        
        auto topScoreValueLabel = ui::Text::create("0", "HelveticaNeue", 16);
        topScoreValueLabel->setTextColor(Color4B(255, 255, 255, 255));
        addChild(topScoreValueLabel);
        auto topScoreValueLabelLayout = ui::RelativeLayoutParameter::create();
        topScoreValueLabelLayout->setRelativeToWidgetName("top_score_label");
        topScoreValueLabelLayout->setAlign(RelativeAlign::LOCATION_RIGHT_OF_TOPALIGN);
        topScoreValueLabelLayout->setMargin(ui::Margin(10, 0, 0, 0));
        topScoreValueLabel->setLayoutParameter(topScoreValueLabelLayout);
        mTopScoreValueLabel = topScoreValueLabel;
        
        auto topScoreLabel = ui::Text::create("Top Score", "HelveticaNeue", 16);
        topScoreLabel->setTextColor(Color4B(255, 255, 255, 255));
        addChild(topScoreLabel);
        auto topScoreLabelLayout = ui::RelativeLayoutParameter::create();
        topScoreLabelLayout->setRelativeName("top_score_label");
        topScoreLabelLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        topScoreLabelLayout->setMargin(ui::Margin(20, 20, 0, 0));
        topScoreLabel->setLayoutParameter(topScoreLabelLayout);
        
        mGameOverScreen = GameOverWidget::create();
        mGameOverScreen->setContentSize(Size(uiSize.width - 20, 120));
        mGameOverScreen->setBackGroundColor(Color3B(225, 225, 225));
        mGameOverScreen->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        mGameOverScreen->onRestartClick = [this]() {
            if (getGameScene()) {
                getGameScene()->requestRestart();
            }
        };
        auto gameOverScreenLayout = ui::RelativeLayoutParameter::create();
        gameOverScreenLayout->setMargin(ui::Margin(10, 100, 10, 0));
        gameOverScreenLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        mGameOverScreen->setLayoutParameter(gameOverScreenLayout);
        addChild(mGameOverScreen);
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [](EventCustom* event) {
            Player::getMainPlayer()->addScore(1);
            
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    void MainGameHUD::update(float time)
    {
        RelativeBox::update(time);
        
        mScoreValueLabel->setString(boost::lexical_cast<std::string>(Player::getMainPlayer()->getCurrentScore()));
        mTopScoreValueLabel->setString(boost::lexical_cast<std::string>(Player::getMainPlayer()->getTopScore()));
    }
    
    void MainGameHUD::setContentSize(const cocos2d::Size& size)
    {
        RelativeBox::setContentSize(size);
    }
    
    void MainGameHUD::onGameStateChanged(GameState newState)
    {
        switch (newState) {
            case GameState::Finished:
                mGameOverScreen->setVisible(true);
                break;
            default:
                mGameOverScreen->setVisible(false);
        }
    }
}
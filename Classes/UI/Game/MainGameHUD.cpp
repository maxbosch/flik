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
#include "Literals.h"
#include "Styles.h"
#include "PauseOverlayWidget.h"
#include "MainGameHeader.h"
#include "GameBoard.h"
#include "TextObjectiveOverlay.h"
#include "LevelObjectiveOverlay.h"
#include "DefaultGameOverOverlay.h"
#include "SceneManager.h"

#include <boost/lexical_cast.hpp>

USING_NS_CC;

using RelativeAlign = cocos2d::ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    MainGameHUD::~MainGameHUD()
    {
    }
    
    GameBoard* MainGameHUD::getGameBoard()
    {
        return mGameBoard;
    }
    
    bool MainGameHUD::init()
    {
        if (!GameHUD::init())
        {
            return false;
        }
        
        //setGlobalZOrder(2);
        
        this->setTouchEnabled(false);
        this->setLayoutComponentEnabled(true);
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        
        auto header = MainGameHeader::create();
        auto headerLayout = ui::RelativeLayoutParameter::create();
        headerLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        header->setLayoutParameter(headerLayout);
        addChild(header, 2);
        header->setTouchEnabled(true);
        header->addTouchEventListener([this](Ref* sender, TouchEventType type) {
            if (type == TouchEventType::ENDED) {
                getGameScene()->pauseGame();
            }
        });
        header->onPowerUpTapped = [this](PowerUpType type) {
            getGameScene()->getGameMode()->handlePowerUp(type);
        };
        //header->setGlobalZOrder(2);
        mHeader = header;
        
        mGameOverScreen = createGameOverOverlay();
        auto gameOverScreenLayout = ui::RelativeLayoutParameter::create();
        gameOverScreenLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        mGameOverScreen->setLayoutParameter(gameOverScreenLayout);
        mGameOverScreen->setVisible(false);
        addChild(mGameOverScreen, 3);
        
        auto gameBoard = GameBoard::create();
        gameBoard->setBackGroundColor(Color3B::BLACK);
        gameBoard->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        gameBoard->setContentSize(Size(uiSize.width, uiSize.height - header->getContentSize().height));
        auto gameBoardLayout = ui::RelativeLayoutParameter::create();
        gameBoardLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        gameBoard->setLayoutParameter(gameBoardLayout);
        addChild(gameBoard, 1);
        mGameBoard = gameBoard;
        
        auto pauseOverlay = PauseOverlayWidget::create();
        pauseOverlay->onBackTapped = [this]() {
            getGameScene()->unpauseGame();
        };
        pauseOverlay->onHomeTapped = [this]() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        };
        pauseOverlay->onRestartTapped = [this]() {
            getGameScene()->unpauseGame();
            getGameScene()->requestRestart();
        };
        pauseOverlay->setVisible(false);
        
        addChild(pauseOverlay, 3);
        mPauseOverlay = pauseOverlay;
        
        scheduleOnce([this](float time) {
            auto objectiveOverlay = createObjectiveOverlay();
            auto objectiveOverlayLayout = ui::RelativeLayoutParameter::create();
            objectiveOverlayLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
            objectiveOverlay->setLayoutParameter(objectiveOverlayLayout);
            addChild(objectiveOverlay, 3);
            objectiveOverlay->onStartButtonTapped = [this]() {
                if (getGameScene()) {
                    mObjectiveOverlay->setVisible(false);
                    getGameScene()->requestRestart();
                }
            };
            objectiveOverlay->onExitButtonTapped = [this]() {
                SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
            };
            objectiveOverlay->setVisible(false);
            mObjectiveOverlay = objectiveOverlay;

            mObjectiveOverlay->setVisible(true);
        }, Director::getInstance()->getAnimationInterval(), "show_objective");
        
        return true;
    }
    
    void MainGameHUD::update(float time)
    {
        RelativeBox::update(time);

        mHeader->setScore(Player::getMainPlayer()->getCurrentScore());
    }
    
    void MainGameHUD::setContentSize(const cocos2d::Size& size)
    {
        RelativeBox::setContentSize(size);
    }
    
    void MainGameHUD::onGameStateChanged(GameState newState)
    {
        switch (newState) {
            case GameState::Finished:
                onShowGameOverScreen();
                mGameOverScreen->setVisible(true);
                break;
            case GameState::Paused:
                mPauseOverlay->setVisible(true);
                break;
            default:
                mGameOverScreen->setVisible(false);
                mPauseOverlay->setVisible(false);
        }
    }
    
    GameObjectiveOverlay* MainGameHUD::createObjectiveOverlay()
    {
        return TextObjectiveOverlay::create("Unlimited Mode", "Score as many points as you can before the board fills up");
    }
    
    ui::Widget* MainGameHUD::createGameOverOverlay()
    {
        auto gameOverOverlay = DefaultGameOverOverlay::create();
        gameOverOverlay->onRestartTapped = [this]() {
            if (getGameScene()) {
                getGameScene()->requestRestart();
            }
        };
        gameOverOverlay->onHomeTapped = [this]() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        };
        
        return gameOverOverlay;
    }
    
    void MainGameHUD::onShowGameOverScreen()
    {
        auto gameOverScreen = dynamic_cast<DefaultGameOverOverlay*>(mGameOverScreen);
        gameOverScreen->setTitle("NICE JOB");
        gameOverScreen->setTopScore(getGameScene()->getGameMode()->getTopScore());
        gameOverScreen->setCurrentScore(Player::getMainPlayer()->getCurrentScore());
    }
}
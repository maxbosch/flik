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
#include "Animations.h"
#include "SettingsScene.h"
#include "LocalizedString.h"
#include "AchievementsScene.h"
#include "AchievementOverlay.h"
#include "BonusBar.h"
#include "ChoosePowerupScene.h"

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
                //getGameScene()->pauseGame();
            }
        });
        header->onPauseTapped = [this]() {
            getGameScene()->getGameMode()->pauseGame();
        };
        //header->setGlobalZOrder(2);
        mHeader = header;
        
        mBonusBar = BonusBar::create(Size(uiSize.width, 70.0_dp));
        mBonusBar->setBackGroundColor(Color3B::BLACK);
        mBonusBar->setBackGroundColorType(BackGroundColorType::SOLID);
        auto bonusBarLayout = ui::RelativeLayoutParameter::create();
        bonusBarLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        mBonusBar->setLayoutParameter(bonusBarLayout);
        addChild(mBonusBar, 2);
        mBonusBar->onBonusTapped = [this](BonusType bonus) {
            auto gameMode = this->getGameScene()->getGameMode();
            gameMode->addBonus(bonus);
            Player::getMainPlayer()->consumePowerUp(bonus, 1);
        };
        mBonusBar->onAddBonusTapped = [this]() {
            auto scene = ChoosePowerupScene::create(mBonusBar->getBonuses(), true);
            scene->onPowerupsChosen = [this](const std::vector<BonusType>& bonuses) {
                mBonusBar->setBonuses(bonuses);
            };
            SceneManager::pushSceneWithTransition<TransitionMoveInR>(scene, kTransitionDuration);
        };
        
        mGameOverScreen = createGameOverOverlay();
        auto gameOverScreenLayout = ui::RelativeLayoutParameter::create();
        gameOverScreenLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
        mGameOverScreen->setLayoutParameter(gameOverScreenLayout);
        mGameOverScreen->setVisible(false);
        addChild(mGameOverScreen, 3);
        
        auto gameBoard = GameBoard::create();
        gameBoard->setBackGroundColor(Color3B::BLACK);
        gameBoard->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        gameBoard->setContentSize(Size(uiSize.width, uiSize.height - header->getContentSize().height - mBonusBar->getContentSize().height));
        auto gameBoardLayout = ui::RelativeLayoutParameter::create();
        gameBoardLayout->setAlign(RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
        gameBoardLayout->setMargin(ui::Margin(0, 0, 0, mBonusBar->getContentSize().height));
        gameBoard->setLayoutParameter(gameBoardLayout);
        addChild(gameBoard, 1);
        mGameBoard = gameBoard;
        
        auto timerBar = ui::RelativeBox::create(Size(getContentSize().width, 5.0_dp));
        timerBar->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        timerBar->setBackGroundColor(kGoldColor);
        auto timerBarLayout = ui::RelativeLayoutParameter::create();
        timerBarLayout->setAlign(RelativeAlign::PARENT_TOP_LEFT);
        timerBar->setLayoutParameter(timerBarLayout);
        addChild(timerBar, 2);
        mTimerBar = timerBar;
        
        auto pauseOverlay = PauseOverlayWidget::create();
        pauseOverlay->onBackTapped = [this]() {
            getGameScene()->unpauseGame();
        };
        pauseOverlay->onHomeTapped = [this]() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInB>(kTransitionDuration);
        };
        pauseOverlay->onRestartTapped = [this]() {
            getGameScene()->reloadScene();
        };
        pauseOverlay->onSettingsTapped = [this]() {
            SceneManager::pushSceneWithTransition<TransitionSlideInR>(SettingsScene::create(), 0.3);
        };
        pauseOverlay->onAchievementsTapped = [this]() {
            SceneManager::pushSceneWithTransition<TransitionSlideInL>(AchievementsScene::create(), kTransitionDuration);
        };
        
        pauseOverlay->setVisible(false);
        
        addChild(pauseOverlay, 3);
        mPauseOverlay = pauseOverlay;
        
        showObjectiveOverlay();
        
        return true;
    }
    
    void MainGameHUD::showObjectiveOverlay() {
        scheduleOnce([this](float time) {
            auto objectiveOverlay = createObjectiveOverlay();
            auto objectiveOverlayLayout = ui::RelativeLayoutParameter::create();
            objectiveOverlayLayout->setAlign(RelativeAlign::CENTER_IN_PARENT);
            objectiveOverlay->setLayoutParameter(objectiveOverlayLayout);
            addChild(objectiveOverlay, 3);
            objectiveOverlay->onStartButtonTapped = [this](const std::vector<BonusType>& bonuses) {
                if (getGameScene()) {
                    mObjectiveOverlay->setVisible(false);
                    mBonusBar->setBonuses(bonuses);
                    mBonusBar->reset();
                    getGameScene()->requestRestart();
                }
            };
            objectiveOverlay->onExitButtonTapped = [this]() {
                getGameScene()->getGameMode()->onBackPressed();
            };
            objectiveOverlay->setVisible(false);
            mObjectiveOverlay = objectiveOverlay;
            
            mObjectiveOverlay->setVisible(true);
            
        }, kTransitionDuration, "show_objective");
    }
    
    void MainGameHUD::update(float time)
    {
        RelativeBox::update(time);

        mHeader->setScore(Player::getMainPlayer()->getCurrentScore());
        
        if (mTimerBar->isVisible()) {
            auto gameMode = getGameScene()->getGameMode();
            auto ratio = gameMode->getTimeRemaining() / gameMode->getGameTime();
            mTimerBar->setContentSize(Size(getContentSize().width * ratio, mTimerBar->getContentSize().height));
            
            mTimerBar->setBackGroundColor(Util::colorInterpolate(kRedColor, kGoldColor, ratio));
        }
    }
    
    void MainGameHUD::setContentSize(const cocos2d::Size& size)
    {
        RelativeBox::setContentSize(size);
    }
    
    void MainGameHUD::onGameStateChanged(GameState newState)
    {
        switch (newState) {
            case GameState::Finished:
                if (mPendingAchievements.size() > 0) {
                    showAchievement(0);
                } else {
                    onShowGameOverScreen();
                    mGameOverScreen->setVisible(true);
                }
                break;
            case GameState::Paused:
                mPauseOverlay->setVisible(true);
                break;
            default:
                mGameOverScreen->setVisible(false);
                mPauseOverlay->setVisible(false);
        }
    
        if (newState == GameState::InProgress) {
            auto gameMode = getGameScene()->getGameMode();
            if (gameMode->getGameTime() > 0) {
                mTimerBar->setVisible(true);
            }
        }
    }
    
    GameObjectiveOverlay* MainGameHUD::createObjectiveOverlay()
    {
        return TextObjectiveOverlay::create(LocalizedString::getString("game_mode_unlimited"), LocalizedString::getString("objective_unlimited"));
    }
    
    ui::Widget* MainGameHUD::createGameOverOverlay()
    {
        auto gameOverOverlay = DefaultGameOverOverlay::create();
        gameOverOverlay->onRestartTapped = [this]() {
            if (getGameScene()) {
                getGameScene()->reloadScene();
            }
        };
        gameOverOverlay->onHomeTapped = [this]() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInB>(kTransitionDuration);
        };
        
        return gameOverOverlay;
    }
    
    void MainGameHUD::onShowGameOverScreen()
    {
        auto gameOverScreen = dynamic_cast<DefaultGameOverOverlay*>(mGameOverScreen);
        auto gameMode = getGameScene()->getGameMode();
        gameOverScreen->show(Player::getMainPlayer()->getCurrentScore(), gameMode->getPreviousTopScore());
    }
    
    void MainGameHUD::showAchievement(int index)
    {
        if (index < mPendingAchievements.size()) {
            auto achievementOverlay = AchievementOverlay::create(mPendingAchievements[index]);
            achievementOverlay->onNextLevelTapped = [this, index, achievementOverlay]() {
                showAchievement(index + 1);
                achievementOverlay->animateOut();
            };

            addChild(achievementOverlay, 3);
            achievementOverlay->animateIn();
        } else {
            mPendingAchievements.clear();
            
            onShowGameOverScreen();
            mGameOverScreen->setVisible(true);
        }
    }
}

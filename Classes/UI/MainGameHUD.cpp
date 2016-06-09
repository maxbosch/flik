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
        //header->setGlobalZOrder(2);
        mHeader = header;
        
        mGameOverScreen = GameOverWidget::create();
        mGameOverScreen->setContentSize(Size(uiSize.width - 20.0_dp, 120.0_dp));
        mGameOverScreen->setBackGroundColor(Color3B(225, 225, 225));
        mGameOverScreen->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        mGameOverScreen->onRestartClick = [this]() {
            if (getGameScene()) {
                getGameScene()->requestRestart();
            }
        };
        auto gameOverScreenLayout = ui::RelativeLayoutParameter::create();
        gameOverScreenLayout->setMargin(ui::Margin(10.0_dp, 100.0_dp, 10.0_dp, 0));
        gameOverScreenLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        mGameOverScreen->setLayoutParameter(gameOverScreenLayout);
        mGameOverScreen->setVisible(false);
        addChild(mGameOverScreen, 3);
        
        auto gameBoard = ui::Layout::create();
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
            Director::getInstance()->popToRootScene();
        };
        pauseOverlay->onRestartTapped = [this]() {
            getGameScene()->requestRestart();
        };
        pauseOverlay->setVisible(false);
        
        addChild(pauseOverlay, 3);
        mPauseOverlay = pauseOverlay;
        
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
}
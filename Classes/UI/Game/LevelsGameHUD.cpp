//
//  LevelsGameHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#include "LevelsGameHUD.h"
#include "Util.h"
#include "LevelObjectiveOverlay.h"
#include "MainGameHeader.h"
#include "Literals.h"
#include "Events.h"
#include "LevelGameOverOverlay.h"
#include "MainGameScene.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#include "LevelsGameMode.h"
#include "SceneManager.h"
#include "Styles.h"
#include "LocalizedString.h"
#include "AchievementsScene.h"
#include "LevelGameScene.h"
#include "ObjectiveTracker.h"
#include "Analytics.h"

namespace flik
{
    using RelativeAlign = ui::RelativeLayoutParameter::RelativeAlign;
    
    LevelsGameHUD* LevelsGameHUD::create(const LevelDescription* levelDesc)
    {
        return createWithParams<LevelsGameHUD>(levelDesc);
    }
    
    bool LevelsGameHUD::init(const LevelDescription* levelDesc)
    {
        mLevelDesc = levelDesc;
        
        if (!MainGameHUD::init())
        {
            return false;
        }
        
        mHeader->setScoreVisible(false);
        mObjectiveProgress = 0;
 
        auto objectivesWidget = Fonts::createLocalizedText("", 20.0_dp);
        objectivesWidget->setColor(kGoldColor);
        objectivesWidget->setTextHorizontalAlignment(TextHAlignment::RIGHT);
        auto objectivesWidgetLayout = ui::RelativeLayoutParameter::create();
        objectivesWidgetLayout->setAlign(RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
        objectivesWidgetLayout->setMargin(ui::Margin(0, 0, 30.0_dp, 0));
        objectivesWidget->setLayoutParameter(objectivesWidgetLayout);
        mHeader->addChild(objectivesWidget);
        mObjectiveText = objectivesWidget;
        
        return true;
    }
    
    GameObjectiveOverlay* LevelsGameHUD::createObjectiveOverlay()
    {
        auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
        
        auto name = LocalizedString::getString("level_name_" + std::string(mLevelDesc->data["name"].GetString()));
        return LevelObjectiveOverlay::create(name, mLevelDesc, gameMode->getSublevel());
    }
    
    cocos2d::ui::Widget* LevelsGameHUD::createGameOverOverlay()
    {
        auto gameOverOverlay = LevelGameOverOverlay::create();
        gameOverOverlay->onRestartTapped = [this]() {
            if (getGameScene()) {
                getGameScene()->reloadScene();
                
                PTree attributes;
                attributes.add("mode", kGameModeStrings[getGameScene()->getGameMode()->getGameModeType()]);
                Analytics::logEvent("game_end_restart", attributes);
            }
        };
        
        gameOverOverlay->onNextLevelTapped = [this]() {
            auto levelInfo = LevelInfo::getInstance();
            auto levelDesc = levelInfo->getLevelDescription(mLevelDesc->levelNum);
            auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
            auto newScene = LevelGameScene::create(levelDesc, gameMode->getSublevel() + 1);
            SceneManager::replaceSceneWithTransition<TransitionMoveInR>(newScene, kTransitionDuration);
        };
        
        gameOverOverlay->onShowLevelListTapped = [this]() {
            SceneManager::popSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
            
            if (getGameScene()) {
                PTree attributes;
                attributes.add("mode", kGameModeStrings[getGameScene()->getGameMode()->getGameModeType()]);
                Analytics::logEvent("game_end_home", attributes);
            }
        };
        
        return gameOverOverlay;
    }

    void LevelsGameHUD::onShowGameOverScreen()
    {
        auto gameOverOverlay = dynamic_cast<LevelGameOverOverlay*>(mGameOverScreen);
        auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
        bool hasNext = !gameMode->isFinalLevel();
        
        gameOverOverlay->show(gameMode->getSublevel(), gameMode->isObjectiveCompleted(), gameMode->getScore(), gameMode->getPointsEarned(), hasNext);
//
//        gameOverOverlay->setNextLevel(gameMode->isObjectiveCompleted(), mLevelDesc->levelNum, gameMode->getSublevel());
    }
    
    void LevelsGameHUD::update(float seconds)
    {
        MainGameHUD::update(seconds);
        
        if (getGameScene()) {
            auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
            if (gameMode) {
                auto objective = gameMode->getObjectives()[0];
                Fonts::updateLocalizedText(mObjectiveText, fmt::sprintf("%d/%d", objective->getCurrentValue(), objective->getTotalValue()));
                mHeader->forceDoLayout();
            }
        }
    }
}

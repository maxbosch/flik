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
#include "LevelsGameMode.h"
#include "ObjectiveTracker.h"

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
        auto objectivesWidgetLayout = ui::RelativeLayoutParameter::create();
        objectivesWidgetLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        objectivesWidgetLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        objectivesWidget->setLayoutParameter(objectivesWidgetLayout);
        mHeader->addChild(objectivesWidget);
        mObjectiveText = objectivesWidget;
        
        return true;
    }
    
    GameObjectiveOverlay* LevelsGameHUD::createObjectiveOverlay()
    {
        return LevelObjectiveOverlay::create(LocalizedString::getString("game_mode_level", mLevelDesc->levelNum, mLevelDesc->sublevelNum + 1), mLevelDesc);
    }
    
    cocos2d::ui::Widget* LevelsGameHUD::createGameOverOverlay()
    {
        auto gameOverOverlay = LevelGameOverOverlay::create();
        gameOverOverlay->onRestartTapped = [this]() {
            if (getGameScene()) {
                getGameScene()->requestRestart();
            }
        };
        gameOverOverlay->onHomeTapped = [this]() {
            SceneManager::popToRootSceneWithTransition<TransitionSlideInB>(kTransitionDuration);
        };
        
        gameOverOverlay->onAchievementsTapped = [this]() {
            SceneManager::pushSceneWithTransition<TransitionSlideInL>(AchievementsScene::create(), kTransitionDuration);
        };
        
        gameOverOverlay->onNextLevelTapped = [this]() {
            auto levelInfo = LevelInfo::getInstance();
            auto levelDesc = levelInfo->getLevelDescription(mLevelDesc->levelNum);
            auto newScene = MainGameScene::create({LevelsGameMode::create(levelDesc), LevelsGameHUD::create(levelDesc)});
            SceneManager::replaceSceneWithTransition<TransitionMoveInR>(newScene, kTransitionDuration);
        };
        
        gameOverOverlay->onShowLevelListTapped = [this]() {
            SceneManager::popSceneWithTransition<TransitionSlideInR>(kTransitionDuration);
        };
        
        return gameOverOverlay;
    }

    void LevelsGameHUD::onShowGameOverScreen()
    {
        auto gameOverOverlay = dynamic_cast<LevelGameOverOverlay*>(mGameOverScreen);
        
        auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
        
        gameOverOverlay->setNextLevel(gameMode->isObjectiveCompleted(), mLevelDesc->levelNum);
    }
    
    void LevelsGameHUD::update(float seconds)
    {
        MainGameHUD::update(seconds);
        
        if (getGameScene()) {
            auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
            if (gameMode) {
                auto objective = gameMode->getObjectives()[0];
                mObjectiveText->setString(fmt::sprintf("%d/%d", objective->getCurrentValue(), objective->getTotalValue()));
            }
        }
    }
}

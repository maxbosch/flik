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
#include "ObjectiveDisplayWidget.h"
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
        
        if (!TimedGameHUD::init())
        {
            return false;
        }
        
        mHeader->setScoreVisible(false);
        mObjectiveProgress = 0;
        
        auto quantity = mLevelDesc->objectives[0].quantity;
        
        auto objectivesWidget = Fonts::createLocalizedText(fmt::sprintf("0/%d", quantity), 20.0_dp);
        objectivesWidget->setColor(kGoldColor);
        auto objectivesWidgetLayout = ui::RelativeLayoutParameter::create();
        objectivesWidgetLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        objectivesWidgetLayout->setMargin(ui::Margin(0, 30.0_dp, 0, 0));
        objectivesWidget->setLayoutParameter(objectivesWidgetLayout);
        mHeader->addChild(objectivesWidget);
        
        auto pieceRemovedListener = EventListenerCustom::create(kObjectiveUpdatedEvent, [this, objectivesWidget, quantity](EventCustom* event) {
            ObjectiveIncrementUpdate* updateData = reinterpret_cast<ObjectiveIncrementUpdate*>(event->getUserData());
            mObjectiveProgress += updateData->increment;
            mObjectiveProgress = std::min(mObjectiveProgress, quantity);
            objectivesWidget->setString(fmt::sprintf("%d/%d", mObjectiveProgress, quantity));
            
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    GameObjectiveOverlay* LevelsGameHUD::createObjectiveOverlay()
    {
        return LevelObjectiveOverlay::create(LocalizedString::getString("game_mode_level", mLevelDesc->levelNum), mLevelDesc);
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
            auto levelDesc = levelInfo->getLevelDescription(mLevelDesc->levelNum + 1);
            auto newScene = MainGameScene::create({LevelsGameMode::create(levelDesc), LevelsGameHUD::create(levelDesc)});
            SceneManager::replaceSceneWithTransition<TransitionMoveInR>(newScene, kTransitionDuration);
        };
        
        return gameOverOverlay;
    }

    void LevelsGameHUD::onShowGameOverScreen()
    {
        auto gameOverOverlay = dynamic_cast<LevelGameOverOverlay*>(mGameOverScreen);
        
        auto gameMode = dynamic_cast<LevelsGameMode*>(getGameScene()->getGameMode());
        
        gameOverOverlay->setNextLevel(gameMode->isObjectiveCompleted(), mLevelDesc->levelNum + 1);
    }
}

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
        
        auto objectivesWidget = ObjectiveDisplayWidget::create(mLevelDesc->objectives);
        auto objectivesWidgetLayout = ui::RelativeLayoutParameter::create();
        objectivesWidgetLayout->setAlign(RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
        objectivesWidgetLayout->setMargin(ui::Margin(0, 10.0_dp, 0, 0));
        objectivesWidget->setLayoutParameter(objectivesWidgetLayout);
        mHeader->addChild(objectivesWidget);
        
        auto pieceRemovedListener = EventListenerCustom::create(kObjectiveUpdatedEvent, [objectivesWidget](EventCustom* event) {
            ObjectiveIncrementUpdate* updateData = reinterpret_cast<ObjectiveIncrementUpdate*>(event->getUserData());
            objectivesWidget->incrementObjective(updateData->type, updateData->increment);
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    GameObjectiveOverlay* LevelsGameHUD::createObjectiveOverlay()
    {
        std::stringstream title;
        title << "Level " << mLevelDesc->levelNum;
        return LevelObjectiveOverlay::create(title.str(), mLevelDesc);
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
            SceneManager::popToRootSceneWithTransition<TransitionSlideInL>(kTransitionDuration);
        };
        
        gameOverOverlay->onAchievementsTapped = [this]() {
            sdkbox::PluginSdkboxPlay::showAchievements();
        };
        
        gameOverOverlay->onNextLevelTapped = [this]() {
            auto levelInfo = LevelInfo::getInstance();
            auto levelDesc = levelInfo->getLevelDescription(mLevelDesc->levelNum + 1);
            auto newScene = MainGameScene::create({LevelsGameMode::create(levelDesc), LevelsGameHUD::create(levelDesc)});
            SceneManager::replaceSceneWithTransition<TransitionSlideInR>(newScene, kTransitionDuration);
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

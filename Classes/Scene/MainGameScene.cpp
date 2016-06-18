#include "MainGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SideRailNode.h"
#include "GamePiece.h"
#include "Player.h"
#include "GameOverWidget.h"
#include "MainGameHUD.h"
#include "GameMode.h"
#include "GameBoard.h"
#include "Util.h"

USING_NS_CC;

using namespace cocostudio::timeline;

namespace flik
{
    void MainGameScene::setGameMode(GameMode* gameMode)
    {
        mGameMode = gameMode;
        mGameMode->setGameScene(this);
        mGameMode->onGameStateChanged = CC_CALLBACK_1(MainGameScene::onGameStateChanged, this);
        addChild(mGameMode);
    }
    
    void MainGameScene::setGameHUD(GameHUD* hud)
    {
        addChild(hud);
        
        mGameHUD = hud;
        mGameHUD->setContentSize(Director::getInstance()->getOpenGLView()->getDesignResolutionSize());
        mGameHUD->setLocalZOrder(1000);
        mGameHUD->setGameScene(this);
        if (mGameMode) {
            mGameHUD->onGameStateChanged(mGameMode->getGameState());
        }
        
        mGameBoard = mGameHUD->getGameBoard();
       
        auto sideRailNode = SideRailNode::create(mGameBoard->getContentSize());
        sideRailNode->setPosition(0, 0);
        sideRailNode->setAnchorPoint(Vec2(0, 0));
        mSideRails = sideRailNode;
        
        mGameBoard->addChild(mSideRails);
    }
    
    void MainGameScene::onGameStateChanged(GameState newState)
    {
        switch (newState) {
            case GameState::Finished:
                finishGame();
                break;
                
            case GameState::Starting:
                restartGame();
                
            default:
                break;
        }
    
        if (mGameHUD) {
            mGameHUD->onGameStateChanged(newState);
        }
    }
    
    void MainGameScene::finishGame()
    {
        enumeratePieces([this](Node* piece) {
            getEventDispatcher()->removeEventListenersForTarget(piece);
        });
        
        Player::getMainPlayer()->handleEndOfGameAchievements(mGameMode->getGameModeType());
    }
    
    MainGameScene* MainGameScene::create(const LevelParams& params)
    {
        return createWithParams<MainGameScene>(params);
    }
    
    // on "init" you need to initialize your instance
    bool MainGameScene::init(const LevelParams& params)
    {
        if ( !Scene::initWithPhysics() )
        {
            return false;
        }
        
        auto physicsWorld = getPhysicsWorld();
        //physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
        physicsWorld->setSubsteps(2);
        //physicsWorld->setSpeed(1.0 / 120.0);
        
        setGameHUD(params.hud);
        
        setGameMode(params.mode);
        
        this->scheduleUpdate();

        return true;
    }
    
    void MainGameScene::requestRestart()
    {
        mGameMode->restartGame();
    }
    
    void MainGameScene::restartGame()
    {
    }
    
    void MainGameScene::clearPieces()
    {
        mGameBoard->clearBoard();
    }
    
    void MainGameScene::update(float delta)
    {
        Node::update(delta);
        
        if (mGameHUD) {
            mGameHUD->update(delta);
        }
    }
    
    Rect MainGameScene::getGameBoardBounds()
    {
        return mSideRails->getInnerBoundingBox();
    }
    
    void MainGameScene::spawnPiece(const Vec2& position)
    {
        if (mGameBoard) {
            auto piece = GamePiece::create(position);
            piece->setGameScene(this);
            mGameBoard->addPiece(piece);
        }
    }
    
    void MainGameScene::enumeratePieces(std::function<void(Node*)> callback) {
        if (mGameBoard) {
            for (auto piece : mGameBoard->getPieces()) {
                callback(piece);
            }
        }
    }
    
    int MainGameScene::getPiecesCount()
    {
        if (mGameBoard) {
            return (int) mGameBoard->getPieces().size();
        }
        
        return 0;
    }
    
    void MainGameScene::pauseGame()
    {
        mGameMode->pauseGame();
    }
    
    void MainGameScene::unpauseGame()
    {
        mGameMode->resumeGame();
    }
}


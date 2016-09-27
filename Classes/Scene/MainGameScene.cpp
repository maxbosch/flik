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
#include "Events.h"
#include "GoalLayer.h"
#include "GLES-Render.h"

USING_NS_CC;

using namespace cocostudio::timeline;

#define DEBUG_PHYSICS 0

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
       
        auto sideRailNode = SideRailNode::create(this, mGameBoard->getContentSize());
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
        
        std::vector<std::string> achievements;
        Player::getMainPlayer()->handleEndOfGameAchievements(mGameMode->getGameModeType(), achievements);
        
        if (achievements.size() > 0) {
            auto mainGameHUD = dynamic_cast<MainGameHUD*>(mGameHUD);
            if (mainGameHUD) {
                mainGameHUD->showAchievements(achievements);
            }
        }
    }
    
    MainGameScene* MainGameScene::create(const LevelParams& params)
    {
        return createWithParams<MainGameScene>(params);
    }
    
    // on "init" you need to initialize your instance
    bool MainGameScene::init(const LevelParams& params)
    {
        if ( !Scene::init() )
        {
            return false;
        }
        
//        auto physicsWorld = getPhysicsWorld();
//        physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
//        physicsWorld->setSubsteps(10);

        //physicsWorld->setSpeed(1.0 / 120.0);
       
        mPhysicsWorldBox2D = std::shared_ptr<b2World>(new b2World(b2Vec2(0, 0)));
        //mPhysicsWorldBox2D->SetContinuousPhysics(true);
        mPhysicsWorldBox2D->SetContactListener(this);
        
#if DEBUG_PHYSICS
        b2Draw *m_debugDraw = new GLESDebugDraw(kPixelsToMeters);
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_aabbBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        m_debugDraw->SetFlags(flags);
        mPhysicsWorldBox2D->SetDebugDraw(m_debugDraw);
#endif
        
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
        mPhysicsWorldBox2D->Step(1.0 / 60.0, 1, 1);
        
        Node::update(delta);
        
        if (mGameHUD) {
            mGameHUD->update(delta);
        }
    }
    
    Rect MainGameScene::getGameBoardBounds()
    {
        return mSideRails->getInnerBoundingBox();
    }
    
    void MainGameScene::spawnPiece(const Vec2& position, GamePieceType pieceType)
    {
        if (mGameBoard) {
            auto piece = GamePiece::create(position, pieceType);
            piece->setGameScene(this);
            mGameBoard->addPiece(piece);
            
            EventCustom eventObj(kPieceAddedEvent);
            eventObj.setUserData(piece);
            getEventDispatcher()->dispatchEvent(&eventObj);
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
    
    void MainGameScene::setColorEnabled(GamePieceType color, bool enabled)
    {
        auto layer = mSideRails->getColorLayer(color);
        layer->setEnabled(enabled);
    }
    
    GoalLayer* MainGameScene::getLayerForColor(GamePieceType color)
    {
        return mSideRails->getColorLayer(color);
    }
    
    void MainGameScene::onBackPressed()
    {
        if (mGameMode) {
            mGameMode->onBackPressed();
        }
    }
    
    void MainGameScene::render(Renderer *renderer)
    {
        SceneEx::render(renderer);
        
#if DEBUG_PHYSICS
        mPhysicsWorldBox2D->DrawDebugData();
#endif
    }
    
    void MainGameScene::BeginContact(b2Contact* contact)
    {
    }
    
    void MainGameScene::reloadScene()
    {
        Player::getMainPlayer()->resetScore();
    }
}


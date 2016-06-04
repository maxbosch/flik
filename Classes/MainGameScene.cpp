#include "MainGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SideRailNode.h"
#include "GamePiece.h"
#include "Player.h"
#include "GameOverWidget.h"
#include "MainGameHUD.h"
#include "GameMode.h"

USING_NS_CC;

using namespace cocostudio::timeline;

namespace flik
{
    static const int kPieceTag = 0xF00F;
    
    void MainGameScene::setGameMode(GameMode* gameMode)
    {
        mGameMode = gameMode;
        mGameMode->setGameScene(this);
        mGameMode->onGameStateChanged = CC_CALLBACK_1(MainGameScene::onGameStateChanged, this);
        addChild(mGameMode);
        
        mGameMode->restartGame();
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
        
        //mGameOverScreen->setVisible(true);
        Player::getMainPlayer()->recordScore();
    }
    
    // on "init" you need to initialize your instance
    bool MainGameScene::init()
    {
        if ( !Scene::initWithPhysics() )
        {
            return false;
        }
        
        auto physicsWorld = getPhysicsWorld();
        //physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
        physicsWorld->setSubsteps(2);
        //physicsWorld->setSpeed(1.0 / 120.0);
        
        auto uiSize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
        
        auto sideRailNode = SideRailNode::create();
        sideRailNode->setContentSize(Director::getInstance()->getVisibleSize());
        sideRailNode->setPosition(0, 0);
        sideRailNode->setAnchorPoint(Vec2(0, 0));
        mSideRails = sideRailNode;
        
        mGameBoard = Node::create();
        mGameBoard->setContentSize(getContentSize());
        mGameBoard->setColor(Color3B(255, 255, 255));
        mGameBoard->addChild(mSideRails);
        addChild(mGameBoard);
        
        this->scheduleUpdate();

        return true;
    }
    
    void MainGameScene::requestRestart()
    {
        if (mGameMode->getGameState() == GameState::Finished) {
            mGameMode->restartGame();
        }
    }
    
    void MainGameScene::restartGame()
    {
        // Remove any existing pieces
        enumeratePieces([](Node* piece) {
            piece->removeFromParent();
        });
        
        Player::getMainPlayer()->resetScore();
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
        auto piece = GamePiece::create(position);
        piece->setGameScene(this);
        piece->setTag(kPieceTag);
        mGameBoard->addChild(piece);
    }
    
    void MainGameScene::constrainPieceToGameBounds(GamePiece* piece)
    {
        auto boardBounds = mSideRails->getInnerBoundingBox();
        auto pieceBounds = piece->getBoundingBox();
        
        float xOffset = 0, yOffset = 0;
        if (boardBounds.getMinX() > pieceBounds.getMinX()) {
            xOffset = boardBounds.getMinX() - pieceBounds.getMinX();
        } else if (boardBounds.getMaxX() < pieceBounds.getMaxX()) {
            xOffset = boardBounds.getMaxX() - pieceBounds.getMaxX();
        }
        
        if (boardBounds.getMinY() > pieceBounds.getMinY()) {
            yOffset = boardBounds.getMinY() - pieceBounds.getMinY();
        } else if (boardBounds.getMaxY() < pieceBounds.getMaxY()) {
            yOffset = boardBounds.getMaxY() - pieceBounds.getMaxY();
        }
        
        piece->setPosition(piece->getPosition() + Vec2(xOffset, yOffset));
    }
    
    void MainGameScene::enumeratePieces(std::function<void(Node*)> callback) {
        auto children = mGameBoard->getChildren();
        for (auto child : children) {
            if (child->getTag() == kPieceTag) {
                callback(child);
            }
        }
    }
}


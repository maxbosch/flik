#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Enums.h"
#include "SceneEx.h"
#include "box2d/Box2D.h"

namespace flik
{
    class GamePiece;
    class SideRailNode;
    class GameOverWidget;
    class GameHUD;
    class GameMode;
    class GameBoard;
    class GoalLayer;
    enum class GameState;
    
    struct LevelParams
    {
        GameMode* mode;
        GameHUD* hud;
    };
    
    class MainGameScene : public SceneEx, public b2ContactListener
    {
    public:
        // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        virtual bool init(const LevelParams& params);
        
        // implement the "static create()" method manually
        static MainGameScene* create(const LevelParams& params);
        
        void update(float delta);
        virtual void requestRestart();
        void spawnPiece(const cocos2d::Vec2& position, GamePieceType pieceType = GamePieceType::RandomPiece);
        void clearPieces();
        int getPiecesCount();
        
        void enumeratePieces(std::function<void(Node*)> callback);
        cocos2d::Rect getGameBoardBounds();
        
        void setGameMode(GameMode* gameMode);
        GameMode* getGameMode() { return mGameMode; }
    
        void setGameHUD(GameHUD* hud);
        GameHUD* getGameHUD() { return mGameHUD; }
        
        GameBoard* getGameBoard() { return mGameBoard; }
        
        void pauseGame();
        void unpauseGame();
        
        void setColorEnabled(GamePieceType color, bool enabled);
        GoalLayer* getLayerForColor(GamePieceType color);
        
        void onBackPressed();
        
        std::shared_ptr<b2World>& getPhysicsWorldBox2D() { return mPhysicsWorldBox2D; }
        
        void render(cocos2d::Renderer *renderer, const cocos2d::Mat4& eyeTransform, const cocos2d::Mat4* eyeProjection = nullptr);
        
        /* b2ContactListener methods */
        void BeginContact(b2Contact* contact);
        
        virtual void reloadScene();
        
    private:
        cocos2d::TimerTargetCallback* mSpawnTimer;
        SideRailNode* mSideRails;
        GameBoard* mGameBoard;
        GameHUD* mGameHUD = nullptr;
        GameMode* mGameMode = nullptr;
        
        std::shared_ptr<b2World> mPhysicsWorldBox2D = nullptr;
    
        cocos2d::Vec2 findOpenSpawnPosition();
        void restartGame();
        void finishGame();
        void onGameStateChanged(GameState newState);
    };
}



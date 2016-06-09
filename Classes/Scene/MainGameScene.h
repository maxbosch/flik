#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace flik
{
    class GamePiece;
    class SideRailNode;
    class GameOverWidget;
    class GameHUD;
    class GameMode;
    enum class GameState;
    
    struct LevelParams
    {
        GameMode* mode;
        GameHUD* hud;
    };
    
    class MainGameScene : public cocos2d::Scene
    {
    public:
        // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        virtual bool init(const LevelParams& params);
        
        // implement the "static create()" method manually
        static MainGameScene* create(const LevelParams& params);
        
        void constrainPieceToGameBounds(GamePiece* piece);
        void update(float delta);
        void requestRestart();
        void spawnPiece(const cocos2d::Vec2& position);
        void clearPieces();
        
        void enumeratePieces(std::function<void(Node*)> callback);
        cocos2d::Rect getGameBoardBounds();
        
        void setGameMode(GameMode* gameMode);
        GameMode* getGameMode() { return mGameMode; }
        
        void setGameHUD(GameHUD* hud);
        
        void pauseGame();
        void unpauseGame();
        
    private:
        cocos2d::TimerTargetCallback* mSpawnTimer;
        SideRailNode* mSideRails;
        cocos2d::Node* mGameBoard;
        GameHUD* mGameHUD = nullptr;
        GameMode* mGameMode = nullptr;
    
        cocos2d::Vec2 findOpenSpawnPosition();
        void restartGame();
        void finishGame();
        void onGameStateChanged(GameState newState);
    };
}



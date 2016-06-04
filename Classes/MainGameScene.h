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
    
    class MainGameScene : public cocos2d::Node
    {
    public:
        // there's no 'id' in cpp, so we recommend returning the class instance pointer
        cocos2d::Scene* createScene();
        
        // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        virtual bool init();
        
        // implement the "static create()" method manually
        CREATE_FUNC(MainGameScene);
        
        void constrainPieceToGameBounds(GamePiece* piece);
        void update(float delta);
        void requestRestart();
        void spawnPiece(const cocos2d::Vec2& position);
        
        void enumeratePieces(std::function<void(Node*)> callback);
        cocos2d::Rect getGameBoardBounds();
        
        void setGameMode(GameMode* gameMode);
        GameMode* getGameMode() { return mGameMode; }
        
        void setGameHUD(GameHUD* hud);
        
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



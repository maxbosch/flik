//
//  TutorialGameMode.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/29/16.
//
//

#include "TutorialGameMode.h"
#include "MainGameScene.h"
#include "Util.h"
#include "Events.h"
#include "Physics.h"
#include "Literals.h"
#include "Enums.h"
#include "TutorialGameHUD.h"
#include "MainGameScene.h"

USING_NS_CC;

namespace flik
{
    struct TutorialPieceInfo {
        GamePieceType pieceType;
        float rotation;
        TutorialArrowPosition position;
    };
    
    static const std::vector<TutorialPieceInfo> kPieceOrder {{
        { GamePieceType::RedPiece, 325.0f, TutorialArrowPosition::TopLeft },
        { GamePieceType::YellowPiece, 145.0f, TutorialArrowPosition::BottomRight },
        { GamePieceType::PinkPiece, 215.0f, TutorialArrowPosition::BottomLeft },
        { GamePieceType::BluePiece, 35.0f, TutorialArrowPosition::TopRight }
    }};
    
    bool TutorialGameMode::init()
    {
        if (!GameMode::init())
        {
            return false;
        }
        
        auto pieceRemovedListener = EventListenerCustom::create(kPieceRemovedEvent, [this](EventCustom* event) {
            spawnNextPiece();
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceRemovedListener, this);
        
        return true;
    }
    
    void TutorialGameMode::restartGame()
    {
        setGameState(GameState::InProgress);
        
        spawnNextPiece();
        
        this->scheduleUpdate();
    }
    
    void TutorialGameMode::spawnNextPiece()
    {
        if (getGameState() == GameState::InProgress) {
            if (nextPieceId < kPieceOrder.size()) {
                auto visibleSize = Director::getInstance()->getVisibleSize();
                auto position = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
                
                getGameScene()->spawnPiece(position, kPieceOrder[nextPieceId].pieceType);
                
                auto hud = dynamic_cast<TutorialGameHUD*>(getGameScene()->getGameHUD());
                if (hud) {
                    hud->setArrowPosition(kPieceOrder[nextPieceId].position, kPieceOrder[nextPieceId].rotation);
                }
                
                nextPieceId++;
            } else {
                setGameState(GameState::Finished);
            }
        }
    }
}

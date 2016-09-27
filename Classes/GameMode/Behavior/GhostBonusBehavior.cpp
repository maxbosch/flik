//
//  GhostBonusBehavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#include "GhostBonusBehavior.h"
#include "Util.h"
#include "Events.h"
#include "GamePiece.h"
#include "Physics.h"
#include "MainGameScene.h"
#include "GameBoard.h"

USING_NS_CC;

namespace flik
{
    GhostBonusBehavior* GhostBonusBehavior::create(MainGameScene* scene, float duration)
    {
        return createWithParams<GhostBonusBehavior>(scene, duration);
    }
    
    bool GhostBonusBehavior::init(MainGameScene* scene, float duration)
    {
        if (!Behavior::init(scene, duration))
        {
            return false;
        }
        
        auto makeGhostPiece = [](GamePiece* piece){
            piece->setPieceCollisionEnabled(false);
            
            piece->setOpacity(128);
        };
        
        auto pieceAddedListener = EventListenerCustom::create(kPieceAddedEvent, [this, makeGhostPiece](EventCustom* event) {
            auto piece = reinterpret_cast<GamePiece*>(event->getUserData());
            makeGhostPiece(piece);
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceAddedListener, this);
        
        auto& pieces = scene->getGameBoard()->getPieces();
        for (auto piece : pieces) {
            makeGhostPiece(piece);
        }
        
        return true;
    }
    
    void GhostBonusBehavior::onExpire(MainGameScene* scene)
    {
        auto& pieces = scene->getGameBoard()->getPieces();
        for (auto piece : pieces) {
            piece->setPieceCollisionEnabled(true);
            piece->setOpacity(255);
        }
    }
}

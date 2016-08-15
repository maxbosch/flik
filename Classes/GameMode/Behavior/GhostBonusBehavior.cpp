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
        
        auto pieceAddedListener = EventListenerCustom::create(kPieceAddedEvent, [this](EventCustom* event) {
            int mask = collision::AllPieces;
            
            auto piece = reinterpret_cast<GamePiece*>(event->getUserData());
            auto piecePhysicsBody = piece->getPhysicsBody();
            piecePhysicsBody->setCollisionBitmask(piecePhysicsBody->getCollisionBitmask() ^ mask);
            piecePhysicsBody->setContactTestBitmask(piecePhysicsBody->getContactTestBitmask() ^ mask);
        });
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(pieceAddedListener, this);
        
        return true;
    }
}
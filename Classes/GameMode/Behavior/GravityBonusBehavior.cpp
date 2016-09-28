//
//  GravityBonusBehavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 9/13/16.
//
//

#include "GravityBonusBehavior.h"
#include "Util.h"
#include "Events.h"
#include "GamePiece.h"
#include "Physics.h"
#include "MainGameScene.h"
#include "GameBoard.h"
#include "GameMode.h"

USING_NS_CC;

namespace flik
{
    static const Vec2 kVelocity(10, 10);
    
    GravityBonusBehavior* GravityBonusBehavior::create(MainGameScene* scene, float duration)
    {
        return createWithParams<GravityBonusBehavior>(scene, duration);
    }
    
    bool GravityBonusBehavior::init(MainGameScene* scene, float duration)
    {
        if (!Behavior::init(scene, duration))
        {
            return false;
        }
        
        
        return true;
    }
    
    void GravityBonusBehavior::update(float time)
    {
        Behavior::update(time);
        
        auto gameBoard = getGameScene()->getGameBoard();
        auto boardSize = gameBoard->getContentSize();
        auto pieces = gameBoard->getPieces();
        
        for (auto piece : pieces) {
            auto physicsBody = piece->getPhysicsBodyBox2D();
            auto& velocity = physicsBody->GetLinearVelocity();
            if (b2Dot(velocity, velocity) == 0 && !piece->isDragging()) {
                b2Vec2 unitPosition;
                
                switch (static_cast<GamePieceType>(piece->getType())) {
                    case GamePieceType::RedPiece:
                        unitPosition = b2Vec2(0, 1);
                        break;
                        
                    case GamePieceType::GreenPiece:
                        unitPosition = b2Vec2(0, 0);
                        break;
                        
                    case GamePieceType::YellowPiece:
                        unitPosition = b2Vec2(1, 0);
                        break;
                        
                    case GamePieceType::BluePiece:
                        unitPosition = b2Vec2(1, 1);
                        break;
                        
                    default:
                        break;
                }
                
                b2Vec2 endPosition(unitPosition.x * boardSize.width, unitPosition.y * boardSize.height);
                b2Vec2 piecePosition(piece->getPositionX(), piece->getPositionY());
                b2Vec2 normalVector = (endPosition - piecePosition);
                normalVector.Normalize();
                
                physicsBody->SetLinearVelocity(b2Vec2(normalVector.x * kVelocity.x, normalVector.y * kVelocity.y));
            }
        }

    }
                
    void GravityBonusBehavior::applyGravity(GamePiece* piece)
    {
        
    }
    
    void GravityBonusBehavior::onExpire(MainGameScene* scene)
    {
        auto gameBoard = getGameScene()->getGameBoard();
        auto pieces = gameBoard->getPieces();
        
        for (auto piece : pieces) {
            auto physicsBody = piece->getPhysicsBodyBox2D();
            if (!piece->isDragging() && !piece->isDecelerating()) {
                physicsBody->SetLinearVelocity(b2Vec2(0, 0));
            }
        }
    }
}

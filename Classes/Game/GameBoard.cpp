//
//  GameBoard.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/13/16.
//
//

#include <algorithm>

#include "GameBoard.h"
#include "GamePiece.h"
#include "Literals.h"
#include "Events.h"

namespace flik
{
    static const float kVelocityDamping = 0.7;
    static const int kPieceTag = 0xF00F;
    
    bool GameBoard::init()
    {
        if (!Node::init())
        {
            return false;
        }
        
        auto touchListener = EventListenerTouchAllAtOnce::create();
        
        touchListener->onTouchesBegan = CC_CALLBACK_2(GameBoard::onTouchesBegan, this);
        touchListener->onTouchesEnded = CC_CALLBACK_2(GameBoard::onTouchesEnded, this);
        touchListener->onTouchesMoved = CC_CALLBACK_2(GameBoard::onTouchesMoved, this);
        touchListener->onTouchesCancelled = CC_CALLBACK_2(GameBoard::onTouchesCancelled, this);
        
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        scheduleUpdate();
        
        return true;
    }
    
    void GameBoard::addPiece(GamePiece* piece)
    {
        piece->setTag(kPieceTag);
        addChild(piece);
    }
    
    void GameBoard::update(float seconds)
    {
        Node::update(seconds);
        
        auto visibleBounds = Rect(Vec2(), Director::getInstance()->getOpenGLView()->getDesignResolutionSize());

        for (auto piece : this->getPieces()) {
            bool outsideBounds = !getParent()->getBoundingBox().intersectsRect(piece->getBoundingBox());
            if (outsideBounds) {
                EventCustom eventObj(kPieceRemovedEvent);
                eventObj.setUserData(this);
                
                getEventDispatcher()->dispatchEvent(&eventObj);
                
                piece->removeFromParent();
            }
        }
    }
    
    void GameBoard::clearBoard(bool notify)
    {
        for (auto piece : this->getPieces()) {
            if (notify) {
                EventCustom eventObj(kPieceRemovedEvent);
                eventObj.setUserData(this);
                
                getEventDispatcher()->dispatchEvent(&eventObj);
            }
            
            piece->removeFromParent();
        }
        
    }
    
    bool GameBoard::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
    {
        for (auto touch : touches) {
            auto pieces = this->getPieces();
            for (auto piece = pieces.rbegin(); piece != pieces.rend(); piece++) {
                if ((*piece)->getTouchBoundingBox().containsPoint(touch->getLocation())) {
                    bool found = false;
                    for (auto& selected : mSelectedPieces) {
                        if (selected.piece == *piece) {
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        mSelectedPieces.emplace_back(*piece, touch->getStartLocation());
                        
                        auto& selected = mSelectedPieces.back();
                        selected.velocityTracker.Reset();
                        selected.velocityTracker.AddPoint(touch->getLocation());
                        selected.piece->getPhysicsBody()->setVelocity(Vec2());
                        break;
                    }
                }
            }
        }
        
        return true;
    }
    
    void GameBoard::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
    {
        for (auto touch : touches) {
            for (auto& selected : mSelectedPieces) {
                if (selected.startLocation == touch->getStartLocation()) {
                    selected.velocityTracker.AddPoint(touch->getLocation());
                    selected.piece->setPosition(selected.piece->getPosition() + touch->getDelta());
                    constrainPieceToGameBounds(selected.piece);
                    break;
                }
            }
        }
    }
    
    void GameBoard::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
    {
        for (auto touch : touches) {
            mSelectedPieces.erase(std::remove_if(mSelectedPieces.begin(), mSelectedPieces.end(), [touch](SelectedGamePiece& selected) -> bool {
                bool isTouched = selected.startLocation == touch->getStartLocation();
                if (isTouched) {
                    selected.piece->getPhysicsBody()->setVelocity(selected.velocityTracker.GetVelocity() * kVelocityDamping);
                }
                return isTouched;
            }), mSelectedPieces.end());
        }
        
        
    }
    void GameBoard::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
    {
        onTouchesEnded(touches, unused_event);
    }
    
    void GameBoard::constrainPieceToGameBounds(GamePiece* piece)
    {
        auto boardBounds = this->getBoundingBox();
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
    
    const std::vector<GamePiece*> GameBoard::getPieces()
    {
        std::vector<GamePiece*> pieces;
        for (auto piece : this->getChildren()) {
            if (piece->getTag() == kPieceTag) {
                pieces.push_back(dynamic_cast<GamePiece*>(piece));
            }
        }
        
        return pieces;
    }
}

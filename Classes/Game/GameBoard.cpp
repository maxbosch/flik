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
#include "MainGameScene.h"

namespace flik
{
    static const float kVelocityDamping = 0.4;
    static const int kPieceTag = 0xF00F;
    static const float kMaxVelocity = 1000.0f;
    
    bool GameBoard::init()
    {
        if (!RelativeBox::init())
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
        addChild(piece, mPieceZIndexCounter++);
    }
    
    void GameBoard::update(float seconds)
    {
        Node::update(seconds);
        
        auto visibleBounds = Rect(Vec2(), Director::getInstance()->getOpenGLView()->getDesignResolutionSize());

        for (auto piece : this->getPieces()) {
            bool outsideBounds = !getParent()->getBoundingBox().intersectsRect(piece->getBoundingBox());
            if (outsideBounds) {
                EventCustom eventObj(kPieceRemovedEvent);
                eventObj.setUserData(piece);
                
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
                eventObj.setUserData(piece);
                
                getEventDispatcher()->dispatchEvent(&eventObj);
            }
            
            piece->removeFromParent();
        }
        
    }
    
    bool GameBoard::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
    {
        for (auto touch : touches) {
            auto pieces = this->getPieces();
            pieces.erase(std::remove_if(pieces.begin(), pieces.end(), [this](GamePiece* piece) {
                // Remove any pieces already selected
                for (auto& selected : mSelectedPieces) {
                    if (selected.piece == piece) {
                        return true;
                    }
                }
                
                return false;
            }), pieces.end());
            
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
                        selected.piece->getPhysicsBodyBox2D()->SetLinearVelocity(b2Vec2(0, 0));
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
                    auto lastPosition = selected.piece->getPosition();
                    selected.velocityTracker.AddPoint(touch->getLocation());
                    auto newPosition = lastPosition + touch->getDelta();
                    
                    constrainPieceToGameBounds(selected.piece);
                    if (newPosition.distance(lastPosition) < 75.0_dp) {
                        selected.piece->setPosition(newPosition);
                        
                        auto pieceBounds = selected.piece->getBoundingBox();
                        
                        // if the user tries to drag the piece inside the bounds of a wall, we reject it
                        for (auto child : getChildren()) {
                            auto obstacle = dynamic_cast<PhysicsNode*>(child);
                            if (obstacle && obstacle->getTag() != kPieceTag) {
                                auto obstacleBounds = obstacle->getBoundingBox();
                                if (pieceBounds.intersectsRect(obstacleBounds)) {
                                    Vec2 newPosition;
                                    
                                    float halfWidth = selected.piece->getContentSize().width;
                                    float halfHeight = selected.piece->getContentSize().height;
                                    
                                    if (pieceBounds.getMinX() > obstacleBounds.getMinX() && pieceBounds.getMaxX() < obstacleBounds.getMaxX()) {
                                        newPosition.x = selected.piece->getPositionX();
                                    } else if (pieceBounds.getMinX() < obstacleBounds.getMinX()) {
                                        newPosition.x = obstacleBounds.getMinX() - halfWidth;
                                    } else if (pieceBounds.getMaxX() > obstacleBounds.getMaxX()) {
                                        newPosition.x = obstacleBounds.getMaxX() + halfWidth;
                                    }
                                    
                                    if (pieceBounds.getMinY() > obstacleBounds.getMinY() && pieceBounds.getMaxY() < obstacleBounds.getMaxY()) {
                                        newPosition.y = selected.piece->getPositionY();
                                    } else if (pieceBounds.getMinY() < obstacleBounds.getMinY()) {
                                        newPosition.y = obstacleBounds.getMinY() - halfHeight;
                                    } else if (pieceBounds.getMaxY() > obstacleBounds.getMaxY()) {
                                        newPosition.y = obstacleBounds.getMaxY() + halfHeight;
                                    }
                                    selected.piece->setPosition(newPosition);
                                    
                                    onTouchesEnded(touches, unused_event);
                                    
                                    break;
                                }
                            }
                        }
                    } else {
                        onTouchesEnded(touches, unused_event);
                    }
                    
                    break;
                }
            }
        }
    }
    
    void GameBoard::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
    {
        for (auto touch : touches) {
            mSelectedPieces.erase(std::remove_if(mSelectedPieces.begin(), mSelectedPieces.end(), [this, touch](SelectedGamePiece& selected) -> bool {
                bool isTouched = selected.startLocation == touch->getStartLocation();
                if (isTouched) {
                    onPieceTouchEnd(selected);
                }
                return isTouched;
            }), mSelectedPieces.end());
        }
        
        
    }
    void GameBoard::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
    {
        onTouchesEnded(touches, unused_event);
    }
    
    void GameBoard::forceReleasePiece(GamePiece* piece)
    {
        mSelectedPieces.erase(std::remove_if(mSelectedPieces.begin(), mSelectedPieces.end(), [this, piece](SelectedGamePiece& selected) -> bool {
            if (selected.piece == piece) {
                onPieceTouchEnd(selected);
            }
            return selected.piece == piece;
        }), mSelectedPieces.end());
    }
    
    void GameBoard::onPieceTouchEnd(SelectedGamePiece& selected)
    {
        auto velocity = (selected.velocityTracker.GetVelocity() * kVelocityDamping);
        auto velocityX = std::max(std::min<float>(velocity.x, kMaxVelocity), -kMaxVelocity);
        auto velocityY = std::max(std::min<float>(velocity.y, kMaxVelocity), -kMaxVelocity);
        selected.piece->getPhysicsBodyBox2D()->SetLinearVelocity(b2Vec2(velocityX * kInversePixelsToMeters, velocityY * kInversePixelsToMeters));

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

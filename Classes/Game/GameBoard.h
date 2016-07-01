//
//  GameBoard.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/13/16.
//
//

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "VelocityTracker.h"

namespace flik
{
    class GamePiece;
    
    struct SelectedGamePiece
    {
        GamePiece* piece;
        cocos2d::Vec2 startLocation;
        VelocityTracker velocityTracker;
        
        SelectedGamePiece(GamePiece* _piece, const cocos2d::Vec2& _startLocation):
        piece(_piece), startLocation(_startLocation) {}
    };
    
    class GameBoard : public cocos2d::ui::RelativeBox
    {
    public:
        CREATE_FUNC(GameBoard);
        
        bool init();
        
        void addPiece(GamePiece* piece);
        
        void update(float seconds);
        
        bool onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        
        const std::vector<GamePiece*> getPieces();
        
        void clearBoard(bool notify = false);
        
    private:
        std::vector<SelectedGamePiece> mSelectedPieces;
        
        void constrainPieceToGameBounds(GamePiece* piece);
    };
}
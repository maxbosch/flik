//
//  SideRailNode.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#pragma once

#include <map>

#include "cocos2d.h"
#include "Enums.h"

namespace flik
{
    enum SideRailBox
    {
        RedBox,
        BlueBox,
        PinkBox,
        YellowBox
    };
    
    static const int ColorBoxMasks[] = {
        1 << 1, // Red
        1 << 2, // Blue
        1 << 3, // Pink
        1 << 4  // Yellow
    };
    
    class GoalLayer;
    
    class SideRailNode : public cocos2d::Node
    {
    public:
        
        bool init(const cocos2d::Size& gameBoardSize);
    
        static SideRailNode* create(const cocos2d::Size& gameBoardSize);
        
        GoalLayer* getColorLayer(GamePieceType color) { return mBoxes[color]; }
        
        cocos2d::Rect getInnerBoundingBox() { return mInnerBox->getBoundingBox(); }
        
    private:
        void calculateRails();
        
        std::map<GamePieceType, GoalLayer *> mBoxes;
        cocos2d::LayerColor* mOuterBox;
        cocos2d::LayerColor* mInnerBox;
        cocos2d::Size mBoxDimens;
        double mRailSize;
    };
}
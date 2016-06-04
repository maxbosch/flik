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

namespace flik
{
    enum SideRailBox
    {
        RedBox,
        BlueBox,
        GreenBox,
        YellowBox
    };
    
    static const int ColorBoxMasks[] = {
        1 << 1, // Red
        1 << 2, // Blue
        1 << 3, // Green
        1 << 4  // Yellow
    };
    
    class SideRailNode : public cocos2d::Node
    {
    public:
        bool init();
    
        CREATE_FUNC(SideRailNode);
        
        cocos2d::Rect getInnerBoundingBox() { return mInnerBox->getBoundingBox(); }
        
    private:
        void calculateRails();
        
        std::map<SideRailBox, cocos2d::LayerColor *> mBoxes;
        cocos2d::LayerColor* mOuterBox;
        cocos2d::LayerColor* mInnerBox;
    };
}
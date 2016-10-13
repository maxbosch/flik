//
//  Styles.h
//  Fling
//
//  Created by Adam Eskreis on 5/24/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Util.h"
#include "Fonts.h"

USING_NS_CC;

namespace flik
{
    static const Color3B kBlueColor = Util::getColorFromHex("2086E4");
    static const Color3B kYellowColor = Util::getColorFromHex("FDFF00");
    static const Color3B kGreenColor = Util::getColorFromHex("77C198");
    static const Color3B kRedColor = Util::getColorFromHex("F22239");
    static const Color3B kBlueBorderColor = Util::getColorFromHex("2086E4");
    
    static const Color3B kBlackColor = Util::getColorFromHex("1D0023");
    static const Color3B kGoldColor = Util::getColorFromHex("FBCD89");
    
    static const Color3B kStarColor = Util::getColorFromHex("FAFC02");
    static const Color3B kOrangeColor = Util::getColorFromHex("F5CC94");
    static const Color3B kPinkColor = Util::getColorFromHex("FD02A1");
    
    static const float kTransitionDuration = 0.3;
    
    static const float kOverlayBackgroundOpacity = 0.85 * 255;
}

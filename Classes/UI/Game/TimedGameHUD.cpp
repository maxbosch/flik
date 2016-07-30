//
//  TimedGameHUD.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/3/16.
//
//

#include "TimedGameHUD.h"
#include "ui/CocosGUI.h"
#include "TimedGameMode.h"
#include "MainGameScene.h"
#include <boost/lexical_cast.hpp>
#include "Literals.h"
#include "Styles.h"
#include "Util.h"
#include "TextObjectiveOverlay.h"
#include "LocalizedString.h"

USING_NS_CC;

using RelativeAlign = cocos2d::ui::RelativeLayoutParameter::RelativeAlign;

namespace flik
{
    TimedGameHUD::~TimedGameHUD()
    {
        
    }
    
    bool TimedGameHUD::init()
    {
        if (!MainGameHUD::init())
        {
            return false;
        }
        
        return true;
    }
    
    GameObjectiveOverlay* TimedGameHUD::createObjectiveOverlay()
    {
        return TextObjectiveOverlay::create(LocalizedString::getString("game_mode_timed"), LocalizedString::getString("objective_timed"));
    }
}
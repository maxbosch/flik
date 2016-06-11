//
//  PowerUpButton.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/8/16.
//
//

#include <boost/lexical_cast.hpp>

#include "PowerUpButton.h"
#include "Styles.h"
#include "Literals.h"
#include "Player.h"

USING_NS_CC;

namespace flik
{
    static std::map<PowerUpType, std::string> kPowerUpImages {
        std::pair<PowerUpType, std::string>(PowerUpType::Target, "powerup_target.png"),
        std::pair<PowerUpType, std::string>(PowerUpType::Timestop, "powerup_timestop.png")
    };
    
    PowerUpButton* PowerUpButton::create(PowerUpType type)
    {
        PowerUpButton* widget = new (std::nothrow) PowerUpButton();
        if (widget && widget->initWithType(type))
        {
            widget->autorelease();
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return nullptr;
    }
    
    bool PowerUpButton::initWithType(PowerUpType type)
    {
        mType = type;
        
        auto& image = kPowerUpImages[type];
        
        if (!Button::init(image))
        {
            return false;
        }
        
        setTitleColor(Color3B::WHITE);
        setTitleFontName(kDefaultFont);
        setTitleFontSize(11.0_dp);
        
        setCount(0);
        
        scheduleUpdate();
        
        return true;
    }
    
    void PowerUpButton::setCount(int count)
    {
        setTitleText(boost::lexical_cast<std::string>(count));
        
        getTitleRenderer()->setPosition(getContentSize().width * 0.5, -15.0_dp);
    }
    
    void PowerUpButton::update(float seconds)
    {
        Button::update(seconds);
        
        setCount(Player::getMainPlayer()->getPowerUpCount(mType));
    }
}

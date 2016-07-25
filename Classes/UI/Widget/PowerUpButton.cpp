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
#include "Util.h"

USING_NS_CC;

namespace flik
{
    static std::map<PowerUpType, std::string> kPowerUpImages {
        std::pair<PowerUpType, std::string>(PowerUpType::Target, "powerup_target.png"),
        std::pair<PowerUpType, std::string>(PowerUpType::Timestop, "powerup_timestop.png")
    };
    
    PowerUpButton* PowerUpButton::create(PowerUpType type)
    {
        return createWithParams<PowerUpButton>(type);
    }
    
    bool PowerUpButton::init(PowerUpType type)
    {
        mType = type;
        
        auto& image = kPowerUpImages[type];
        
        if (!Button::init(image))
        {
            return false;
        }
        
        setTitleColor(Color3B::WHITE);
        setTitleFontName(Fonts::getFontForString("1234567890"));
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
    
    void PowerUpButton::onEnter()
    {
        Button::onEnter();
        
        scheduleUpdate();
    }
}

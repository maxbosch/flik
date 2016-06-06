//
//  Player.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#include "Player.h"
#include "cocos2d.h"

USING_NS_CC;

namespace flik
{
    static Player* sPlayerInstance = nullptr;
    
    static std::string kTopScoreKey = "key_topScore";
    
    Player* Player::getMainPlayer()
    {
        if (sPlayerInstance == nullptr) {
            sPlayerInstance = new Player();
        }
        
        return sPlayerInstance;
    }
    
    Player::Player() :
        mCurrentScore(0)
    {
    }
    
    int Player::getTopScore(std::string key)
    {
        auto userDefaults = UserDefault::getInstance();
        return userDefaults->getIntegerForKey((kTopScoreKey + "_" + key).c_str());
    }
    
    void Player::resetScore()
    {
        mCurrentScore = 0;
    }
    
    void Player::addScore(int amount)
    {
        mCurrentScore += amount;
    }
    
    void Player::recordScore(std::string key)
    {
        int topScore = getTopScore(key);
        if (topScore < mCurrentScore) {
            UserDefault::getInstance()->setIntegerForKey((kTopScoreKey + "_" + key).c_str(), mCurrentScore);
        }
    }
}

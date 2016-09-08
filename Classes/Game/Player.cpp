//
//  Player.cpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#include "Player.h"
#include "cocos2d.h"
#include "Achievement.h"
#include "GameServices.h"

USING_NS_CC;

namespace flik
{
    static Player* sPlayerInstance = nullptr;
    
    static std::string kTopScoreKey = "key_topScore";
    static std::map<PowerUpType, std::string> kPowerUpCountKeys {
        std::pair<PowerUpType, std::string>(PowerUpType::Timestop, "key_powerUpTimestopCount"),
        std::pair<PowerUpType, std::string>(PowerUpType::Target, "key_powerUpTargetCount")
    };
    static std::string kCurrencyKey = "key_currency";
    
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
    
    int Player::getPowerUpCount(PowerUpType type)
    {
        return UserDefault::getInstance()->getIntegerForKey(kPowerUpCountKeys[type].c_str(), 0);
    }
    
    void Player::consumePowerUp(PowerUpType type, int count)
    {
        int newCount = getPowerUpCount(type) - count;
        UserDefault::getInstance()->setIntegerForKey(kPowerUpCountKeys[type].c_str(), newCount);
    }
    
    void Player::addPowerUp(PowerUpType type, int count)
    {
        int newCount = getPowerUpCount(type) + count;
        UserDefault::getInstance()->setIntegerForKey(kPowerUpCountKeys[type].c_str(), newCount);
    }
    
    int Player::getCurrencyAmount()
    {
         return UserDefault::getInstance()->getIntegerForKey(kCurrencyKey.c_str(), 0);
    }
    
    void Player::addCurrency(int amount)
    {
        int newCount = getCurrencyAmount() + amount;
        UserDefault::getInstance()->setIntegerForKey(kCurrencyKey.c_str(), newCount);
    }
    
    void Player::removeCurrency(int amount)
    {
        int newCount = getCurrencyAmount() - amount;
        UserDefault::getInstance()->setIntegerForKey(kCurrencyKey.c_str(), newCount);
    }
    
    void Player::handleEndOfGameAchievements(GameModeType type, std::vector<std::string>& earnedAchievements)
    {
        int score = this->getCurrentScore();
        
        std::vector<AchievementIncrement> increments;
        
        switch (type) {
            case GameModeType::Timed:
            {
                sdkbox::PluginSdkboxPlay::submitScore("score_timed", score);
                
                increments.push_back({"play_timed_game_1", 100});
                increments.push_back({"play_timed_game_5", 20});
                increments.push_back({"play_timed_game_20", 5});
                
                if (score >= 25) {
                    increments.push_back({"score_timed_25", 100});
                }
                
                if (score >= 50) {
                    increments.push_back({"score_timed_50", 100});
                }
                
                if (score >= 75) {
                    increments.push_back({"score_timed_75", 100});
                }
                
                if (score >= 100) {
                    increments.push_back({"score_timed_100", 100});
                }
                
                break;
            }
                
            case GameModeType::Unlimited:
            {
                sdkbox::PluginSdkboxPlay::submitScore("score_unlimited", score);
                
                increments.push_back({"play_unlimited_game_1", 100});
                increments.push_back({"play_unlimited_game_5", 20});
                increments.push_back({"play_unlimited_game_20", 5});
                
                if (score >= 50) {
                    sdkbox::PluginSdkboxPlay::unlockAchievement("score_unlimited_50");
                }
                
                if (score >= 100) {
                    sdkbox::PluginSdkboxPlay::unlockAchievement("score_unlimited_100");
                }
                
                if (score >= 150) {
                    sdkbox::PluginSdkboxPlay::unlockAchievement("score_unlimited_150");
                }
                
                if (score >= 200) {
                    sdkbox::PluginSdkboxPlay::unlockAchievement("score_unlimited_200");
                }
                
                break;
            }
 
            default:
                break;
        }
        
        auto gameServices = GameServices::getInstance();
        
        for (auto& increment : increments) {
            sdkbox::PluginSdkboxPlay::incrementAchievement(increment.name, increment.amount);
            
            auto achievement = gameServices->getAchievementByName(increment.name);
            if (achievement) {
                bool wasComplete = gameServices->isComplete(increment.name);
                gameServices->incrementAchievement(increment);
                if (!wasComplete && gameServices->isComplete(increment.name)) {
                    earnedAchievements.push_back(increment.name);
                    addCurrency(achievement->bonus);
                }
            }
        }
    }
}

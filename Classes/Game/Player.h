//
//  Player.hpp
//  Fling
//
//  Created by Adam Eskreis on 5/31/16.
//
//

#pragma once

#include "cocos2d.h"
#include "Enums.h"

#include "PluginSdkboxPlay/PluginSdkboxPlay.h"

namespace flik
{
    static const int kMaxCurrencyAmount = 99999;
    
    class Player
    {
    public:
        static Player* getMainPlayer();
        
        int getTopScore(std::string key);
        
        void resetScore();
        void addScore(int amount);
        int getCurrentScore() { return mCurrentScore; }
        void recordScore(std::string key);
        int getPowerUpCount(BonusType type);
        void consumePowerUp(BonusType type, int count);
        void addPowerUp(BonusType type, int count);
        
        int getCurrencyAmount();
        void addCurrency(int amount);
        void removeCurrency(int amount);
        
        void handleEndOfGameAchievements(GameModeType type, std::vector<std::string>& earnedAchievements);
        
        void setLastBonusChoices(const std::vector<BonusType>& bonuses);
        const std::vector<BonusType>& getLastBonusChoices();
        
    private:
        Player();
        
        int mCurrentScore;
        std::vector<BonusType> mLastBonusChoices;
    };
}

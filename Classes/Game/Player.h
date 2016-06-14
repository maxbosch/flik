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
    
    class Player : public sdkbox::SdkboxPlayListener
    {
    public:
        static Player* getMainPlayer();
        
        int getTopScore(std::string key);
        
        void resetScore();
        void addScore(int amount);
        int getCurrentScore() { return mCurrentScore; }
        void recordScore(std::string key);
        int getPowerUpCount(PowerUpType type);
        void consumePowerUp(PowerUpType type, int count);
        void addPowerUp(PowerUpType type, int count);
        
        int getCurrencyAmount();
        void addCurrency(int amount);
        void removeCurrency(int amount);
        
        void handleEndOfGameAchievements(GameModeType type);
        
        /** SdkboxPlayListener */
        virtual void onConnectionStatusChanged( int status );
        virtual void onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday );
        virtual void onIncrementalAchievementUnlocked( const std::string& achievement_name );
        virtual void onIncrementalAchievementStep( const std::string& achievement_name, int step );
        virtual void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked );
        
        
    private:
        Player();
        
        int mCurrentScore;
    };
}

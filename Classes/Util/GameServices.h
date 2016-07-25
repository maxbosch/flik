//
//  GameServices.hpp
//  Flik
//
//  Created by Adam Eskreis on 7/8/16.
//
//

#pragma once

#include "Achievement.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"

namespace flik
{
    typedef std::vector<Achievement> TAchievementList;
    typedef std::function<void(const TAchievementList& achievements, int error)> TAchievementsCallback;
    
    class GameServices : public sdkbox::SdkboxPlayListener
    {
    public:
        static GameServices* getInstance();
        
        void initialize();
        
        void getAchievements(TAchievementsCallback callback, bool force = false);
        
        /** SdkboxPlayListener */
        void onConnectionStatusChanged( int status );
        void onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday );
        void onIncrementalAchievementUnlocked( const std::string& achievement_name );
        void onIncrementalAchievementStep( const std::string& achievement_name, int step );
        void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked );
        void onAchievementsLoaded( bool reload_forced, const std::string& json_achievements_info );
        
    private:
        GameServices();
        
        TAchievementsCallback mAchievementsCallback;
        TAchievementList mAchievements;
        bool mAchievementsLoaded;
    };
}

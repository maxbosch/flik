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
#include "PluginIAP/PluginIAP.h"
#include <functional>
#include <vector>
#include <string>

namespace flik
{
    typedef std::vector<Achievement> TAchievementList;
    typedef std::vector<LocalAchievement> TLocalAchievementList;
    typedef std::function<void(const TAchievementList& achievements, int error)> TAchievementsCallback;
    typedef std::function<void(const sdkbox::Product&, bool, const std::string&)> TProductPurchaseCallback;
    
    class GameServices : public sdkbox::SdkboxPlayListener, public sdkbox::IAPListener
    {
    public:
        static GameServices* getInstance();
        
        void initialize();
        
        void getAchievements(TAchievementsCallback callback, bool force = false);
        const TLocalAchievementList getLocalAchievements() { return mLocalAchievements; }
        const LocalAchievement* getAchievementByName(const std::string& name);
        
        void incrementAchievement(const AchievementIncrement& increment);
        int getAchievementStatus(const std::string& achievement);
        bool isComplete(const std::string& achievement);
        
        void purchaseProduct(const std::string& name, TProductPurchaseCallback callback);
        
        /** SdkboxPlayListener */
        void onConnectionStatusChanged( int status );
        void onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday );
        void onIncrementalAchievementUnlocked( const std::string& achievement_name );
        void onIncrementalAchievementStep( const std::string& achievement_name, int step );
        void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked );
        void onAchievementsLoaded( bool reload_forced, const std::string& json_achievements_info );
        
        /** IAPListener */
        /**
         * Called when IAP initialized
         */
        virtual void onInitialized(bool success);
        
        /**
         * Called when an IAP processed successfully
         */
        virtual void onSuccess(const sdkbox::Product& p);
        
        /**
         * Called when an IAP fails
         */
        virtual void onFailure(const sdkbox::Product& p, const std::string& msg);
        
        /**
         * Called when user canceled the IAP
         */
        virtual void onCanceled(const sdkbox::Product& p);
        
        /**
         * Called when server returns the IAP items user already purchased
         * @note this callback will be called multiple times if there are multiple IAP
         */
        virtual void onRestored(const sdkbox::Product& p);
        
        /**
         * Called the product request is successful, usually developers use product request to update the latest info(title, price) from IAP
         */
        virtual void onProductRequestSuccess(const std::vector<sdkbox::Product>& products);
        
        /**
         * Called when the product request fails
         */
        virtual void onProductRequestFailure(const std::string& msg);
        
        /**
         * Called when the restore completed
         */
        virtual void onRestoreComplete(bool ok, const std::string &msg);
        
    private:
        GameServices();
        
        TAchievementsCallback mAchievementsCallback;
        TAchievementList mAchievements;
        TLocalAchievementList mLocalAchievements;
        bool mAchievementsLoaded;
        
        TProductPurchaseCallback mProductCallback;
    };
}

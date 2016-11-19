//
//  GameServices.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/8/16.
//
//

#include "GameServices.h"
#include "LocalizedString.h"
#include "Errors.h"
#include <rapidjson/document.h>

USING_NS_CC;

namespace flik
{
    static GameServices* sInstance = nullptr;
    
    GameServices* GameServices::getInstance()
    {
        if (!sInstance) {
            sInstance = new GameServices();
        }
        
        return sInstance;
    }
    
    GameServices::GameServices():
        mAchievementsLoaded(false)
    {
    }
    
    bool GameServices::isComplete(const std::string& achievement)
    {
        return getAchievementStatus(achievement) >= 100;
    }
    
    void GameServices::initialize()
    {
        //sdkbox::PluginSdkboxPlay::init();
        //sdkbox::PluginSdkboxPlay::setListener(this);
        
        //sdkbox::PluginSdkboxPlay::signin();
        
        // Register IAP
        sdkbox::IAP::init();
        sdkbox::IAP::setDebug(true);
        sdkbox::IAP::refresh();
        sdkbox::IAP::setListener(this);
        
        auto achievementJson = cocos2d::FileUtils::getInstance()->getStringFromFile("achievements.json");
        rapidjson::Document doc;
        doc.Parse<0>(achievementJson.c_str());
        if (doc.GetParseError() == rapidjson::ParseErrorCode::kParseErrorNone) {
            auto& achievementsObj = doc["achievements"];
            for (int i = 0; i < achievementsObj.Size(); i++) {
                auto& achievementObj = achievementsObj[i];
                mLocalAchievements.push_back({
                    achievementObj["name"].GetString(),
                    achievementObj["bonus"].GetInt()
                });
            }
        }
    }
    
    const LocalAchievement* GameServices::getAchievementByName(const std::string& name)
    {
        for (auto& achievement : mLocalAchievements) {
            if (achievement.name == name) {
                return &achievement;
            }
        }
        
        return nullptr;
    }
    
    int GameServices::getAchievementStatus(const std::string& achievement)
    {
        return UserDefault::getInstance()->getIntegerForKey(("achievement_percent_" + achievement).c_str(), 0);
    }
    
    void GameServices::getAchievements(TAchievementsCallback callback, bool force)
    {
        if (!mAchievementsLoaded || force) {
            mAchievementsCallback = callback;
            //sdkbox::PluginSdkboxPlay::loadAchievements(true);
        } else {
            if (callback) {
                callback(mAchievements, RESULT_OK);
            }
        }
    }
    
    void GameServices::incrementAchievement(const AchievementIncrement& increment)
    {
        std::string key = "achievement_percent_" + increment.name;
        int currentStatus = getAchievementStatus(increment.name);
        UserDefault::getInstance()->setIntegerForKey(key.c_str(), std::min(100, currentStatus + increment.amount));
    }
    
    void GameServices::purchaseProduct(const std::string& name, TProductPurchaseCallback callback)
    {
        mProductCallback = callback;
        
        sdkbox::IAP::purchase(name);
    }
    
    /** SdkboxPlayListener */
    void GameServices::onConnectionStatusChanged( int status )
    {
        //sdkbox::PluginSdkboxPlay::loadAchievements(true);
    }
    
    void GameServices::onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday )
    {
        
    }
    
    void GameServices::onIncrementalAchievementUnlocked( const std::string& achievement_name )
    {
        
    }
    
    void GameServices::onIncrementalAchievementStep( const std::string& achievement_name, int step )
    {
        
    }
    
    void GameServices::onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked )
    {
        
    }
    
    void GameServices::onAchievementsLoaded( bool reload_forced, const std::string& json_achievements_info )
    {
        if (json_achievements_info.length() > 0) {
            cocos2d::log("Achievements JSON: %s\n", json_achievements_info.c_str());
            rapidjson::Document doc;
            doc.Parse<0>(json_achievements_info.c_str());
            if (doc.GetParseError() != rapidjson::kParseErrorNone) {
                cocos2d::log("RapidJSON parsing error: %d", doc.GetParseError());
                
                if (mAchievementsCallback) {
                    mAchievementsCallback(mAchievements, RESULT_PARSE_FAILED);
                }
            } else {
                if (doc.IsArray()) {
                    mAchievements.resize(doc.Size());
                    for (int i = 0; i < doc.Size(); i++) {
                        auto& achievementJson = doc[i];
                        auto& achievement = mAchievements[i];
                        
                        if (achievementJson.HasMember("id")) {
                            achievement.id = achievementJson["id"].GetString();
                        }
                        
                        if (achievementJson.HasMember("name")) {
                            achievement.name = achievementJson["name"].GetString();
                        }
                        
                        if (achievementJson.HasMember("description")) {
                            achievement.description = achievementJson["description"].GetString();
                        }
                        
                        if (achievementJson.HasMember("state")) {
                            achievement.state = (AchievementState) achievementJson["state"].GetDouble();
                        }
                        
                        if (achievementJson.HasMember("type")) {
                            achievement.type = (AchievementType)achievementJson["type"].GetDouble();
                        }
                        
                        if (achievementJson.HasMember("xp_value")) {
                            achievement.xpValue = achievementJson["xp_value"].GetDouble();
                        }
                        
                        if (achievementJson.HasMember("last_updated_timestamp")) {
                            achievement.lastUpdatedTimestamp = achievementJson["last_updated_timestamp"].GetDouble();
                        }
                        
                        if (achievementJson.HasMember("percentage")) {
                            achievement.percentage = achievementJson["percentgate"].GetDouble();
                        }
                        
                        if (achievementJson.HasMember("total_steps")) {
                            achievement.totalSteps = achievementJson["total_steps"].GetDouble();
                        }
                    }
                    
                    mAchievementsLoaded = true;
                    
                    if (mAchievementsCallback) {
                        mAchievementsCallback(mAchievements, RESULT_OK);
                    }
                } else {
                    if (mAchievementsCallback) {
                        mAchievementsCallback(mAchievements, RESULT_PARSE_FAILED);
                    }
                }
            }
        } else {
            if (mAchievementsCallback) {
                mAchievementsCallback(mAchievements, RESULT_LOAD_FAILED);
            }
        }
    }
    
    /**
     * Called when IAP initialized
     */
    void GameServices::onInitialized(bool success)
    {
        
    }
    
    /**
     * Called when an IAP processed successfully
     */
    void GameServices::onSuccess(const sdkbox::Product& p)
    {
        mProductCallback(p, true, "");
    }
    
    /**
     * Called when an IAP fails
     */
    void GameServices::onFailure(const sdkbox::Product& p, const std::string& msg)
    {
        mProductCallback(p, false, msg);
    }
    
    /**
     * Called when user canceled the IAP
     */
    void GameServices::onCanceled(const sdkbox::Product& p)
    {
        mProductCallback(p, false, "");
    }
    
    /**
     * Called when server returns the IAP items user already purchased
     * @note this callback will be called multiple times if there are multiple IAP
     */
    void GameServices::onRestored(const sdkbox::Product& p)
    {
    }
    
    /**
     * Called the product request is successful, usually developers use product request to update the latest info(title, price) from IAP
     */
    void GameServices::onProductRequestSuccess(const std::vector<sdkbox::Product>& products)
    {
    }
    
    /**
     * Called when the product request fails
     */
    void GameServices::onProductRequestFailure(const std::string& msg)
    {
    }
    
    /**
     * Called when the restore completed
     */
    void GameServices::onRestoreComplete(bool ok, const std::string &msg)
    {
    }
}

//
//  LevelTypes.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#include "cocos2d.h"
#include "LevelTypes.h"
#include "format.h"

#include <rapidjson/document.h>

USING_NS_CC;

namespace flik
{
    static LevelInfo* sInstance = nullptr;
    static const std::string kMaxLevelCompleted = "key_maxLevelCompleted_%d";
    static const std::string kLevelScore = "key_levelScore_%d.%d";
    LevelInfo* LevelInfo::getInstance()
    {
        if (!sInstance) {
            sInstance = new LevelInfo();
        }
        
        return sInstance;
    }
    
    LevelInfo::LevelInfo()
    {
        auto fileInfo = FileUtils::getInstance()->getStringFromFile("levels.json");
        ParseLevels(fileInfo);
    }
    
    bool LevelInfo::isCompleted(int level, int sublevel)
    {
        return getMaxLevelCompleted(level) >= sublevel;
    }
    
    int LevelInfo::getMaxLevelCompleted(int level)
    {
        return UserDefault::getInstance()->getIntegerForKey(fmt::sprintf(kMaxLevelCompleted, level).c_str(), -1);
    }
    
    void LevelInfo::completeLevel(int level, int sublevel, int score)
    {
        if (getMaxLevelCompleted(level) <= sublevel) {
            UserDefault::getInstance()->setIntegerForKey(fmt::sprintf(kMaxLevelCompleted, level).c_str(), sublevel);
        }
    
        if (score > getLevelStatus(level, sublevel)) {
            UserDefault::getInstance()->setIntegerForKey(fmt::sprintf(kLevelScore, level, sublevel).c_str(), score);
        }
    }
    
    const LevelDescription* LevelInfo::getLevelDescription(int level)
    {
        return &mLevels[level];
    }
    
    int LevelInfo::getNextLevel()
    {
        //return std::min(getMaxLevelCompleted() + 1, getMaxLevel());
        return 0;
    }
    
    int LevelInfo::getLevelStatus(int level, int sublevel)
    {
        int maxLevel = getMaxLevelCompleted(level);
        
        if (maxLevel >= sublevel) {
            return getLevelScore(level, sublevel);
        } else if (maxLevel == (sublevel - 1)) {
            return 0;
        } else {
            return -1;
        }
    }
    
    int LevelInfo::getLevelScore(int level, int sublevel)
    {
        return UserDefault::getInstance()->getIntegerForKey(fmt::sprintf(kLevelScore, level, sublevel).c_str(), 0);
    }
    
    void LevelInfo::ParseLevels(const std::string& json)
    {
        rapidjson::Document *doc = new rapidjson::Document;
        doc->Parse<0>(json.c_str());
        if (doc->GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone) {
            // Parse failed, uh oh
            return;
        }
        auto& levels = (*doc)["levels"];
        if (levels.IsArray()) {
            mLevels.resize(levels.Size());
            for (int i = 0; i < levels.Size(); i++) {
                auto& level = levels[i];
                
                auto& levelObj = mLevels[i];
                levelObj.levelNum = i;
                levelObj.data = level;
            }
        }
    }
    
    int LevelInfo::getMaxLevel(int level) {
        auto& levelDesc = mLevels[level];
        auto& sublevels = levelDesc.data["sublevels"];
        return sublevels.Size() - 1;
    }
    
    float LevelInfo::getGameCompletionPercentage(int level)
    {
        int maxLevel = getMaxLevel(level);
        int maxScore = maxLevel;
        int playerScore = 0;
        
        for (int i = 1; i <= maxLevel; i++) {
            int status = getLevelScore(level, i);
            if (status > 0) {
                playerScore += 1;
            }
        }
        
        return (float)playerScore / (float)maxScore;
    }
    
    /** LevelProgress */
    
    void LevelProgress::setLevelDescription(const LevelDescription* levelDesc)
    {
        mLevelDesc = levelDesc;
        
        reset();
    }
    
    bool LevelProgress::isCompleted()
    {
        bool done = true;
        
        for (auto& pair : mObjectiveProgress) {
            if (pair.second > 0) {
                done = false;
                break;
            }
        }
        
        return done;
    }
    
    void LevelProgress::incrementObjective(const std::string& type, int count)
    {
        auto pair = mObjectiveProgress.find(type);
        if (pair != mObjectiveProgress.end()) {
            pair->second -= count;
        }
    }
    
    void LevelProgress::reset()
    {
    }
}

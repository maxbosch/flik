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
    static const std::string kMaxLevelCompleted = "key_maxLevelCompleted";
    
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
    
    bool LevelInfo::isCompleted(int level)
    {
        return getMaxLevelCompleted() >= level;
    }
    
    int LevelInfo::getMaxLevelCompleted()
    {
        return UserDefault::getInstance()->getIntegerForKey(kMaxLevelCompleted.c_str(), 1);
    }
    
    void LevelInfo::completeLevel(int level)
    {
        auto& levelObj = mLevels[level-1];
        auto& sublevels = levelObj.data["sublevels"];
        int newSublevelNum = std::min<int>(sublevels.Size() - 1, getSublevel(level) + 1);
        //return UserDefault::getInstance()->setIntegerForKey(kMaxLevelCompleted.c_str(), getMaxLevelCompleted() + 1);
        UserDefault::getInstance()->setIntegerForKey(fmt::sprintf("sublevel_%d", level).c_str(), newSublevelNum);
        
        mLevels[level - 1].sublevelNum = newSublevelNum;
    }
    
    int LevelInfo::getSublevel(int level)
    {
        return UserDefault::getInstance()->getIntegerForKey(fmt::sprintf("sublevel_%d", level).c_str(), 0);
    }
    
    const LevelDescription* LevelInfo::getLevelDescription(int level)
    {
        return &mLevels[level - 1];
    }
    
    int LevelInfo::getNextLevel()
    {
        return std::min(getMaxLevelCompleted() + 1, getMaxLevel());
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
                levelObj.levelNum = i + 1;
                levelObj.data = level;
                levelObj.sublevelNum = getSublevel(levelObj.levelNum);
            }
        }
    }
    
    int LevelInfo::getMaxLevel() {
        return (int) mLevels.size();
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

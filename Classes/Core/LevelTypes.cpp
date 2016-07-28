//
//  LevelTypes.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#include "cocos2d.h"
#include "LevelTypes.h"

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
        return UserDefault::getInstance()->setIntegerForKey(kMaxLevelCompleted.c_str(), getMaxLevelCompleted() + 1);
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
                levelObj.timeLimit = level["time"].GetInt();
                levelObj.levelNum = i + 1;
                
                if (level.HasMember("obstacles")) {
                    levelObj.obstacles = level["obstacles"];
                }
                
                auto& objectives = level["objectives"];
                if (objectives.IsArray()) {
                    levelObj.objectives.resize(objectives.Size());
                    for (int j = 0; j < objectives.Size(); j++) {
                        auto& objective = objectives[j];
                        
                        auto& objectiveObj = levelObj.objectives[j];
                        
                        objectiveObj.quantity = objective["quantity"].GetInt();
                        
                        std::string type = objective["type"].GetString();
                        if (type == "collect") {
                            objectiveObj.type = ObjectiveType::CollectPiece;
                        } else if (type == "clear") {
                            objectiveObj.type = ObjectiveType::ClearBoard;
                        }
                    }
                }
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
    
    void LevelProgress::incrementObjective(ObjectiveType type, int count)
    {
        auto pair = mObjectiveProgress.find(type);
        if (pair != mObjectiveProgress.end()) {
            pair->second -= count;
        }
    }
    
    void LevelProgress::reset()
    {
        for (auto& objective : mLevelDesc->objectives) {
            mObjectiveProgress[objective.type] = objective.quantity;
        }
    }
    
}

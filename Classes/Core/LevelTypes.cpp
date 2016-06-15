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
        auto fileInfo = FileUtils::getInstance()->getDataFromFile("levels.json");
        ParseLevels(fileInfo.getBytes());
    }
    
    bool LevelInfo::isCompleted(int level)
    {
        return getMaxLevelCompleted() >= level;
    }
    
    int LevelInfo::getMaxLevelCompleted()
    {
        return UserDefault::getInstance()->getIntegerForKey(kMaxLevelCompleted.c_str(), 0);
    }
    
    void LevelInfo::completeLevel(int level)
    {
        return UserDefault::getInstance()->setIntegerForKey(kMaxLevelCompleted.c_str(), getMaxLevelCompleted() + 1);
    }
    
    const LevelDescription& LevelInfo::getLevelDescription(int level)
    {
        return mLevels[level];
    }
    
    void LevelInfo::ParseLevels(const unsigned char* bytes)
    {
        rapidjson::Document doc;
        doc.Parse<0>((const char *)bytes);
        if (doc.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone) {
            // Parse failed, uh oh
            return;
        }
        auto& levels = doc["levels"];
        if (levels.IsArray()) {
            mLevels.resize(levels.Size());
            for (int i = 0; i < levels.Size(); i++) {
                auto& level = levels[i];
                
                auto& levelObj = mLevels[i];
                levelObj.timeLimit = level["time_limit"].GetInt();
                
                auto& objectives = level["objectives"];
                if (objectives.IsArray()) {
                    levelObj.objectives.resize(objectives.Size());
                    for (int j = 0; j < objectives.Size(); j++) {
                        auto& objective = objectives[j];
                        
                        auto& objectiveObj = levelObj.objectives[j];
                        
                        objectiveObj.quantity = objective["quantity"].GetInt();
                        
                        std::string type = objective["type"].GetString();
                        if (type == "red") {
                            objectiveObj.type = PieceType::Red;
                        } else if (type == "blue") {
                            objectiveObj.type = PieceType::Blue;
                        } else if (type == "pink") {
                            objectiveObj.type = PieceType::Pink;
                        } else if (type == "yellow") {
                            objectiveObj.type = PieceType::Yellow;
                        }
                    }
                }
            }
        }
    }
}

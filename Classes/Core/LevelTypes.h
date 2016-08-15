//
//  LevelTypes.h
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#pragma once

#include "Enums.h"
#include <rapidjson/document.h>

namespace flik
{
    static const std::string ObjectiveTypeCollect = "collect";
    static const std::string ObjectiveTypeClear = "clear";

    struct LevelDescription
    {
        int levelNum;
        rapidjson::Value data;
    };
    
    struct ObjectiveIncrementUpdate
    {
        std::string type;
        int increment;
    };
    
    class LevelInfo
    {
    public:
        static LevelInfo* getInstance();
        
        bool isCompleted(int level, int sublevel);
        const LevelDescription* getLevelDescription(int level);
        void completeLevel(int level, int sublevel, int score);
        int getMaxLevelCompleted(int level);
        int getMaxLevel();
        int getNextLevel();
        int getLevelStatus(int level, int sublevel);
        int getLevelScore(int level, int sublevel);
        
    private:
        LevelInfo();
        
        void ParseLevels(const std::string& json);
        
        std::vector<LevelDescription> mLevels;
    };
    
    class LevelProgress
    {
    public:
        void setLevelDescription(const LevelDescription* levelDesc);
        
        void incrementObjective(const std::string& type, int count);
        
        bool isCompleted();
        
        void reset();
        
        
    private:
        std::map<std::string, int> mObjectiveProgress;
        const LevelDescription* mLevelDesc;
    };
}
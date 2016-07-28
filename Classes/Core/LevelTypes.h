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
    enum class ObjectiveType
    {
        CollectPiece,
        ClearBoard
    };
    
    struct LevelObjective
    {
        ObjectiveType type;
        int quantity;
    };
    
    struct LevelDescription
    {
        std::vector<LevelObjective> objectives;
        int timeLimit;
        int levelNum;
        rapidjson::Value obstacles;
    };
    
    struct ObjectiveIncrementUpdate
    {
        ObjectiveType type;
        int increment;
    };
    
    class LevelInfo
    {
    public:
        static LevelInfo* getInstance();
        
        bool isCompleted(int level);
        const LevelDescription* getLevelDescription(int level);
        void completeLevel(int level);
        int getMaxLevelCompleted();
        int getMaxLevel();
        int getNextLevel();
        
    private:
        LevelInfo();
        
        void ParseLevels(const std::string& json);
        
        std::vector<LevelDescription> mLevels;
    };
    
    class LevelProgress
    {
    public:
        void setLevelDescription(const LevelDescription* levelDesc);
        
        void incrementObjective(ObjectiveType type, int count);
        
        bool isCompleted();
        
        void reset();
        
        
    private:
        std::map<ObjectiveType, int> mObjectiveProgress;
        const LevelDescription* mLevelDesc;
    };
}
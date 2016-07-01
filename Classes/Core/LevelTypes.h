//
//  LevelTypes.h
//  Flik
//
//  Created by Adam Eskreis on 6/14/16.
//
//

#pragma once

#include "Enums.h"

namespace flik
{
    enum class ObjectiveType
    {
        CollectPiece
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
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
    struct LevelObjective
    {
        PieceType type;
        int quantity;
    };
    
    struct LevelDescription
    {
        std::vector<LevelObjective> objectives;
        int timeLimit;
    };
    
    class LevelInfo
    {
    public:
        static LevelInfo* getInstance();
        
        bool isCompleted(int level);
        const LevelDescription& getLevelDescription(int level);
        void completeLevel(int level);
        int getMaxLevelCompleted();
        
    private:
        LevelInfo();
        
        void ParseLevels(const unsigned char* bytes);
        
        std::vector<LevelDescription> mLevels;
    };
}
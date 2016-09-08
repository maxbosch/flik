//
//  Achievement.h
//  Flik
//
//  Created by Adam Eskreis on 7/8/16.
//
//

#pragma once

#include <string>

namespace flik
{
    enum class AchievementState
    {
        Revealed = 0,
        Unlocked = 1,
        Hidden = 2
    };
    
    enum class AchievementType
    {
        Standard = 0,
        Incremental = 1
    };
    
    struct AchievementIncrement
    {
        std::string name;
        int amount;
    };
    
    struct LocalAchievement
    {
        std::string name;
        int bonus;
    };
    
    struct Achievement
    {
        std::string id;
        std::string name;
        int32_t xpValue = 0;
        double lastUpdatedTimestamp = 0;
        std::string description;
        AchievementState state = AchievementState::Revealed;
        AchievementType type = AchievementType::Standard;
        double percentage = 0;
        double totalSteps = 0;
        
        /* iOS Only */
        bool replayable = false;
        
        /* Android Only */
        std::string formattedCurrentSteps;
        std::string formattedTotalSteps;
    };
}

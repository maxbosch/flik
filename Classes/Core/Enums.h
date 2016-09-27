//
//  Modes.h
//  Flik
//
//  Created by Adam Eskreis on 6/7/16.
//
//

#pragma once

namespace flik
{
    enum class GameModeType
    {
        Unlimited,
        Timed,
        Levels,
        Tutorial
    };
    
    enum class PowerUpType
    {
        Timestop,
        Target
    };
    
    enum class TutorialArrowPosition
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Hidden
    };
    
    enum class GamePieceType
    {
        RedPiece,
        BluePiece,
        GreenPiece,
        YellowPiece,
        RandomPiece
    };

    enum class BonusType
    {
        None = -1,
        AddTime,
        Ghost,
        DoubleUp,
        Gravity,
        Rainbow,
        Count
    };
    
    static std::map<BonusType, std::string> kBonusStrings {
        std::pair<BonusType, std::string>(BonusType::Ghost, "ghost"),
        std::pair<BonusType, std::string>(BonusType::Rainbow, "rainbow"),
        std::pair<BonusType, std::string>(BonusType::AddTime, "add_time"),
        std::pair<BonusType, std::string>(BonusType::DoubleUp, "double_up"),
        std::pair<BonusType, std::string>(BonusType::Gravity, "gravity")
    };
    
    static std::map<BonusType, int> kBonusCosts {
        std::pair<BonusType, int>(BonusType::Ghost, 500),
        std::pair<BonusType, int>(BonusType::Rainbow, 1000),
        std::pair<BonusType, int>(BonusType::AddTime, 500),
        std::pair<BonusType, int>(BonusType::DoubleUp, 750),
        std::pair<BonusType, int>(BonusType::Gravity, 750)
    };
}

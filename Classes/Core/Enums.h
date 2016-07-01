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
        PinkPiece,
        YellowPiece,
        RandomPiece
    };
}

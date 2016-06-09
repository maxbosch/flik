//
//  Physics.h
//  Fling
//
//  Created by Adam Eskreis on 5/26/16.
//
//

#pragma once

namespace flik
{
    namespace collision
    {
        static const int RedPiece = 1 << 0;
        static const int BluePiece = 1 << 1;
        static const int PinkPiece = 1 << 2;
        static const int YellowPiece = 1 << 3;
        
        static const int AllPieces = RedPiece | BluePiece | PinkPiece | YellowPiece;
        static const int AllButRedPiece = BluePiece | PinkPiece | YellowPiece;
        static const int AllButBluePiece = RedPiece | PinkPiece | YellowPiece;
        static const int AllButPinkPiece = RedPiece | BluePiece | YellowPiece;
        static const int AllButYellowPiece = RedPiece | BluePiece | PinkPiece;
        
        static const int RedRail = 1 << 4;
        static const int BlueRail = 1 << 5;
        static const int PinkRail = 1 << 6;
        static const int YellowRail = 1 << 7;
        static const int BlackRail = 1 << 8;
        
        static const int AllRails = RedRail | BlueRail | PinkRail | YellowRail | BlackRail;
        static const int AllButRedRail = BlueRail | PinkRail | YellowRail | BlackRail;
        static const int AllButBlueRail = RedRail | PinkRail | YellowRail | BlackRail;
        static const int AllButPinkRail = RedRail | BlueRail | YellowRail | BlackRail;
        static const int AllButYellowRail = RedRail | BlueRail | PinkRail | BlackRail;
        
        static const int All = AllRails | AllPieces;
    
        static const int PieceCategoryMasks[] {
            RedPiece,
            BluePiece,
            PinkPiece,
            YellowPiece
        };
        
        static const int PieceContactMasks[] {
            AllButRedRail | AllPieces,
            AllButBlueRail | AllPieces,
            AllButPinkRail | AllPieces,
            AllButYellowRail | AllPieces
        };
        
        static const int PieceCollisionMasks[] {
            AllButRedRail | AllPieces,
            AllButBlueRail | AllPieces,
            AllButPinkRail | AllPieces,
            AllButYellowRail | AllPieces
        };
    }
}

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
        static const int GreenPiece = 1 << 2;
        static const int YellowPiece = 1 << 3;
        
        static const int AllPieces = RedPiece | BluePiece | GreenPiece | YellowPiece;
        static const int AllButRedPiece = BluePiece | GreenPiece | YellowPiece;
        static const int AllButBluePiece = RedPiece | GreenPiece | YellowPiece;
        static const int AllButGreenPiece = RedPiece | BluePiece | YellowPiece;
        static const int AllButYellowPiece = RedPiece | BluePiece | GreenPiece;
        
        static const int RedRail = 1 << 4;
        static const int BlueRail = 1 << 5;
        static const int GreenRail = 1 << 6;
        static const int YellowRail = 1 << 7;
        static const int BlackRail = 1 << 8;
        
        static const int AllRails = RedRail | BlueRail | GreenRail | YellowRail | BlackRail;
        static const int AllButRedRail = BlueRail | GreenRail | YellowRail | BlackRail;
        static const int AllButBlueRail = RedRail | GreenRail | YellowRail | BlackRail;
        static const int AllButGreenRail = RedRail | BlueRail | YellowRail | BlackRail;
        static const int AllButYellowRail = RedRail | BlueRail | GreenRail | BlackRail;
        
        static const int All = AllRails | AllPieces;
    
        static const int PieceCategoryMasks[] {
            RedPiece,
            BluePiece,
            GreenPiece,
            YellowPiece
        };
        
        static const int PieceContactMasks[] {
            AllButRedRail | AllPieces,
            AllButBlueRail | AllPieces,
            AllButGreenRail | AllPieces,
            AllButYellowRail | AllPieces
        };
        
        static const int PieceCollisionMasks[] {
            AllButRedRail | AllPieces,
            AllButBlueRail | AllPieces,
            AllButGreenRail | AllPieces,
            AllButYellowRail | AllPieces
        };
    }
}

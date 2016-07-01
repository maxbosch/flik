//
//  TutorialGameMode.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/29/16.
//
//

#pragma once

#include "cocos2d.h"
#include "GameMode.h"
#include "Enums.h"

namespace flik
{
    class TutorialGameMode : public GameMode
    {
    public:
        CREATE_FUNC(TutorialGameMode);
        
        bool init();
        
        virtual void restartGame();
        
        virtual int getTopScore() { return 0; }
        
        virtual GameModeType getGameModeType() { return GameModeType::Tutorial; }
        
    private:
        int nextPieceId;
        
        void spawnNextPiece();
    };
}

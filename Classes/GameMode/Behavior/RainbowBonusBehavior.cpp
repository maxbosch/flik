//
//  GhostBonusBehavior.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/4/16.
//
//

#include "RainbowBonusBehavior.h"
#include "Util.h"
#include "Events.h"
#include "GamePiece.h"
#include "Physics.h"
#include "Enums.h"
#include "MainGameScene.h"
#include "GoalLayer.h"
#include "format.h"
#include "Styles.h"

USING_NS_CC;

namespace flik
{
    RainbowBonusBehavior* RainbowBonusBehavior::create(MainGameScene* scene, float duration)
    {
        return createWithParams<RainbowBonusBehavior>(scene, duration);
    }
    
    bool RainbowBonusBehavior::init(MainGameScene* scene, float duration)
    {
        if (!Behavior::init(scene, duration))
        {
            return false;
        }
        
        auto layers = std::vector<GoalLayer*> {
            scene->getLayerForColor(GamePieceType::RedPiece),
            scene->getLayerForColor(GamePieceType::BluePiece),
            scene->getLayerForColor(GamePieceType::GreenPiece),
            scene->getLayerForColor(GamePieceType::YellowPiece)
        };
        
        for (auto layer : layers) {
            layer->overrideCollisionFlags(collision::AllPieces, collision::BlackRail, collision::BlackRail);
            
            std::vector<Color3B> colors = { kRedColor, kYellowColor, kGreenColor, kBlueColor };
            std::vector<float> locations = { 0.0f, 0.33f, 0.67f, 1.0f };
            layer->overrideColors(colors, locations);
        }
        
        scheduleOnce([layers](float t) {
            
        }, duration, fmt::sprintf("rainbow_bonus_%d", rand()));
        
        return true;
    }
    
    void RainbowBonusBehavior::onExpire(MainGameScene* scene)
    {
        auto layers = std::vector<GoalLayer*> {
            scene->getLayerForColor(GamePieceType::RedPiece),
            scene->getLayerForColor(GamePieceType::BluePiece),
            scene->getLayerForColor(GamePieceType::GreenPiece),
            scene->getLayerForColor(GamePieceType::YellowPiece)
        };
        
        for (auto layer : layers) {
            layer->resetCollisionFlags();
            layer->resetColor();
        }
    }
}
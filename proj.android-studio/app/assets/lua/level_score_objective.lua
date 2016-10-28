-- Level score objective

require("lua/functions")

local LevelScoreObjective = class("LevelScoreObjective")

function LevelScoreObjective:ctor()
    local eventListener = cc.EventListener:create("event_pieceRemoved", self:onPieceRemoved)
    cc.EventDispatcher.addEventListenerWithFixedPriority(eventListener, 1)
end

function LevelScoreObjective:onPieceRemoved()
    print("A piece removed!")
end

local obj = LevelScoreObjective.new()
print("Created objective object")
//
//  SceneManager.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/28/16.
//
//

#include <queue>
#include "SceneManager.h"

namespace flik
{
    std::stack<Scene*> SceneManager::sSceneStack;
}
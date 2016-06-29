//
//  SceneManager.hpp
//  Flik
//
//  Created by Adam Eskreis on 6/28/16.
//
//

#pragma once

#include <stack>

#include "cocos2d.h"

USING_NS_CC;

namespace flik
{
    class SceneManager
    {
    public:
        static void runWithScene(Scene* scene)
        {
            sSceneStack.push(scene);
            
            Director::getInstance()->runWithScene(scene);
        }
        
        static void pushScene(Scene* scene)
        {
            sSceneStack.push(scene);
            
            Director::getInstance()->pushScene(scene);
        }
        
        template <typename T>
        static void pushSceneWithTransition(Scene* scene, float duration)
        {
            sSceneStack.push(scene);
            
            Director::getInstance()->pushScene(T::create(duration, scene));
        }
        
        static void popScene()
        {
            sSceneStack.pop();
            
            Director::getInstance()->popScene();
        }
        
        template <typename T>
        static void popSceneWithTransition(float duration)
        {
            sSceneStack.pop();
            if (sSceneStack.size() == 0) {
                Director::getInstance()->end();
                return;
            }
            
            auto backScene = sSceneStack.top();
            
            Director::getInstance()->replaceScene(T::create(duration, backScene));
        }
        
        static void replaceScene(Scene* scene)
        {
            sSceneStack.pop();
            sSceneStack.push(scene);
            
            Director::getInstance()->replaceScene(scene);
        }
        
        template <typename T>
        static void replaceSceneWithTransition(Scene* scene, float duration)
        {
            sSceneStack.pop();
            sSceneStack.push(scene);
            
            Director::getInstance()->replaceScene(T::create(duration, scene));
        }
        
        static void popToRootScene()
        {
            Director::getInstance()->popToRootScene();
        }
        
        template <typename T>
        static void popToRootSceneWithTransition(float duration)
        {
            while (sSceneStack.size() > 1) {
                sSceneStack.pop();
            }
            
            auto backScene = sSceneStack.top();
            Director::getInstance()->replaceScene(T::create(duration, backScene));
        }
        
    private:
        static std::stack<Scene*> sSceneStack;
    };
}
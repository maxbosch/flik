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

#include "Animations.h"
#include "SceneEx.h"

USING_NS_CC;

namespace flik
{
    class SceneManager
    {
    public:
        static void runWithScene(Scene* scene)
        {
            sSceneStack.push(scene);
            
            notifySceneDisappeared();
            
            Director::getInstance()->runWithScene(scene);
            
            Animations::onSceneChanged(scene);
            
            notifySceneAppeared(scene);
        }
        
        static void pushScene(Scene* scene)
        {
            sSceneStack.push(scene);
            
            notifySceneDisappeared();
            
            Director::getInstance()->pushScene(scene);
            
            Animations::onSceneChanged(scene);
            
            notifySceneAppeared(scene);
        }
        
        template <typename T>
        static void pushSceneWithTransition(Scene* scene, float duration)
        {
            sSceneStack.push(scene);
            
            notifySceneDisappeared();
            
            Director::getInstance()->pushScene(T::create(duration, scene));
            
            Animations::onSceneChanged(scene);
            
            notifySceneAppeared(scene);
        }
        
        static void popScene()
        {
            sSceneStack.pop();
            if (sSceneStack.size() == 0) {
                Director::getInstance()->end();
                return;
            }
            
            notifySceneDisappeared();
            
            auto backScene = sSceneStack.top();
            
            Director::getInstance()->replaceScene(backScene);
            
            Animations::onSceneChanged(backScene);
            
            notifySceneAppeared(backScene);
        }
        
        template <typename T>
        static void popSceneWithTransition(float duration)
        {
            sSceneStack.pop();
            if (sSceneStack.size() == 0) {
                Director::getInstance()->end();
                return;
            }
            
            notifySceneDisappeared();
            
            auto backScene = sSceneStack.top();
            
            Director::getInstance()->replaceScene(T::create(duration, backScene));
            
            Animations::onSceneChanged(backScene);
            
            notifySceneAppeared(backScene);
        }
        
        static void replaceScene(Scene* scene)
        {
            sSceneStack.pop();
            sSceneStack.push(scene);
            
            notifySceneDisappeared();
            
            Director::getInstance()->replaceScene(scene);
            
            Animations::onSceneChanged(scene);
            
            notifySceneAppeared(scene);
        }
        
        template <typename T>
        static void replaceSceneWithTransition(Scene* scene, float duration)
        {
            sSceneStack.pop();
            sSceneStack.push(scene);
            
            notifySceneDisappeared();
            
            Director::getInstance()->replaceScene(T::create(duration, scene));
            
            Animations::onSceneChanged(scene);
            
            notifySceneAppeared(scene);
        }
        
        static void popToRootScene()
        {
            while (sSceneStack.size() > 1) {
                sSceneStack.pop();
            }
            
            notifySceneDisappeared();
            
            auto backScene = sSceneStack.top();
            Director::getInstance()->replaceScene(backScene);
            
            Animations::onSceneChanged(backScene);
            
            notifySceneAppeared(backScene);
        }
        
        template <typename T>
        static void popToRootSceneWithTransition(float duration)
        {
            while (sSceneStack.size() > 1) {
                sSceneStack.pop();
            }
            
            notifySceneDisappeared();
            
            auto backScene = sSceneStack.top();
            Director::getInstance()->replaceScene(T::create(duration, backScene));
            
            Animations::onSceneChanged(backScene);
            
            notifySceneAppeared(backScene);
            
            notifySceneDisappeared();
        }
        
        static Scene* getActiveScene() {
            if (sSceneStack.size() > 0) {
                return sSceneStack.top();
            }
            
            return nullptr;
        }
        
        static void notifySceneAppeared(Scene* scene) {
            auto sceneEx = dynamic_cast<SceneEx*>(scene);
            if (sceneEx) {
                sceneEx->onAppear();
            }
        }
        
        static void notifySceneDisappeared() {
            auto currentScene = Director::getInstance()->getRunningScene();
            if (currentScene) {
                auto sceneEx = dynamic_cast<SceneEx*>(currentScene);
                if (sceneEx) {
                    sceneEx->onDisappear();
                }
            }
        }
        
    private:
        static std::stack<Scene*> sSceneStack;
    };
}

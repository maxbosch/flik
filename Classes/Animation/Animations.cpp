//
//  Animations.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/1/16.
//
//

#include "Animations.h"
#include "SceneManager.h"

USING_NS_CC;

namespace flik
{
    static const int kAnimationNodeTag = 0x184357;
    
    struct AnimationData
    {
        float duration;
        AnimationStepFunction step;
        AnimationStepFunction complete;
        AnimationCurveFunction curve;
        
        float elapsed = 0;
        
        bool finished = false;
    };
    
    class AnimationNode : public Node
    {
    public:
        CREATE_FUNC(AnimationNode);
        
        bool init()
        {
            if (!Node::init())
            {
                return false;
            }
            
            return true;
        }
        
        void update(float t)
        {
            for (auto& anim : mAnimationData) {
                anim.elapsed += t;
                
                float t = std::min(1.0f, anim.elapsed / anim.duration);
                float curveT = anim.curve(t);
                
                anim.step(curveT);
                
                if (t == 1.0f) {
                    if (anim.complete) {
                        anim.complete(true);
                    }
                    anim.finished = true;
                }
            }
            
            mAnimationData.erase(std::remove_if(mAnimationData.begin(), mAnimationData.end(), [](AnimationData& anim) {
                return anim.finished;
            }), mAnimationData.end());
        }
        
        void addAnimation(float duration, AnimationStepFunction step, AnimationCompleteFunction complete,
                          AnimationCurveFunction curve) {
            mAnimationData.push_back(AnimationData());
            
            auto& animationData = mAnimationData.back();
            animationData.duration = duration;
            animationData.step = step;
            animationData.complete = complete;
            animationData.curve = curve;
        }
        
        void removeFromParent() {
            Node::removeFromParent();
            
            mAnimationData.clear();
        }
        
        static void addAnimationPending(float duration, AnimationStepFunction step, AnimationCompleteFunction complete,
                                 AnimationCurveFunction curve) {
            sPendingAnimations.push_back(AnimationData());
            
            auto& animationData = sPendingAnimations.back();
            animationData.duration = duration;
            animationData.step = step;
            animationData.complete = complete;
            animationData.curve = curve;
        }
        
        std::vector<AnimationData> mAnimationData;
        
        static std::vector<AnimationData> sPendingAnimations;
    };
    
    static AnimationNode* sAnimationNode = AnimationNode::create();
    
    void Animations::animate(float duration, AnimationStepFunction step, AnimationCompleteFunction complete,
                             AnimationCurveFunction curve)
    {
        sAnimationNode->addAnimation(duration, step, complete, curve);
    }
    
    void Animations::onSceneChanged(cocos2d::Scene* scene)
    {
        if (sAnimationNode->getParent() != scene) {
            sAnimationNode->removeFromParent();
            sAnimationNode->retain();
            
            if (scene) {
                scene->addChild(sAnimationNode);
                sAnimationNode->scheduleUpdate();
            }
        }
    }
}

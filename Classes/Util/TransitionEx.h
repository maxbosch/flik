//
//  TransitionSlideOutR.hpp
//  Flik
//
//  Created by Adam Eskreis on 10/12/16.
//
//

#pragma once

#include <cocos2d.h>

namespace cocos2d
{
    class TransitionSlideOutL : public TransitionScene, public TransitionEaseScene
    {
    public:
        /** Creates a transition with duration and incoming scene.
         *
         * @param t Duration time, in seconds.
         * @param scene A given scene.
         * @return A autoreleased TransitionSlideOutL object.
         */
        static TransitionSlideOutL* create(float t, Scene* scene);
        
        virtual ActionInterval* easeActionWithAction(ActionInterval * action) override;
        
        /** Returns the action that will be performed by the incoming and outgoing scene.
         *
         * @return The action that will be performed by the incoming and outgoing scene.
         */
        virtual ActionInterval* action(void);
        
        //
        // Overrides
        //
        virtual void onEnter() override;
        
    CC_CONSTRUCTOR_ACCESS:
        TransitionSlideOutL();
        virtual ~TransitionSlideOutL();
        
    protected:
        /** initializes the scenes */
        virtual void initScenes(void);
        
        virtual void sceneOrder() override;
        
    private:
        CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideOutL);
    };
    
    class TransitionSlideOutR : public TransitionSlideOutL
    {
    public:
        /** Creates a transition with duration and incoming scene.
         *
         * @param t Duration time, in seconds.
         * @param scene A given scene.
         * @return A autoreleased TransitionSlideOutR object.
         */
        static TransitionSlideOutR* create(float t, Scene* scene);
        
        /** Returns the action that will be performed by the incoming and outgoing scene. */
        virtual ActionInterval* action(void) override;
        
    CC_CONSTRUCTOR_ACCESS:
        TransitionSlideOutR();
        virtual ~TransitionSlideOutR();
        
    protected:
        /** initializes the scenes */
        virtual void initScenes(void) override;
        
        virtual void sceneOrder() override;
        
    private:
        CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideOutR);
    };
};

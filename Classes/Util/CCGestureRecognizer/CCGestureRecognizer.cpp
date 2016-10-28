/****************************************************************************
Copyright (c) 2013 Artavazd Barseghyan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCGestureRecognizer.h"

USING_NS_CC;

bool GestureRecognizer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    isRecognizing = false;
    
    setCancelsTouchesInView(false);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GestureRecognizer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GestureRecognizer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GestureRecognizer::onTouchEnded, this);
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GestureRecognizer::setTarget(Ref * tar, SEL_CallFuncO sel)
{
    target = tar;
    selector = sel;
}

void GestureRecognizer::stopTouchesPropagation(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)
{
    //hack! cancel touch so it won't propagate
    
}

void GestureRecognizer::setParent(Node*p)
{
    Layer::setParent(p);
    
    if (p!=NULL) {
        Size size = p->getContentSize();
        setContentSize(size);
        setPosition(p->getPosition());
        frame = p->getBoundingBox();
    }
}


bool GestureRecognizer::isPositionBetweenBounds(Vec2 pos)
{
    return frame.containsPoint(pos);
}

void GestureRecognizer::gestureRecognized(cocos2d::Ref * gesture)
{
    if (target && selector) (target->*selector)(gesture); //call selector
    
    if (lambdaTarget) {
        lambdaTarget(gesture);
    }
}

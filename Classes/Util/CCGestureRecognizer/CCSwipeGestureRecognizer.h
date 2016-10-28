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

#pragma once

#include "CCGestureRecognizer.h"

#include <chrono>

#define kSwipeMaxDuration 300
#define kSwipeMinDistance 60

typedef enum {
    kSwipeGestureRecognizerDirectionRight = 1 << 0,
    kSwipeGestureRecognizerDirectionLeft  = 1 << 1,
    kSwipeGestureRecognizerDirectionUp    = 1 << 2,
    kSwipeGestureRecognizerDirectionDown  = 1 << 3
} SwipeGestureRecognizerDirection;

//this class is used for storing information about the swipe gesture
class Swipe : public cocos2d::Ref
{
public:
    bool init() {return true;}
    CREATE_FUNC(Swipe);
    SwipeGestureRecognizerDirection direction;
    cocos2d::Vec2 location;
};

class SwipeGestureRecognizer : public GestureRecognizer
{
public:
    bool init();

    CREATE_FUNC(SwipeGestureRecognizer);
    
    virtual bool onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
    virtual void onTouchMoved(cocos2d::Touch * pTouch, cocos2d::Event * pEvent){};
    virtual void onTouchEnded(cocos2d::Touch * pTouch, cocos2d::Event * pEvent);
protected:
    CC_SYNTHESIZE(int, direction, Direction);
private:
    cocos2d::Vec2 initialPosition;

    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    TimePoint startTime;
    
    bool checkSwipeDirection(cocos2d::Vec2 p1, cocos2d::Vec2 p2, int & dir);
};

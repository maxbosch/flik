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

#include "CCSwipeGestureRecognizer.h"
#include <iostream>

USING_NS_CC;

bool SwipeGestureRecognizer::init()
{
    if (!GestureRecognizer::init())
    {
        return false;
    }
    
    direction = 0;
    return true;
}

bool SwipeGestureRecognizer::checkSwipeDirection(Vec2 p1, Vec2 p2, int & dir)
{
    bool right = p2.x-p1.x>=kSwipeMinDistance && std::abs(p2.y - p1.y) <= kSwipeMaxOppositeDistance;
    bool left = p1.x-p2.x>=kSwipeMinDistance && std::abs(p2.y - p1.y) <= kSwipeMaxOppositeDistance;
    bool down = p1.y-p2.y>=kSwipeMinDistance && std::abs(p2.x - p1.x) <= kSwipeMaxOppositeDistance;
    bool up = p2.y-p1.y>=kSwipeMinDistance && std::abs(p2.x - p1.x) <= kSwipeMaxOppositeDistance;
    
    if (right) {
        if ((direction & kSwipeGestureRecognizerDirectionRight) == kSwipeGestureRecognizerDirectionRight) {
            dir = kSwipeGestureRecognizerDirectionRight;
            return true;
        }
    }
    else if (left) {
        if ((direction & kSwipeGestureRecognizerDirectionLeft) == kSwipeGestureRecognizerDirectionLeft) {
            dir = kSwipeGestureRecognizerDirectionLeft;
            return true;
        }
    }
    else if (up) {
        if ((direction & kSwipeGestureRecognizerDirectionUp) == kSwipeGestureRecognizerDirectionUp) {
            dir = kSwipeGestureRecognizerDirectionUp;
            return true;
        }
    }
    else if (down) {
        if ((direction & kSwipeGestureRecognizerDirectionDown) == kSwipeGestureRecognizerDirectionDown) {
            dir = kSwipeGestureRecognizerDirectionDown;
            return true;
        }
    }
    
    return false;
}

bool SwipeGestureRecognizer::onTouchBegan(Touch * pTouch, Event * pEvent)
{
    if (isRecognizing) {
        isRecognizing = false;
        return false;
    }
    
    initialPosition = pTouch->getLocation();
    if (!isPositionBetweenBounds(initialPosition)) return false;
    
    startTime = std::chrono::high_resolution_clock::now();
    
    isRecognizing = true;
    return true;
}

void SwipeGestureRecognizer::onTouchEnded(Touch * pTouch, Event * pEvent)
{
    Vec2 finalPosition = pTouch->getLocation();
    if (!isPositionBetweenBounds(finalPosition)) {
        isRecognizing = false;
        return;
    }
    
    //distance between initial and final point of touch
    float distance = initialPosition.distance(finalPosition);
    
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeDiff = currentTime - startTime;
    double duration = timeDiff.count();
    
    //check that minimum distance has been reached
    //check that maximum duration hasn't been reached
    //check if the direction of the swipe is correct
    int dir = getDirection();
    if (distance>=kSwipeMinDistance && duration<=kSwipeMaxDuration && checkSwipeDirection(initialPosition,finalPosition,dir)) {
        Swipe * swipe = Swipe::create();
        swipe->direction = (SwipeGestureRecognizerDirection)dir;
        swipe->location = initialPosition;
        
        gestureRecognized(swipe);
        //if (cancelsTouchesInView) stopTouchesPropagation(createSetWithTouch(pTouch), pEvent); //cancel touch over other views
    }
    
    isRecognizing = false;
}

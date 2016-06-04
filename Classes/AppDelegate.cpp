#include "AppDelegate.h"
#include "MainGameScene.h"
#include "MarathonGameMode.h"
#include "MainGameHUD.h"

USING_NS_CC;

namespace flik
{
    AppDelegate::AppDelegate() {
        
    }
    
    AppDelegate::~AppDelegate()
    {
    }
    
    //if you want a different context,just modify the value of glContextAttrs
    //it will takes effect on all platforms
    void AppDelegate::initGLContextAttrs()
    {
        //set OpenGL context attributions,now can only set six attributions:
        //red,green,blue,alpha,depth,stencil
        GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
        
        GLView::setGLContextAttrs(glContextAttrs);
    }
    
    bool AppDelegate::applicationDidFinishLaunching() {
        // initialize director
        auto director = Director::getInstance();
        auto size = director->getVisibleSize();
        auto aspect = size.height / size.width;
        //auto designSize = Size(640, 1136);
        auto designSize = Size(320, 320 * aspect);
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("Fling", Rect(0, 0, size.width, size.height));
            director->setOpenGLView(glview);
        }
        
        director->getOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
        
        //auto contentScale = Size(size.width / designSize.width, size.height / designSize.height);
        //director->getOpenGLView()->setContentScaleFactor(contentScale.width);
        
        // turn on display FPS
        director->setDisplayStats(true);
        
        // set FPS. the default value is 1.0/60 if you don't call this
        director->setAnimationInterval(1.0 / 60);
        
        FileUtils::getInstance()->addSearchPath("res");
        
        // create a scene. it's an autorelease object
        auto level = MainGameScene::create();
        level->setGameMode(MarathonGameMode::create());
        level->setGameHUD(MainGameHUD::create());
        auto scene = level->createScene();
        
        // run
        director->runWithScene(scene);
        
        return true;
    }
    
    // This function will be called when the app is inactive. When comes a phone call,it's be invoked too
    void AppDelegate::applicationDidEnterBackground() {
        Director::getInstance()->stopAnimation();
        
        // if you use SimpleAudioEngine, it must be pause
        // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    
    // this function will be called when the app is active again
    void AppDelegate::applicationWillEnterForeground() {
        Director::getInstance()->startAnimation();
        
        // if you use SimpleAudioEngine, it must resume here
        // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}



#include "AppDelegate.h"
#include "MainGameScene.h"
#include "MarathonGameMode.h"
#include "TimedGameMode.h"
#include "TimedGameHUD.h"
#include "MainGameHUD.h"
#include "MainMenuScene.h"
#include "Player.h"
#include "SceneManager.h"

#include "PluginSdkboxPlay/PluginSdkboxPlay.h"

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

        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("Fling", Rect(0, 0, size.width, size.height));
            director->setOpenGLView(glview);
        }
        
        sdkbox::PluginSdkboxPlay::init();
        sdkbox::PluginSdkboxPlay::setListener(Player::getMainPlayer());

        auto contentScale = Device::getDPI() / 160.0;
        // turn on display FPS
        //director->setDisplayStats(true);
        
        // set FPS. the default value is 1.0/60 if you don't call this
        director->setAnimationInterval(1.0 / 60);
        auto aspect = size.height / size.width;
        director->getOpenGLView()->setDesignResolutionSize(750, 750 * aspect, ResolutionPolicy::EXACT_FIT);
        //director->setContentScaleFactor(1);
        
        std::vector<std::string> resFolders;
        if (contentScale >= 4.1) {
            resFolders.push_back("4x");
            resFolders.push_back("3x");
            resFolders.push_back("2x");
            resFolders.push_back("1x");
        } else if (contentScale >= 3.1) {
            resFolders.push_back("3x");
            resFolders.push_back("4x");
            resFolders.push_back("2x");
            resFolders.push_back("1x");
        } else if (contentScale >= 2.1) {
            resFolders.push_back("2x");
            resFolders.push_back("3x");
            resFolders.push_back("4x");
            resFolders.push_back("1x");
        } else {
            resFolders.push_back("1x");
            resFolders.push_back("2x");
            resFolders.push_back("3x");
            resFolders.push_back("4x");
        }
        
        FileUtils::getInstance()->setSearchResolutionsOrder(resFolders);
        
        // create a scene. it's an autorelease object
//        auto level = MainGameScene::create();
//        level->setGameMode(MarathonGameMode::create());
//        level->setGameHUD(MainGameHUD::create());
        //level->setGameMode(TimedGameMode::createWithTime(10));
        //level->setGameHUD(TimedGameHUD::create());
        
        /*auto player = Player::getMainPlayer();
        if (player->getPowerUpCount(PowerUpType::Timestop) == 0) {
            player->addPowerUp(PowerUpType::Timestop, 5);
        }
        if (player->getPowerUpCount(PowerUpType::Target) == 0) {
            player->addPowerUp(PowerUpType::Target, 5);
        }*/
        
        auto level = MainMenuScene::create();
        
        
        // run
        SceneManager::runWithScene(level);
        
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



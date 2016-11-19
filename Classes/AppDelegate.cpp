#include "AppDelegate.h"
#include "MainGameScene.h"
#include "MarathonGameMode.h"
#include "TimedGameMode.h"
#include "TimedGameHUD.h"
#include "MainGameHUD.h"
#include "MainMenuScene.h"
#include "Player.h"
#include "SceneManager.h"
#include "TutorialGameMode.h"
#include "TutorialGameHUD.h"
#include "LocalizedString.h"
#include "Fonts.h"

#include "sdkbox/Sdkbox.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#include "GameServices.h"
#include "SceneEx.h"

#include "Analytics.h"

//#include "lua_cocos2dx_auto.hpp"
//#include "CCLuaEngine.h"

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
        
        // Load configuration
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sdkbox::init("f3c8fed09ca10e38e27b888cb9fe7261", "78e4d540c0a089d6");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        sdkbox::init("d372d757b12f6fdfc4972504a8dbe5ab", "3618e189567712b3", "googleplay");
#endif
        
        // Reigster essential services
        LocalizedString::loadStrings();
        Fonts::load();
        GameServices::getInstance()->initialize();
        
        // Register LUA
//        LuaEngine* engine = LuaEngine::getInstance();
//        ScriptEngineManager::getInstance()->setScriptEngine(engine);
//        LuaStack* stack = engine->getLuaStack();
//        lua_State* L = stack->getLuaState();
//        register_all_cocos2dx(L);
        
        // initialize director
        auto director = Director::getInstance();
        auto size = director->getVisibleSize();

        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("Flik", Rect(0, 0, size.width, size.height));
            director->setOpenGLView(glview);
        }

        auto contentScale = Device::getDPI() / 160.0;
        // turn on display FPS
        //director->setDisplayStats(true);
        
        // set FPS. the default value is 1.0/60 if you don't call this
        director->setAnimationInterval(1.0 / 60);
        auto aspect = size.height / size.width;
        director->getOpenGLView()->setDesignResolutionSize(750, 750 * aspect, ResolutionPolicy::EXACT_FIT);
        
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
        
        Scene* level;
        
        int firstLoad = 0;
        
        if (UserDefault::getInstance()->getBoolForKey("installed")) {
            level = MainMenuScene::create();
            firstLoad = 1;
        } else {
            LevelParams params;
            params.hud = TutorialGameHUD::create();
            params.mode = TutorialGameMode::create();
            level = MainGameScene::create(params);
            
            UserDefault::getInstance()->setBoolForKey("installed", true);
            
            Player::getMainPlayer()->addPowerUp(BonusType::AddTime, 1);
            Player::getMainPlayer()->addPowerUp(BonusType::Gravity, 1);
            Player::getMainPlayer()->addPowerUp(BonusType::Rainbow, 1);
            Player::getMainPlayer()->addPowerUp(BonusType::DoubleUp, 1);
            Player::getMainPlayer()->addPowerUp(BonusType::Ghost, 1);
        }
        
        // Set up back button
        auto backListener = EventListenerKeyboard::create();
        backListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
            if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
                auto runningScene = dynamic_cast<SceneEx*>(Director::getInstance()->getRunningScene());
                if (runningScene) {
                    runningScene->onBackPressed();
                }
            }
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(backListener, 1);
        
        // run
        SceneManager::runWithScene(level);
        
        PTree attributes;
        attributes.add("first_load", firstLoad);
        Analytics::logEvent("app_open");
        
        return true;
    }
    
    // This function will be called when the app is inactive. When comes a phone call,it's be invoked too
    void AppDelegate::applicationDidEnterBackground() {
        Director::getInstance()->stopAnimation();
        
        // if you use SimpleAudioEngine, it must be pause
        // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
        Analytics::logEvent("app_minimize");
    }
    
    // this function will be called when the app is active again
    void AppDelegate::applicationWillEnterForeground() {
        Director::getInstance()->startAnimation();
        
        // if you use SimpleAudioEngine, it must resume here
        // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
   
        Analytics::logEvent("app_maximize");
    }
    
    
}



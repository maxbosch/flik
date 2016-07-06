//
//  PlatformUtil.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/27/16.
//
//

#ifdef __APPLE__
// This stuff is so we can keep XCode happy while we write code
#include <JavaVM/jni.h>
#include "JniHelper.h"
#else
// This is what Android will actually use
#include <jni.h>
#include "cocos2d.h"
#endif

#include <boost/format.hpp>

#include "PlatformUtil.h"


namespace flik
{
    static const std::string kPlayStoreBaseUrl = "https://play.google.com/store/apps/details?id=%s&hl=en";
    
    void PlatformUtil::openURL(const std::string& url)
    {
        JNIEnv *env = cocos2d::JniHelper::getEnv();
        if (env) {
            auto clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");
            auto methodId = env->GetStaticMethodID(clazz, "openURL", "(Ljava/lang/String;)V");
            auto urlString = env->NewStringUTF(url.c_str());
            env->CallStaticVoidMethod(clazz, methodId, urlString);
        }
    }
    
    std::string PlatformUtil::getStoreUrl()
    {
        JNIEnv *env = cocos2d::JniHelper::getEnv();
        if (env) {
            auto clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");
            auto methodId = env->GetStaticMethodID(clazz, "getAppPackageName", "()Ljava/lang/String;");
            jstring package = (jstring) env->CallStaticObjectMethod(clazz, methodId);
    
            const char *packageName = env->GetStringUTFChars(package, NULL);
            
            return boost::str(boost::format(kPlayStoreBaseUrl) % packageName);
        }
        
        return "";
    }
    
    void PlatformUtil::presentEmailCompose(const std::string& toAddress, const std::string& subject, const std::string& body)
    {
        JNIEnv *env = cocos2d::JniHelper::getEnv();
        if (env) {
            auto clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");
            auto methodId = env->GetStaticMethodID(clazz, "presentMailIntent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            auto toAddressString = env->NewStringUTF(toAddress.c_str());
            auto subjectString = env->NewStringUTF(subject.c_str());
            auto bodyString = env->NewStringUTF(body.c_str());
            env->CallStaticVoidMethod(clazz, methodId, toAddressString, subjectString, bodyString);
        }
    }
    
    std::string PlatformUtil::getLanguage()
    {
        //Locale.getDefault().getLanguage()
        JNIEnv *env = cocos2d::JniHelper::getEnv();
        if (env) {
            auto clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");
            auto methodId = env->GetStaticMethodID(clazz, "getLanguage", "()Ljava/lang/String;");
            jstring language = (jstring) env->CallStaticObjectMethod(clazz, methodId);
            return env->GetStringUTFChars(language, NULL);;
        }
        
        return "";
    }
}

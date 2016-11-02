//
//  Answers.cpp
//  Flik
//
//  Created by Adam Eskreis on 11/1/16.
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

#include "Analytics.h"
#include <sstream>
#include <boost/property_tree/json_parser.hpp>

namespace flik
{
    void Analytics::logEventInternal(const std::string& eventName, boost::property_tree::ptree& attributes)
    {
        JNIEnv *env = cocos2d::JniHelper::getEnv();
        if (env) {
            auto clazz = env->FindClass("org/cocos2dx/cpp/AppActivity");
            auto methodId = env->GetStaticMethodID(clazz, "logEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
           
            std::stringstream stream;
            boost::property_tree::write_json(stream, attributes);
            
            auto eventNameString = env->NewStringUTF(eventName.c_str());
            auto attributesJsonString = env->NewStringUTF(stream.str().c_str());
            env->CallStaticVoidMethod(clazz, methodId, eventNameString, attributesJsonString);
        }
    }
}

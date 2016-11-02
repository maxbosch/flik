//
//  Answers.h
//  Flik
//
//  Created by Adam Eskreis on 11/1/16.
//
//

#pragma once

#include <boost/property_tree/ptree.hpp>

namespace flik
{
    using PTree = boost::property_tree::ptree;
    
    class Analytics
    {
    public:
        static void logEvent(const std::string& eventName)
        {
            PTree attributes;
            logEvent(eventName, attributes);
        }
        
        static void logEvent(const std::string& eventName, PTree& attributes);
        
    private:
        static void logEventInternal(const std::string& eventName, PTree& attributes);
    };
}

//
//  DialogMessage.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/3/16.
//
//

#include "DialogMessage.h"
#include "Util.h"
#include "Styles.h"
#include "Literals.h"
#include "Fonts.h"

USING_NS_CC;

namespace flik
{
    DialogMessage* DialogMessage::create(const std::string& title, const std::string& message)
    {
        return createWithParams<DialogMessage>(title, message);
    }
    
    bool DialogMessage::init(const std::string& title, const std::string& message)
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        
        
        return true;
    }
}
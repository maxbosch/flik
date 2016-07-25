//
//  Fonts.cpp
//  Flik
//
//  Created by Adam Eskreis on 7/6/16.
//
//

#include "Fonts.h"

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <rapidjson/document.h>

#include <utf8.h>

USING_NS_CC;

namespace flik
{
    static FT_Library sLibrary;
    static std::map<std::string, FT_Face*> sFaces;
    static std::string sFallbackFont = "";
    static const std::string kBasePath = "fonts/";
    
    void Fonts::load()
    {
        auto data = cocos2d::FileUtils::getInstance()->getStringFromFile("fonts.json");
        
        rapidjson::Document doc;
        doc.Parse<0>(data.c_str());
        
        auto& fonts = doc["fonts"];
        
        
        FT_Init_FreeType(&sLibrary);
        
        for (int i = 0; i < fonts.Size(); i++) {
            const std::string& font = FileUtils::getInstance()->fullPathForFilename(kBasePath + fonts[i].GetString());
            
            FT_Face* outFace = new FT_Face;
            int error = FT_New_Face(sLibrary, font.c_str(), 0, outFace);
            if (error != 0) {
                cocos2d::log("Failed to read font: %s", font.c_str());
            }
            sFaces[font] = outFace;
        }
        
        sFallbackFont = kBasePath + doc["fallback"].GetString();
    }
    
    std::string Fonts::getFontForString(const std::string& str)
    {
        std::vector<char32_t> wideStr;
        utf8::utf8to32(str.begin(), str.end(), back_inserter(wideStr));
        
        for (auto& pair : sFaces) {
            auto face = pair.second;
            
            bool hasAllChars = true;
            
            for (char32_t chr : wideStr) {
                int glyphIndex = FT_Get_Char_Index(*face, chr);
                hasAllChars &= glyphIndex > 0;
            }
            
            if (hasAllChars) {
                return pair.first;
            }
        }
        
        return sFallbackFont;
    }
    
    cocos2d::ui::Text* Fonts::createLocalizedText(const std::string& content, float size)
    {
        return cocos2d::ui::Text::create(content, getFontForString(content), size);
    }
}

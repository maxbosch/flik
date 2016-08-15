//
//  BlurredBackgroundWidget.cpp
//  Flik
//
//  Created by Adam Eskreis on 6/21/16.
//
//

#include "BlurredBackgroundWidget.h"

USING_NS_CC;

namespace flik
{
    bool BlurredBackgroundWidget::init()
    {
        if (!RelativeBox::init())
        {
            return false;
        }
        
        auto calculateGaussianWeights = [](const int points, float* weights)
        {
            float dx = 1.0f/float(points-1);
            float sigma = 1.0f/3.0f;
            float norm = 1.0f/(sqrtf(2.0f*M_PI)*sigma*points);
            float divsigma2 = 0.5f/(sigma*sigma);
            weights[0] = 1.0f;
            for (int i = 1; i < points; i++)
            {
                float x = float(i)*dx;
                weights[i] = norm*expf(-x*x*divsigma2);
                weights[0] -= 2.0f*weights[i];
            }
        };
        
        auto applyUniformData = [](Sprite* sprite, Size pixelSize, Point direction, const int radius, float* weights) {
            auto programState = sprite->getGLProgramState();
            programState->setUniformVec2("pixelSize", Vec2(pixelSize.width, pixelSize.height));
            programState->setUniformVec2("direction", Vec2(direction.x, direction.y));
            programState->setUniformInt("radius", radius);
            programState->setUniformFloatv("weights", radius, weights);
        };
        
        auto uiSize = Director::getInstance()->getVisibleSize();
        setContentSize(uiSize);
        
        auto glSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        int len = (int)glSize.width * (int)glSize.height * 4;
        unsigned char* pixels = new unsigned char[len];
        glReadPixels(0, 0, glSize.width, glSize.height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        auto texture = new Texture2D();
        texture->initWithData(pixels, len, Texture2D::PixelFormat::RGBA8888, glSize.width, glSize.height, glSize);
        
        int radius = 20;
        float step = 1;
        float radiusWithStep = radius / step;
        auto pixelSize = Size(step / uiSize.width, step / uiSize.height);
        
        GLfloat* weights = new GLfloat[radius];
        calculateGaussianWeights(radiusWithStep, weights);
        
        GLProgram* blur = new GLProgram();
        std::string blurShader = FileUtils::getInstance()->getStringFromFile("shaders/blur_overlay_frag.glsl");
        blur->initWithByteArrays(ccPositionTextureColor_vert, blurShader.c_str());
        blur->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        blur->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        blur->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        blur->link();
        blur->updateUniforms();

        
        Sprite* stepX = Sprite::createWithTexture(texture);
        stepX->retain();
        stepX->setPosition(Point(0.5f*glSize.width, 0.5f*glSize.height));
        stepX->setFlippedY(true);
        
        stepX->setGLProgram(blur);
        applyUniformData(stepX, pixelSize, Point(1.0f, 0.0f), radiusWithStep, weights);
        
        RenderTexture* rtX = RenderTexture::create(glSize.width, glSize.height);
        rtX->retain();
        rtX->begin();
        stepX->visit();
        rtX->end();
        
        Sprite* stepY = Sprite::createWithTexture(rtX->getSprite()->getTexture());
        stepY->retain();
        stepY->setPosition(Point(0.5f*glSize.width, 0.5f*glSize.height));
        stepY->setFlippedY(true);
        
        GLProgram* blurY = new GLProgram();
        //std::string blurShader = FileUtils::getInstance()->getStringFromFile("shaders/blur_overlay_frag.glsl");
        blurY->initWithByteArrays(ccPositionTextureColor_vert, blurShader.c_str());
        blurY->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        blurY->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        blurY->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        blurY->link();
        blurY->updateUniforms();
        
        stepY->setGLProgram(blurY);
        applyUniformData(stepY, pixelSize, Point(0.0f, 1.0f), radiusWithStep, weights);
        
        RenderTexture* rtY = RenderTexture::create(glSize.width, glSize.height);
        rtY->retain();
        rtY->begin();
        stepY->visit();
        rtY->end();
        
//
//        RenderTexture* renderTexture = RenderTexture::create(glSize.width, glSize.height);
//        
//        
//        auto blurSprite = Sprite::createWithTexture(texture);
//        blurSprite->setFlippedY(true);
//        blurSprite->setPosition(Point(0.5f*glSize.width, 0.5f*glSize.height));
//
//        blurSprite->setGLProgram(blur);
//        applyUniformData(blurSprite, pixelSize, Point(1.0f, 0.0f), radiusWithStep, weights);
//        renderTexture->begin();
//        blurSprite->visit();
//        renderTexture->end();
//        
//        applyUniformData(blurSprite, pixelSize, Point(0.0f, 1.0f), radiusWithStep, weights);
//        renderTexture->begin();
//        blurSprite->visit();
//        renderTexture->end();

        auto sprite = Sprite::createWithTexture(rtY->getSprite()->getTexture());
        sprite->setFlippedY(true);
        sprite->setPosition(Vec2());
        sprite->setAnchorPoint(Vec2());
        sprite->setScale(uiSize.width / glSize.width, uiSize.height / glSize.height);
        
        addChild(sprite);
        
        delete[] pixels;
        
        return true;
    }
}

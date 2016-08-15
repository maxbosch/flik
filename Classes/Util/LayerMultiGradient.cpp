//
//  LayerMultiGradient.cpp
//  Flik
//
//  Created by Adam Eskreis on 8/8/16.
//
//

#include "LayerMultiGradient.h"

USING_NS_CC;

namespace flik
{
    bool LayerMultiGradient::init()
    {
        if (!LayerColor::init())
        {
            return false;
        }
        
        GLProgram* shader = new GLProgram();
        std::string shaderCode = FileUtils::getInstance()->getStringFromFile("shaders/multi_gradient_frag.glsl");
        shader->initWithByteArrays(ccPositionTextureColor_noMVP_vert, shaderCode.c_str());
        shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        shader->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        shader->link();
        shader->updateUniforms();
        
        setGLProgramState(GLProgramState::getOrCreateWithGLProgram(shader));
 
        _squareTexCoords[0] = 0;
        _squareTexCoords[1] = 0;
        _squareTexCoords[2] = 1;
        _squareTexCoords[3] = 0;
        _squareTexCoords[4] = 0;
        _squareTexCoords[5] = 1;
        _squareTexCoords[6] = 1;
        _squareTexCoords[7] = 1;
        
        return true;
    }
    
    void LayerMultiGradient::setColors(std::vector<cocos2d::Color3B> colors, std::vector<float> locations)
    {
        mColors.clear();
        for (auto& color : colors) {
            mColors.push_back(Vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, 1.0));
        }
        mLocations = locations;
    }
    
    void LayerMultiGradient::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        _customCommand.init(_globalZOrder, transform, flags);
        _customCommand.func = CC_CALLBACK_0(LayerMultiGradient::onDraw, this, transform, flags);
        renderer->addCommand(&_customCommand);
        
        for(int i = 0; i < 4; ++i)
        {
            Vec4 pos;
            pos.x = _squareVertices[i].x; pos.y = _squareVertices[i].y; pos.z = _positionZ;
            pos.w = 1;
            _modelViewTransform.transformVector(&pos);
            _noMVPVertices[i] = Vec3(pos.x,pos.y,pos.z)/pos.w;
        }
    }
    
    void LayerMultiGradient::onDraw(const Mat4& transform, uint32_t flags)
    {
        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins(transform);
        getGLProgram()->setUniformLocationWith4fv(getGLProgram()->getUniformLocation("u_colors"), (float *)&mColors[0], (int) mColors.size());
        getGLProgram()->setUniformLocationWith1fv(getGLProgram()->getUniformLocation("u_locations"), (float *)&mLocations[0], (int) mLocations.size());
        getGLProgram()->setUniformLocationWith1f(getGLProgram()->getUniformLocation("u_count"), (float) mColors.size());
        getGLProgram()->setUniformLocationWith2f(getGLProgram()->getUniformLocation("u_anchorPoint"), mDirection.x, mDirection.y);
        
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_TEX_COORD );
        
        //
        // Attributes
        //
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _squareTexCoords);
        
        GL::blendFunc( _blendFunc.src, _blendFunc.dst );
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);
    }
    
    void LayerMultiGradient::setColor(const Color3B& color)
    {
        LayerColor::setColor(color);
        
        std::vector<Color3B> colors { color };
        std::vector<float> locations = { 0 };
        setColors(colors, locations);
    }
}
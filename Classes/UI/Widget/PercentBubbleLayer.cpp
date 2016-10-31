//
//  GLShaderLayer.cpp
//  Flik
//
//  Created by Adam Eskreis on 10/31/16.
//
//

#include "PercentBubbleLayer.h"
#include "Util.h"

USING_NS_CC;

namespace flik
{
    bool PercentBubbleLayer::init()
    {
        if (!Layer::init())
        {
            return false;
        }
        
        mProgram = new GLProgram();
        std::string fragmentShader = FileUtils::getInstance()->getStringFromFile("shaders/percent_bubble_shader.glsl");
        mProgram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, fragmentShader.c_str());
        mProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        mProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        mProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        
        mProgram->link();
        mProgram->updateUniforms();
        setGLProgramState(GLProgramState::getOrCreateWithGLProgram(mProgram));
        
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

    void PercentBubbleLayer::setPercent(float percent)
    {
        mPercent = percent;
    }
    
    void PercentBubbleLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
    {
        _customCommand.init(_globalZOrder, transform, flags);
        _customCommand.func = CC_CALLBACK_0(PercentBubbleLayer::onDraw, this, transform, flags);
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
    
    void PercentBubbleLayer::onDraw(const Mat4& transform, uint32_t flags)
    {
        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins(transform);
        getGLProgram()->setUniformLocationWith1f(getGLProgram()->getUniformLocation("u_percent"), mPercent);
        
        GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD | GL::VERTEX_ATTRIB_FLAG_COLOR );
        
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
}

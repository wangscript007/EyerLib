#include "EyerGL.hpp"

namespace Eyer
{
    EyerGLDraw::EyerGLDraw(EyerString _vertexShaderSrc, EyerString _fragmentShaderSrc)
    {
        vertexShaderSrc = _vertexShaderSrc;
        fragmentShaderSrc = _fragmentShaderSrc;

        program = new EyerGLProgram(vertexShaderSrc, fragmentShaderSrc);
    }

    EyerGLDraw::~EyerGLDraw()
    {
        if(program != nullptr){
            delete program;
            program = nullptr;
        }
    }

    int EyerGLDraw::Init()
    {
        if(program == nullptr){
            return -1;
        }

        program->LinkProgram();

        return 0;
    }

    int EyerGLDraw::SetVAO(EyerGLVAO * vao)
    {
        return 0;
    }

    int EyerGLDraw::Draw()
    {
        return 0;
    }
}
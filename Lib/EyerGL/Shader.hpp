#ifndef	EYER_LIB_GL_SHADER_TEMP_H
#define	EYER_LIB_GL_SHADER_TEMP_H

#include "ShaderH.hpp"

namespace Eyer {

    class GL_SHADER {
    public:
        static char * TEST_VERTEX_SHADER;
        static char * TEST_FRAGMENT_SHADER;
    };


    char * GL_SHADER::TEST_VERTEX_SHADER = SHADER(
            layout (location = 0) in vec3 pos;
            void main(){
                gl_Position = vec4(pos, 1.0);
            }
    );

    char * GL_SHADER::TEST_FRAGMENT_SHADER = SHADER(
             out vec4 color;

             void main()
             {
                 color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
             }
    );

}

#endif
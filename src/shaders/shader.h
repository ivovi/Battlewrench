#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

#include <string.h>
#include <stdio.h>

class Shader{
    public:

        unsigned int ID;

        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        void use(){
            glUseProgram(ID);
        }

        void setBool(const char &name, bool value) const{
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setInt(const char &name, int value) const;
        void setFloat(const char &name, float value) const;
};




#endif
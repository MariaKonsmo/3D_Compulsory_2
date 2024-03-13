#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "VBO.h"

class VAO
{
    public:
        //ID refrence for the Vertex Array Object
        GLuint ID;
        //Constructure that generates a VAO ID,without any inputs
        VAO();

        //then a link vbo function that will take vbo and the layout 
        //Links a VBO Attribute to the VAO using a certain layout
        void LinkAttrib(VBO& VBO, GLuint layout,GLuint numCommponents,GLenum type, GLsizeiptr stride, void*offset);
        //Binds the VAO
        void Bind();
        //Unbinds the VAO
        void Unbind();
        //Deletes the VAO
        void Delete();
};

#endif
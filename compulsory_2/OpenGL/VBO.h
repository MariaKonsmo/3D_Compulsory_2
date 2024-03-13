#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

//creating a VBO class giving it ID variable and a constructure that takes some vertices in their sizing bytes.The size of the vertices is in the gl size iptr
//data type since that is what opengl uses for sizes in bytes
class VBO
{
   public:
	   //Refrence ID of the Vertex Buffr Object
	   GLuint ID;
	   //Constructor that generates a Vertex Buffer Object(VBO) and links it to vertices
	   VBO(GLfloat* vertices, GLsizeiptr size);

	   //Binds the VBO
	   void Bind();
	   //Unbinds the VBO
	   void Unbind();
	   //Delete the VBO
	   void Delete();
};

#endif

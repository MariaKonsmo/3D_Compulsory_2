#include"VBO.h"

//copy paste from main cpp and changing the name of some variables such as VBO to ID 
//Constructor that generates a Vertex Buffer Object(VBO) and links it to vertices
VBO::VBO(GLfloat*vertices,GLsizeiptr size)
{
	//Generate the VBO  with only 1 object 
	glGenBuffers(1, &ID);
	//Bind the VBO specifying it`s a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Introduce the vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

//Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Delete the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
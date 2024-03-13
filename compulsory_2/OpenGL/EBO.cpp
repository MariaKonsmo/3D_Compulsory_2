#include"EBO.h"

//copy paste from main cpp and changing the name of some variables such as EBO to ID 
//Constructor that generates a Element Buffer Object(EBO) and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generate the VBO  with only 1 object 
	glGenBuffers(1, &ID);
	//Bind the VBO specifying it`s a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//Introduce the vertices into VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

//Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

//Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
#include "VAO.h"

//Constructure that generates a VAO ID,without any inputs
VAO::VAO()
{
	glGenVertexArrays(1, &ID);

}
//make sure you bind and unbind the vbo in the linked vbo
//Links a VBO Attribute to the VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numCommponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	//Configure the Vertex Atrribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numCommponents,type,  GL_FALSE, stride, offset);
	//Enable the Vertex Attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

//Binds the VAO
void VAO::Bind()
{
	//Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(ID);
}

//Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}


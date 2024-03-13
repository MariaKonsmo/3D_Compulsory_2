#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

//creating a EBO class giving it ID variable and a constructure that takes some indices in their sizing bytes.The size of the indices is in the gl size iptr
//data type since that is what opengl uses for sizes in bytes
class EBO
{
public:
	//Refrence ID of the Element Buffr Object
	GLuint ID;
	//Constructor that generates a Element Buffer Object(EBO) and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	//Binds the EBO
	void Bind();
	//Unbinds the EBO
	void Unbind();
	//Deletes the EBO
	void Delete();
};

#endif

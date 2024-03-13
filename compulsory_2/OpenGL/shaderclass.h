#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

//need to declare a function that will read the shader text files. it outputs the contents of a text file as a string
std::string get_file_contents(const char* filename);

//declare the shader class which will simply be an openGL shader program
class Shader
{
	//give it a public ID declare(aka refrence), declare a constructure that will take in the shader source codes and functions active and delete
   public:
	   //Refrence ID of the Shader Program
	   GLuint ID;
	   //Constructor that build the Shader Program from 2 different shaders
	   Shader(const char* vertexFile, const char* fragmentFile);

	   //Activates the Shader Program
	   void Active();
	   //Delete the Shader Program
	   void Delete();
   private:
	   // Checks if the different shaders have compiled properly
	   void compileErrors(unsigned int shader, const char* type);

};
#endif
#include"shaderclass.h"


//Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char*filename)
{
	std::ifstream in(filename, std::ios::binary);
	if(in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

//Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile,const char*fragmentFile)
{
	//get the strings from the text files into two variables
	//Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Convert the shader source into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//copy paste all the shader related code from main cpp and modifying it slightly by replacing shader program with ID and replacing vertex shader source 
	// to vertex and fragment source
    //Create Vertex Shader Object and get its refrence
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	//checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	//Create Fragment Shader Object and get its refrence
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Vertex Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	//Create Shader Program Object and get its refrence
	ID = glCreateProgram();
	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Wrap-up/Link all the shader together into Shader Program
	glLinkProgram(ID);
	//checks if Shader linked succesfully
	compileErrors(ID, "PROGRAM");

	//Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

//copy from main.cpp glUseProgram(shaderProgram) in active and glDeleteProgram(shaderProgram) in delete
void Shader::Active()
{
	//Activates the Shader Program
	glUseProgram(ID);
}
void Shader::Delete()
{
	//Delete the Shader Program
	glDeleteProgram(ID);
}

// Checks if the different shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) 
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPLATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}

}

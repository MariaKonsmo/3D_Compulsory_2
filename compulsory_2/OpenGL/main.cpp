#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h.txt>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Kube.h"
#include"Textureh.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	std::vector<TriangleSurface> surfaces; // tillegg 290124
	std::vector<Line> lines; // tillegg 290124
	// Legg inn objekter som skal rendres med push_back
	TriangleSurface triangle;
	surfaces.push_back(triangle);
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
		NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	/////////////////////////////////////////////////////////////////////////////
	// Les inn vertex shader og fragment shader fra fil
	// og gj r n dvendige endringer i koden� �
	////////////////////////////////////////////////////////////////////////////
	std::string vs = readShader("default.vert");
	vertexShaderSource = vs.c_str();
	std::string fs = readShader("default.frag");
	fragmentShaderSource = fs.c_str();
	// build and compile our shader program
	// ------------------------------------

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	// Generates Vertex Array Object and binds it
	//VAO VAO1;
	//VAO1.Bind();

	//// Generates Vertex Buffer Object and links it to vertices
	//VBO VBO1(vertices, sizeof(vertices));
	//// Generates Element Buffer Object and links it to indices
	//EBO EBO1(indices, sizeof(indices));

	//// Links VBO attributes such as coordinates and colors to VAO
	//VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	//VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//// Unbind all to prevent accidentally modifying them
	//VAO1.Unbind();
	//VBO1.Unbind();
	//EBO1.Unbind();

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	unsigned int VBO, VAO;
	// Tillegg 290124: En l kke for� linjeobjekter //////////////////////////////////////////////////////////
		for (auto it = lines.begin(); it != lines.end(); it++) // Tillegg 290124
		{
			//Vertex Array Object - VAO
			glGenVertexArrays(1, &mVAO);
			glBindVertexArray(mVAO);
			//Vertex Buffer Object to hold vertices - VBO
			glGenBuffers(1, &mVBO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, it->mVertices.size() * sizeof(Vertex), it -> mVertices.data(), GL_STATIC_DRAW);
			// 1rst attribute buffer : vertices
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				(GLvoid*)0);
			glEnableVertexAttribArray(0);
			// 2nd attribute buffer : colors
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3
				* sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		}
	// Tillegg 290124: En l kke for� flateobjekter ////////////////////////////////////////////////////////////
		for (auto it = surfaces.begin(); it != surfaces.end(); it++)
		{
			//Vertex Array Object - VAO
			glGenVertexArrays(1, &mVAO);
			glBindVertexArray(mVAO);
			//Vertex Buffer Object to hold vertices - VBO
			glGenBuffers(1, &mVBO);
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, it->mVertices.size() * sizeof(Vertex), it -> mVertices.data(), GL_STATIC_DRAW);
			// 1rst attribute buffer : vertices
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				(GLvoid*)0);
			glEnableVertexAttribArray(0);
			// 2nd attribute buffer : colors
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3
				* sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
			glBindVertexArray(0);
		}
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		///////////////////////////////////////////////////////////////////////////
		//
		// Erstatter den eksisterende koden med l kker for linje- og flateobjekter,�
		// tilsvarende initialiseringen ovenfor
		///////////////////////////////////////////////////////////////////////////
		///
		glBindVertexArray(VAO);
		for (auto it = lines.begin(); it != lines.end(); it++) // Tillegg
			290124
			glDrawArrays(GL_LINE_STRIP, 0, it->mVertices.size());
		for (auto it = surfaces.begin(); it != surfaces.end(); it++) // Tillegg
			290124
			glDrawArrays(GL_TRIANGLES, 0, it->mVertices.size());
		// glfw: swap buffers and poll IO events (keys pressed/released, mousemoved etc.)
		//------------------------------------------------------------------------------ -
			glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//--------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
}
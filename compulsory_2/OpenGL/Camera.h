#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

//camera class
class Camera
{
    //making it public
     public:
         //vector position of the camera
         glm::vec3 Position;
         //vector for the orientation aka direction of the camera
         glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
         //vector for the up direction
         glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0);

         // Prevents the camera from jumping around when first clicking left click
         bool firstClick = true;

         //Now want the place to store our width and height in
         int width;
         int height;

         //Now for the last two variables will be the speed of the camera and the sennsitivity of the camer when looking around
         float speed = 0.1f;
         float sensitivity = 100.0f;

         //make a simple constructor
         Camera(int width, int height, glm::vec3 position);

         //a matrix function which will create and send the view and projection matrices to the shader
         void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
         //and a function to handle all the camera inputs
         void Inputs(GLFWwindow* window);
};
#endif

#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;

}


void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	//initialize the matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//make use of the lookout function. the lookout position takes the position from which you want to look at somthing, the target you want to look at and the
	//up vector. The vector her would be the camera position,the camera position + our orientation and the up vector. The orientation vector is always of
	//length 1 and we`ll be using it as the vector we want to look at.
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	//for the second matrix we`ll do it just like we did in the last tutorial
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	//start with w a s d controls for which we simply need to add or subtract from our position. the speed times the orientation or the right vector which we
	//get by doing a cross product between the up vector and orientation vector. Make sure to use ifs and not else ifs since we want to be able to modify
	//multiple of these at the same time in order to go diagonally. add space for going up and ctrl for going down and make it so that when holding down shift
	//the speed increases and when releasing it it goes back to normal
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.04f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}

	//adding mouse controls so i can look around. add an if and say that if i hold down the left mouse button i want my mouse to dissapear and if i release it
	//i want my mouse to appear again. Creating also two doubles for the x and y positions of the mouse and assing them values using the function glfw get
	//cursor position, plugging in the window and coordinate refrences. Then create two variables for the rotation of our orientation vector and make them
	//equal to the sensitivity of the mouse times their coordinates, but make sure to adjust both coordinates since they normally start in the top left corner
	//but we want them to start in the middle of the screen and be normalized so subtract from them half the height or width and then divide and then divide
	//them by the height or width. In order to prevent the camera from being able to do a barrel roll we want to preemptively calculate the new position of the 
	//orientation around the x axis and if the new angle between the new orientation and the up or negative up vectors is not less or equal than 5 degrees then
	//we assign the new orientation to the orientation. Then we also apply the y rotation to the orientation which we always apply since we want to be able to
	//spin around as much as we want. At the end of the function(første if her nede) we also want to set the position of the mouse to the center of the screen
	//so that the mouse doesnt end up wandering around in a corner and stopping us from freely moving around the camera
	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}


		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}

#include "camera.h"

Camera::Camera(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
	this->firstMouse = true;
	this->lastX = 400;
	this->lastY = 400;
}

Camera::Camera()
{
	this ->cameraPosition = glm::vec3(0.0f, 0.0f, 100.0f);
	this ->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this ->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
	this->firstMouse = true;
	this->lastX = 400;
	this->lastY = 400;
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
	this->firstMouse = true;
	this->lastX = 400;
	this->lastY = 400;
}

Camera::~Camera()
{
}

void Camera::keyboardMoveFront(float cameraSpeed)
{
	cameraPosition += cameraViewDirection * cameraSpeed;
	cameraPosition.y = 1;
}

void Camera::keyboardMoveBack(float cameraSpeed)
{
	cameraPosition -= cameraViewDirection * cameraSpeed;
	cameraPosition.y = 1;
}

void Camera::keyboardMoveLeft(float cameraSpeed)
{
	cameraPosition -= glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * cameraSpeed;
}

void Camera::keyboardMoveRight(float cameraSpeed)
{
	cameraPosition += glm::normalize(glm::cross(cameraViewDirection, cameraUp)) * cameraSpeed;
}

void Camera::keyboardMoveUp(float cameraSpeed)
{
	cameraPosition += cameraUp * cameraSpeed;
}

void Camera::keyboardMoveDown(float cameraSpeed)
{
	cameraPosition -= cameraUp * cameraSpeed;
}

void Camera::rotateOx(float angle)
{	
	cameraViewDirection = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, cameraRight) * glm::vec4(cameraViewDirection, 1))));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraViewDirection));
	cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

void Camera::rotateOy (float angle)
{
	cameraViewDirection = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, cameraUp) * glm::vec4(cameraViewDirection, 1))));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraViewDirection));
	cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->rotationOy += xoffset;
	this->rotationOx += yoffset;

	if (this->rotationOx > 89.0f)
		this->rotationOx = 89.0f;
	if (this->rotationOx < -89.0f)
		this->rotationOx = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(this->rotationOy)) * cos(glm::radians(this->rotationOx));
	direction.y = sin(glm::radians(rotationOx));
	//direction.y = this->cameraViewDirection.y;
	direction.z = sin(glm::radians(this->rotationOy)) * cos(glm::radians(rotationOx));
	this->cameraViewDirection = glm::normalize(direction);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraViewDirection, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraViewDirection()
{
	return cameraViewDirection;
}

glm::vec3 Camera::getCameraUp()
{
	return cameraUp;
}



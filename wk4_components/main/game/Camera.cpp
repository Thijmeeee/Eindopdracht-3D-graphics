#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GLFWwindow* window){}


glm::mat4 Camera::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);

	return ret;
}

void Camera::move(float angle, float fac)
{
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}

void Camera::moveY(float fac)
{
	position.y += fac;
}

void Camera::update(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	rotation.x -= (float)(lastY - y) / 100.0f;
	rotation.y -= (float)(lastX - x) / 100.0f;

	lastX = x;
	lastY = y;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, CAMERA_SPEED);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, CAMERA_SPEED);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, CAMERA_SPEED);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, CAMERA_SPEED);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		moveY(-CAMERA_SPEED);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		moveY(CAMERA_SPEED);
}
#ifdef _DEBUG
#pragma comment(lib, "opencv_world490d")
#else
#pragma comment(lib, "opencv_world490")
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "game/Game.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

Game* game;

int main(void)
{
	
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);
	game = new Game(window);

	tigl::init();
	game->init();

	while (!glfwWindowShouldClose(window))
	{
		game->update();
		game->draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

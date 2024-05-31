#ifdef _DEBUG
#pragma comment(lib, "opencv_world490d")
#else
#pragma comment(lib, "opencv_world490")
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "components/GroundPlaneComponent.h"
#include "components\PlayerComponent.h"
#include "components\CubeComponent.h"
#include "components\MoveToComponent.h"
#include "Camera.h"
#include "GameObject.h"
#include <iostream>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

using tigl::Vertex;

void init();
void update();
void draw();

GLFWwindow* window;
Camera* camera;
bool enable_camera = true;

std::list<std::shared_ptr<GameObject>> objects;
double lastFrameTime = 0;

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

	tigl::init();
	init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::normalize(glm::vec3(1, 1, 1)));
	tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightSpecular(0, glm::vec3(1,1,1));
	tigl::shader->setShinyness(0);

	camera = new Camera(window);

	auto ground_plane = std::make_shared<GameObject>();
	ground_plane->position = glm::vec3(0, 1, 5);
	ground_plane->addComponent(std::make_shared<GroundPlaneComponent>());
	objects.push_back(ground_plane);

	/*for (int i = 0; i < 100; i++)
	{
		auto o = std::make_shared<GameObject>();
		o->position = glm::vec3(rand()%30-15, 1, rand()%30-15);
		o->addComponent(std::make_shared<CubeComponent>(1.0f));
		o->addComponent(std::make_shared<MoveToComponent>());
		o->getComponent<MoveToComponent>()->target = o->position;
		objects.push_back(o);
	}*/

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
			if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
				enable_camera = !enable_camera;
		});
}

void update()
{
	if (enable_camera) camera->update(window);
	double currentFrameTime = glfwGetTime();
	double deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	for (auto& o : objects)
		o->update((float)deltaTime);
}


void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);

	if (enable_camera)
	{
		tigl::shader->setViewMatrix(camera->getMatrix());
	}
	else tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(10,5,5), glm::vec3(10,0,-25), glm::vec3(0,1,0)));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	////temporary draw floor
	//tigl::begin(GL_QUADS);
	//tigl::addVertex(Vertex::PCN(glm::vec3(-50, 0, -50), glm::vec4(1, 0, 0, 1), glm::vec3(0,1,0)));
	//tigl::addVertex(Vertex::PCN(glm::vec3(-50, 0, 50), glm::vec4(0, 1, 0, 1), glm::vec3(0, 1, 0)));
	//tigl::addVertex(Vertex::PCN(glm::vec3(50, 0, 50), glm::vec4(0, 0, 1, 1), glm::vec3(0, 1, 0)));
	//tigl::addVertex(Vertex::PCN(glm::vec3(50, 0, -50), glm::vec4(0, 0, 1, 1), glm::vec3(0, 1, 0)));
	//tigl::end();

	for (auto& o : objects)
		o->draw();
}




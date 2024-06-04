#ifdef _DEBUG
#pragma comment(lib, "opencv_world490d")
#else
#pragma comment(lib, "opencv_world490")
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/GroundPlaneComponent.h"
#include "components\MoveToComponent.h"
#include "Camera.h"
#include "GameObject.h"
#include "components/ArrowComponent.h"
#include "components/ArrowUpdateComponent.h"

#include "components/ModelComponent.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

using tigl::Vertex;

void init_arrows();
void init();
void update();
void draw();
void spawn_random_arrow();

GLFWwindow* window;
Camera* camera;
bool enable_camera = true;

std::list<std::shared_ptr<GameObject>> objects;
std::shared_ptr<ModelComponent> arrowModel;

double lastFrameTime = 0;
float totalGameTime = 10.0f;
float remaingTime = totalGameTime;
float lastSpawnTime = 0;
float spawnInterval = 30.0f;

int gameScore = 0;


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

	tigl::shader->enableFog(true);
	tigl::shader->setFogColor(glm::vec3(171.0f / 255.0, 174.0 / 255.0f, 176.0f / 255.0f));
	tigl::shader->setFogExp(0.05f);

	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::normalize(glm::vec3(1, 1, 1)));
	tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightSpecular(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setShinyness(0);


	camera = new Camera(window);

	auto ground_plane = std::make_shared<GameObject>();
	ground_plane->position = glm::vec3(0, 1, 5);
	ground_plane->addComponent(std::make_shared<GroundPlaneComponent>());
	objects.push_back(ground_plane);

	init_arrows();

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
		if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
			enable_camera = !enable_camera;
	});
}

void init_arrows()
{
	arrowModel = std::make_shared<ModelComponent>("./assets/arrow/Arrow5.obj");
	arrowModel->loadModel();

	auto up = std::make_shared<GameObject>();
	auto down = std::make_shared<GameObject>();
	auto left = std::make_shared<GameObject>();
	auto right = std::make_shared<GameObject>();

	up->addComponent(std::make_shared<ArrowComponent>(ArrowComponent::Direction::UP, arrowModel, false));
	down->addComponent(std::make_shared<ArrowComponent>(ArrowComponent::Direction::DOWN, arrowModel, false));
	left->addComponent(std::make_shared<ArrowComponent>(ArrowComponent::Direction::LEFT, arrowModel, false));
	right->addComponent(std::make_shared<ArrowComponent>(ArrowComponent::Direction::RIGHT, arrowModel, false));

	objects.push_back(up);
	objects.push_back(down);
	objects.push_back(left);
	objects.push_back(right);
}


void update()
{
	if (enable_camera) camera->update(window);

	remaingTime = std::max(0.0f, totalGameTime - (float)glfwGetTime());
	spawnInterval = remaingTime / 10.0f;

	
	float currentFrameTime = (float)glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	if (remaingTime > 2.0f)
	{
		if (currentFrameTime - lastSpawnTime >= spawnInterval)
		{
			spawn_random_arrow();
			lastSpawnTime = currentFrameTime;
		}
	}

	for (auto& o : objects)
	{
		o->update(deltaTime);

		if (o->getComponent<ArrowComponent>() != nullptr && o->getComponent<ArrowComponent>()->playerPressedOnTime) {
			gameScore++;
		}
	}
		
	
	std::cout << gameScore << std::endl;

	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::shared_ptr<GameObject>& o)
	{
		return o->destroy;
	}), objects.end());
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

	else tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(10, 5, 5), glm::vec3(10, 0, -25), glm::vec3(0, 1, 0)));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	for (auto& o : objects)
		o->draw();
}

void spawn_random_arrow()
{
	auto o = std::make_shared<GameObject>();
	o->addComponent(std::make_shared<MoveToComponent>());
	o->getComponent<MoveToComponent>()->target = glm::vec3(0, 0, 27.0f);
	ArrowComponent::Direction direction = static_cast<ArrowComponent::Direction>(rand() % 4);
	o->addComponent(std::make_shared<ArrowComponent>(direction, arrowModel, true));
	o->addComponent(std::make_shared<ArrowUpdateComponent>());
	objects.push_back(o);
}

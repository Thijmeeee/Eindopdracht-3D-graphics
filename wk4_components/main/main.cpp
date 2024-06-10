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

#include "Camera.h"
#include "GameObject.h"
#include "ScoreManager.h"


#include "components/GroundPlaneComponent.h"
#include "components\MoveToComponent.h"
#include "components/ArrowComponent.h"
#include "components/ArrowUpdateComponent.h"
#include "components/NumberComponent.h"

#include "components/ModelComponent.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

using tigl::Vertex;

void init();
void init_models();
void update();
void draw();
void spawnRandomArrow();

GLFWwindow* window;
Camera* camera;
bool enable_camera = true;

std::list<std::shared_ptr<GameObject>> objects;
std::shared_ptr<ModelComponent> arrowModel;

double lastFrameTime = 0;
float totalGameTime = 20.0f;
float remainingTime = totalGameTime;
float lastSpawnTime = 0;
float spawnInterval = 30.0f;

int gameScore = 0;

ScoreManager scoreManager;


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
	tigl::shader->setFogColor(glm::vec3(200.0f / 255.0f, 215.0f / 255.0f, 230.0f / 255.0f));
	tigl::shader->setFogExp(0.02f);

	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::normalize(glm::vec3(1, 1, 1)));
	tigl::shader->setLightAmbient(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightSpecular(0, glm::vec3(1.0f, 1.0f, 1.0f));
	tigl::shader->setShinyness(0);
	camera = new Camera(window);

	auto ground_plane = std::make_shared<GameObject>();
	ground_plane->position = glm::vec3(0, 1, 5);
	ground_plane->addComponent(std::make_shared<GroundPlaneComponent>());
	objects.push_back(ground_plane);

	init_models();

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
		if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
			enable_camera = !enable_camera;
		if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
			remainingTime = totalGameTime;
			lastFrameTime = 0;
			lastSpawnTime = 0;
		}
	});
}

void init_models()
{
	arrowModel = std::make_shared<ModelComponent>("./assets/arrow/Arrow5.obj");
	arrowModel->loadModel();

	auto numberModel = scoreManager.getNumberModel(0);

	auto unitsNumberObject = std::make_shared<GameObject>();
	unitsNumberObject->addComponent(std::make_shared<MoveToComponent>());
	unitsNumberObject->getComponent<MoveToComponent>()->target = glm::vec3(0, 3, -10);
	unitsNumberObject->addComponent(std::make_shared<NumberComponent>(numberModel, true, false));
	objects.push_back(unitsNumberObject);

	auto tensNumberObject = std::make_shared<GameObject>();
	tensNumberObject->addComponent(std::make_shared<MoveToComponent>());
	tensNumberObject->getComponent<MoveToComponent>()->target = glm::vec3(-6, 3, -10); 
	tensNumberObject->addComponent(std::make_shared<NumberComponent>(numberModel, true, true));
	objects.push_back(tensNumberObject);

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

	remainingTime = std::max(0.0f, totalGameTime - (float)glfwGetTime());
	spawnInterval = remainingTime / 10.0f;

	float currentFrameTime = (float)glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	if (remainingTime > 2.0f)
	{
		if (currentFrameTime - lastSpawnTime >= spawnInterval)
		{
			spawnRandomArrow();
			lastSpawnTime = currentFrameTime;
		}
	}

	int units = gameScore % 10;
	int tens = gameScore / 10;

	for (auto& o : objects)
	{
		auto numberComponent = o->getComponent<NumberComponent>();
		if (numberComponent != nullptr) {
			if (numberComponent->tens) {
				numberComponent->numberModel = scoreManager.getNumberModel(tens);
				numberComponent->shouldBeVisible = true;
			}
			else {
				numberComponent->numberModel = scoreManager.getNumberModel(units);
				numberComponent->shouldBeVisible = true;
			}
		}

		o->update(deltaTime);

		auto arrowComponent = o->getComponent<ArrowComponent>();
		if (arrowComponent != nullptr && arrowComponent->playerPressedOnTime) {
			gameScore++;
		}
	}
		
	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::shared_ptr<GameObject>& o)
	{
		return o->destroy;
	}), objects.end());
}


void draw()
{
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);

	if (enable_camera)
	{
		tigl::shader->setViewMatrix(camera->getMatrix());
	}

	else tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(10, 5, 5), glm::vec3(10, 0, -15), glm::vec3(0, 1, 0)));
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	//tigl::shader->enableColorMult(true);

	for (auto& o : objects)
	{
		if (o->getComponent<NumberComponent>() != nullptr) {
				o->draw();
				continue;
		}
		o->draw();
	}
}

void spawnRandomArrow()
{
	auto o = std::make_shared<GameObject>();
	o->addComponent(std::make_shared<MoveToComponent>());
	o->getComponent<MoveToComponent>()->target = glm::vec3(0, 0, 27.0f);
	ArrowComponent::Direction direction = static_cast<ArrowComponent::Direction>(rand() % 4);
	o->addComponent(std::make_shared<ArrowComponent>(direction, arrowModel, true));
	o->addComponent(std::make_shared<ArrowUpdateComponent>());
	objects.push_back(o);
}

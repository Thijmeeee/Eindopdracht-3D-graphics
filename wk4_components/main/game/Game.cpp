#include "Game.h"
#include <main/components/HeartComponent.h>

bool enable_camera = false;
Test test;
int heartsLostCount = 0;

Game::Game(GLFWwindow* window) : window(window) {}

void Game::init_models() {
	// INIT GROUND PLANE
	auto ground_plane = std::make_shared<GameObject>();
	ground_plane->position = glm::vec3(0, 1, 5);
	ground_plane->addComponent(std::make_shared<GroundPlaneComponent>());
	objects.push_back(ground_plane);

	// INIT MODELS
	arrowModel = std::make_shared<ModelComponent>("./assets/arrow/Arrow5.obj");
	auto heartModel = std::make_shared<ModelComponent>("./assets/heart/heart.obj");
	arrowModel->loadModel();
	heartModel->loadModel();

	auto numberModel = scoreManager.getNumberModel(0);

	// INIT UNITS = SCOREBOARD
	auto unitsNumberObject = std::make_shared<GameObject>();
	unitsNumberObject->addComponent(std::make_shared<NumberComponent>(numberModel, true, NumberComponent::UNIT));
	unitsNumberObject->getComponent<NumberComponent>()->setPosition(glm::vec3(0, 3, -15));
	objects.push_back(unitsNumberObject);

	auto tensNumberObject = std::make_shared<GameObject>();
	tensNumberObject->addComponent(std::make_shared<NumberComponent>(numberModel, false, NumberComponent::TENS));
	tensNumberObject->getComponent<NumberComponent>()->setPosition(glm::vec3(-6, 3, -15));
	objects.push_back(tensNumberObject);

	auto hundersNumberObject = std::make_shared<GameObject>();
	hundersNumberObject->addComponent(std::make_shared<NumberComponent>(numberModel, false, NumberComponent::HUNDERDS));
	hundersNumberObject->getComponent<NumberComponent>()->setPosition(glm::vec3(-12, 3, -15));
	objects.push_back(hundersNumberObject);

	// INIT STANDARD ARROWS
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

	// INIT HEARTS

	for (int i = 0; i < TOTAL_HEARTS; i++) {
		auto heart = std::make_shared<GameObject>();
		heart->addComponent(std::make_shared<HeartComponent>(heartModel));
		heart->getComponent<HeartComponent>()->setPosition(glm::vec3(10 + (i * 5), 10, -15));
		hearts.push_back(heart);
	}

}

void Game::init() {
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

	init_models();

	test.TestListNotEmpty(objects);
	test.TestCountOfObjectList(objects);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
			if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) 
				enable_camera = !enable_camera; 
		});
}

void Game::update() {
	if (enable_camera) camera->update(window);

	if (spawnInterval > minimumSpawnInterval) {
		spawnInterval -= INCREASE_DIFFICULTY_NUMBER;
	}
	else spawnInterval = minimumSpawnInterval;

	float currentFrameTime = (float)glfwGetTime();
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	if (currentFrameTime - lastSpawnTime >= spawnInterval)
	{
		spawnRandomArrow();
		lastSpawnTime = currentFrameTime;
	}

	int units = gameScore % 10;
	int tens = (gameScore / 10) % 10;
	int hundreds = gameScore / 100;

	for (auto& o : objects)
	{
		auto numberComponent = o->getComponent<NumberComponent>();
		if (numberComponent != nullptr) {
			if (numberComponent->unit == NumberComponent::HUNDERDS) {
				if (hundreds > 0) {
					numberComponent->numberModel = scoreManager.getNumberModel(hundreds);
					numberComponent->shouldBeVisible = true;
				}
			}
			else if (numberComponent->unit == NumberComponent::TENS){
					numberComponent->numberModel = scoreManager.getNumberModel(tens);
					numberComponent->shouldBeVisible = true;
			}
			else {
				numberComponent->numberModel = scoreManager.getNumberModel(units);
			}
		}

		o->update(deltaTime);

		auto arrowComponent = o->getComponent<ArrowComponent>();
		if (arrowComponent != nullptr) {
			if (arrowComponent->playerPressedOnTime) {
				gameScore++;
			}

			if (arrowComponent->missed) {
				for (auto& h : hearts) {
					auto heart = h->getComponent<HeartComponent>();
					if (!(heart->lifeLost)) {
						heart->lifeLost = true;
						heartsLostCount++;
						break;
					}
				}
			}
		}
	}

	objects.erase(std::remove_if(objects.begin(), objects.end(), [](const std::shared_ptr<GameObject>& o)
		{
			return o->destroy;
		}), objects.end());

	if (heartsLostCount == TOTAL_HEARTS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Game::draw() {
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

	std::for_each(objects.begin(), objects.end(), [](std::shared_ptr<GameObject> o) {
		if (o->getComponent<NumberComponent>() != nullptr && !(o->getComponent<NumberComponent>()->shouldBeVisible)) {
			return;
		}

		o->draw();
	});

	std::for_each(hearts.begin(), hearts.end(), [](std::shared_ptr<GameObject> o) {
		o->draw();
	});
}

void Game::spawnRandomArrow() {
	auto o = std::make_shared<GameObject>();
	o->addComponent(std::make_shared<MoveToComponent>());
	o->getComponent<MoveToComponent>()->target = glm::vec3(0, 0, 27.0f);
	ArrowComponent::Direction direction = static_cast<ArrowComponent::Direction>(rand() % 4);
	o->addComponent(std::make_shared<ArrowComponent>(direction, arrowModel, true));
	o->addComponent(std::make_shared<ArrowUpdateComponent>());
	objects.push_back(o);
}



#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "lib/tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "ScoreManager.h"

#include "../components/GroundPlaneComponent.h"
#include "../components/MoveToComponent.h"
#include "../components/ArrowComponent.h"
#include "../components/ArrowUpdateComponent.h"
#include "../components/NumberComponent.h"

#include "../components/ModelComponent.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "lib/stb_image.h"
#include "../test/Test.h"
#include <algorithm>

using tigl::Vertex;

class Game
{
public:
	Game(GLFWwindow* window);
	~Game() = default;

	void init_models();
	void init();
	void update();
	void draw();
	void spawnRandomArrow();

private:

	std::list<std::shared_ptr<GameObject>> objects;
	std::shared_ptr<ModelComponent> arrowModel;

	ScoreManager scoreManager;
	GLFWwindow* window;
	Camera* camera;

	const float INCREASE_DIFFICULTY_NUMBER = 0.001;

	double lastFrameTime = 0;
	float lastSpawnTime = 0;
	float minimumSpawnInterval = 0.4f;
	float spawnInterval = 2.0f;

	int gameScore = 99;

};


#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "ScoreManager.h"

#include "components/GroundPlaneComponent.h"
#include "components/MoveToComponent.h"
#include "components/ArrowComponent.h"
#include "components/ArrowUpdateComponent.h"
#include "components/NumberComponent.h"

#include "components/ModelComponent.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_image.h"

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

	double lastFrameTime = 0;
	float totalGameTime = 20.0f;
	float remainingTime = totalGameTime;
	float lastSpawnTime = 0;
	float spawnInterval = 30.0f;

	int gameScore = 0;

};


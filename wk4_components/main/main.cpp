
#define _CRT_SECURE_NO_WARNINGS
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
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")



GLuint texId;
stbtt_bakedchar cdata[96];
std::string text = "Hello world";

using tigl::Vertex;

void init();
void init_arrows();
void init_font();
void update();
void draw();
void drawFont();
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
	init_font();

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

void init_font() {
	unsigned char* ttf_buffer = new unsigned char[1 << 20];
	unsigned char* temp_bitmap = new unsigned char[512 * 512];
	fread(ttf_buffer, 1, 1 << 20, fopen("C:\\Windows\\Fonts\\arial.ttf", "rb"));
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete[] ttf_buffer;
	delete[] temp_bitmap;
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

	tigl::shader->enableColor(false);
	tigl::shader->enableLighting(false);
	tigl::shader->enableTexture(true);
	tigl::shader->enableColorMult(false);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texId);

	drawFont();

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(true);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColorMult(true);

	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO); 
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0); 

	for (auto& o : objects)
		o->draw();

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

void drawFont() {
	float x = 30, y = 5;
	stbtt_aligned_quad q;
	tigl::begin(GL_QUADS);
	for (int i = 0; i < text.size(); i++) {
		if (text[i] >= 32 && text[i] < 128) {
			stbtt_GetBakedQuad(cdata, 512, 512, text[i] - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
			tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y1, 0), glm::vec2(q.s0, q.t0)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y1, 0), glm::vec2(q.s1, q.t0)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y0, 0), glm::vec2(q.s1, q.t1)));
			tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y0, 0), glm::vec2(q.s0, q.t1)));
		}
	}
	tigl::end();

}

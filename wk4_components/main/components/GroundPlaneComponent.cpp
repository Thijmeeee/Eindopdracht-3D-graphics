#include "GroundPlaneComponent.h"

GroundPlaneComponent::GroundPlaneComponent()
{
	glm::vec4 redColor(101.0f / 255.0f, 36.0f / 255.0f, 49.0f / 255.0f, 0);
	glm::vec4 blueColor(0.0f, 26.0f / 255.0f, 101.0f / 255.0f, 0);
	glm::vec4 cyanColor(0.0f, 205.0f / 255.0f, 194.0f / 255.0f, 0);
	glm::vec4 orangeColor(1.0f, 174.0f / 255.0f, 62.0f / 255.0f, 0);

	// Base ground plane
	verts.push_back(Vertex::PC(glm::vec3(4, -1, 0), blueColor));
	verts.push_back(Vertex::PC(glm::vec3(16, -1, 0), redColor));
	verts.push_back(Vertex::PC(glm::vec3(16, -1, -100), redColor));
	verts.push_back(Vertex::PC(glm::vec3(4, -1, -100), blueColor));

	// Cyan stripe
	verts.push_back(Vertex::PC(glm::vec3(6, -0.9f, 0), cyanColor));
	verts.push_back(Vertex::PC(glm::vec3(6.2f, -0.9f, 0), cyanColor));
	verts.push_back(Vertex::PC(glm::vec3(6.2f, -0.9f, -100), cyanColor));
	verts.push_back(Vertex::PC(glm::vec3(6, -0.9f, -100), cyanColor));

	// Orange stripe
	verts.push_back(Vertex::PC(glm::vec3(14, -0.9f, 0), orangeColor));
	verts.push_back(Vertex::PC(glm::vec3(13.8f, -0.9f, 0), orangeColor));
	verts.push_back(Vertex::PC(glm::vec3(13.8f, -0.9f, -100), orangeColor));
	verts.push_back(Vertex::PC(glm::vec3(14, -0.9f, -100), orangeColor));

	// Left black border
	verts.push_back(Vertex::PC(glm::vec3(4, -1, 0), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(3.8f, -1, 0), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(3.8f, -1, -100), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(4, -1, -100), glm::vec4(0)));

	// Right black border
	verts.push_back(Vertex::PC(glm::vec3(16, -1, 0), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(16.2f, -1, 0), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(16.2f, -1, -100), glm::vec4(0)));
	verts.push_back(Vertex::PC(glm::vec3(16, -1, -100), glm::vec4(0)));
}

GroundPlaneComponent::~GroundPlaneComponent() = default;

void GroundPlaneComponent::draw()
{
	tigl::drawVertices(GL_QUADS, verts);
}

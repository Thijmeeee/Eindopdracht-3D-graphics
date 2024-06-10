#include "GroundPlaneComponent.h"

GroundPlaneComponent::GroundPlaneComponent()
{
    glm::vec4 darkBlueColor(0.0f, 0.0f, 0.2f, 0);
    glm::vec4 blueColor(0.0f, 0.0f, 0.5f, 0);
    glm::vec4 orangeColor(1.0f, 0.5f, 0.0f, 0);

    // Basis grondvlak
    verts.push_back(Vertex::PC(glm::vec3(4, -1, 0), blueColor));
    verts.push_back(Vertex::PC(glm::vec3(16, -1, 0), darkBlueColor));
    verts.push_back(Vertex::PC(glm::vec3(16, -1, -100), darkBlueColor));
    verts.push_back(Vertex::PC(glm::vec3(4, -1, -100), blueColor));

    // Oranje strook
    verts.push_back(Vertex::PC(glm::vec3(6, -0.9f, 0), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(6.2f, -0.9f, 0), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(6.2f, -0.9f, -100), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(6, -0.9f, -100), orangeColor));

    // Oranje strook
    verts.push_back(Vertex::PC(glm::vec3(14, -0.9f, 0), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(13.8f, -0.9f, 0), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(13.8f, -0.9f, -100), orangeColor));
    verts.push_back(Vertex::PC(glm::vec3(14, -0.9f, -100), orangeColor));

    // Linker zwarte rand
    verts.push_back(Vertex::PC(glm::vec3(4, -1, 0), glm::vec4(0)));
    verts.push_back(Vertex::PC(glm::vec3(3.8f, -1, 0), glm::vec4(0)));
    verts.push_back(Vertex::PC(glm::vec3(3.8f, -1, -100), glm::vec4(0)));
    verts.push_back(Vertex::PC(glm::vec3(4, -1, -100), glm::vec4(0)));

    // Rechter zwarte rand
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

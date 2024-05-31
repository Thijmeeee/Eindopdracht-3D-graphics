#pragma once

#include "DrawComponent.h"
#include <vector>
#include "../tigl.h"

using tigl::Vertex;


class GroundPlaneComponent : public DrawComponent
{
public:
	GroundPlaneComponent();
	~GroundPlaneComponent();

	virtual void draw() override;



private:
	std::vector<Vertex> verts;
};

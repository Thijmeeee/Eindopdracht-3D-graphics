#pragma once

#include <gl/glew.h>
#include <string>
#include <iostream>

#include "lib/tigl.h"


class Texture
{
	GLuint id;
public:
	Texture(const std::string& fileName);
	Texture();
	void bind();
	void unbind();
};
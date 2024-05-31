#pragma once

#include <gl/glew.h>
#include <string>

#include <opencv2/opencv.hpp>

#include "tigl.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h" 

class Texture
{
	GLuint id;
public:
	Texture(const std::string& fileName);
	Texture();
	void bind();
	void updateTexture(cv::Mat& cvImage);
	void unbind();
};
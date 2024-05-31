#pragma once

#include <gl/glew.h>
#include <string>

#include <opencv2/opencv.hpp>



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
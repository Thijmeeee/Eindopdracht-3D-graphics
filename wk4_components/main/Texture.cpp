#include "Texture.h"



Texture::Texture(const std::string& fileName)
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &id);

	int bpp, width, height;
	unsigned char* imgData = stbi_load(
		fileName.c_str(), &width,
		&height, &bpp, 4);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D,
		0, //level
		GL_RGBA, //internal format
		width, //width
		height, //height
		0, //border
		GL_RGBA, //data format
		GL_UNSIGNED_BYTE, //data type
		imgData); //data

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(imgData);
}


Texture::Texture() {
	glGenTextures(1, &id);
}

void Texture::bind()
{
	tigl::shader->enableAlphaTest(true);
	glBindTexture(GL_TEXTURE_2D, id);
	tigl::shader->enableTexture(true);
}

//Sets new image as current one, so it doesnt make a new Texture 
void Texture::updateTexture(cv::Mat& cvImage) {
	glBindTexture(GL_TEXTURE_2D, id);
	const unsigned char* data = cvImage.ptr();
	if (!data)
	{
		std::cout << "[FirewallError] Could not complete Texture class constructor: data was invalid.\n";
		exit(0);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cvImage.cols, cvImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	tigl::shader->enableTexture(false);
	tigl::shader->enableAlphaTest(false);
}

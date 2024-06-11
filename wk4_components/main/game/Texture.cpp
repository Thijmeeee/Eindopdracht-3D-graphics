#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "lib/stb_image.h" 


Texture::Texture(const std::string& fileName)
{
	std::cout << "loading texture " << fileName << std::endl;
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &id);

	int bpp, width, height;
	unsigned char* imgData = stbi_load(
		fileName.c_str(), &width,
		&height, &bpp, 4);
	if(!imgData)
		std::cout << "error loading texture " << fileName << std::endl;

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
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

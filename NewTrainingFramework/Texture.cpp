#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::Load()
{
	pixelArray = LoadTGA(tr->path.c_str(), &width, &height, &bpp);

	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)pixelArray);
	glBindTexture(GL_TEXTURE_2D, 0);
}
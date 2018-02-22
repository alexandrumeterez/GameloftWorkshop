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

	if(tr->min_filter == "LINEAR")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(tr->mag_filter == "LINEAR")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(tr->wrap_s == "REPEAT")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else if(tr->wrap_s == "CLAMP_TO_EDGE")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	if (tr->wrap_t == "REPEAT")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	else if (tr->wrap_t == "CLAMP_TO_EDGE")
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)pixelArray);
	glBindTexture(GL_TEXTURE_2D, 0);
}
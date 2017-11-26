#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"
class Texture
{


public:
	TextureResource *tr; //structura pe baza careia e incarcata textura
	GLuint textureId; //generat prin glGenTextures()
	char *pixelArray;
	int width, height, bpp;
	GLuint format;
	void Load(); //incarca textura
	Texture();
	~Texture();
};


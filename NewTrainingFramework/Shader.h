#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"
class Shader
{


public:
	GLint positionAttribute;
	GLint matrixUniform;
	GLint textureUniform;
	GLint uvAttribute;
	GLuint vertexShader, fragmentShader;
	ShaderResource *sr; //structura pe baza careia e incarcat shader-ul
	GLuint programId; //obtinut prin linkarea vs-ului si a fs-ului
	void Load();
	Shader();
	~Shader();
};


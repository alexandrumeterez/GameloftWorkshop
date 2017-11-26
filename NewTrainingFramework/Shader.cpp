#include "stdafx.h"
#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::Load()
{

	char *fileVertexShader, *fileFragmentShader;
	fileVertexShader = (char*)malloc(512);

	fileFragmentShader = (char*)malloc(512);
	std::strcpy(fileVertexShader, sr->vs.c_str());
	std::strcpy(fileFragmentShader, sr->fs.c_str());
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader); //primeste calea catre fisierul shader si face compilarea
																	 //erorile de sintaxa sunt in output

	if (vertexShader == 0) //daca a esuat
	{
		throw;
	}

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader); //compileaza fragment shader

	if (fragmentShader == 0) //daca a esuat
	{
		glDeleteShader(vertexShader);
		throw;
	}

	programId = esLoadProgram(vertexShader, fragmentShader); //creeaza programul(face linkare la vs si fs)
	positionAttribute = glGetAttribLocation(programId, "a_posL"); //ia locatia var a_posL din shader ca sa pot sa transmit date in ea
	matrixUniform = glGetUniformLocation(programId, "u_matrix");
	textureUniform = glGetUniformLocation(programId, "u_texture");
	uvAttribute = glGetAttribLocation(programId, "a_uv");

}
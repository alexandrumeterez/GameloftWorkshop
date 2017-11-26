// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include <iostream>
#include "ResourceManager.h"
#include "SceneManager.h"

GLuint textureUniform;
//Shaders myShaders;
GLfloat alpha = 0.0f;
bool wired = false;
int width, height, bpp;
GLuint format;
Camera cam(Vector4(0.0f, 0.0f, -1.0f, 1.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f), 1.0f, 0.5f, 0.2f, 5000.0f, 45.0f);
float timeLimit = 0.05f;
float cumulativeDeltaTime = 0.0f;

Model *model;
Shader *shader;
Texture *texture;
int Init(ESContext *esContext)
{
	ResourceManager::getInstance()->Init();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //set background color
	glEnable(GL_DEPTH_TEST);

	std::cout << ResourceManager::getInstance()->modelResourcesMap.at(1) << std::endl;
	model = ResourceManager::getInstance()->loadModel(ResourceManager::getInstance()->modelResourcesMap.at(1));
	shader = ResourceManager::getInstance()->loadShader(ResourceManager::getInstance()->shaderResourcesMap.at(10));
	texture = ResourceManager::getInstance()->loadTexture(ResourceManager::getInstance()->textureResourcesMap.at(4));

	return 0;
}

void Draw(ESContext *esContext)
{
	Matrix P;
	P.SetPerspective(cam.getFov(), (GLfloat)Globals::screenWidth / Globals::screenHeight, cam.getNearBase(), cam.getFarBase());
	Matrix mvp = cam.getViewMatrix() * P;
	Matrix m;
	m.SetScale(0.01f, 0.01f, 0.01f);
	mvp = m * mvp;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //curatam bufferul

	glUseProgram(shader->programId); //spunem ce shader folosim

	if (wired == false)
	{
		glBindBuffer(GL_ARRAY_BUFFER, model->vboId); //deschide bufferul
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, model->vboId); //deschide bufferul
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->wiredIboId);
	}

	glBindTexture(GL_TEXTURE_2D, texture->textureId);

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3)));
	}

	if (shader->matrixUniform != -1)
	{
		glUniformMatrix4fv(shader->matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}

	if (shader->textureUniform != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(textureUniform, 0);
	}
	if (wired == false)
		glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void *)0);
	else
		glDrawElements(GL_LINES, model->wiredIndices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface); //desenez pe un buffer, il afisez, fac swap frameul urmator

}

void Update(ESContext *esContext, float deltaTime)
{
	//Limitare de framerate
	//Adun la cumulativ pana cand sare de limita; cand sare de limita, il dau inapoi cu limita
	cumulativeDeltaTime += deltaTime;
	if (cumulativeDeltaTime >= timeLimit)
	{
		cam.setDeltaTime(cumulativeDeltaTime);
		std::cout << cumulativeDeltaTime << std::endl;

		cumulativeDeltaTime -= timeLimit;
	}
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//switch de key
	//case w
	//cam.moveOZ(1) break
	switch (key)
	{
	case 'W':
		cam.moveOz(1);
		break;
	case 'S':
		cam.moveOz(-1);
		break;
	case 'A':
		cam.moveOx(1);
		break;
	case 'D':
		cam.moveOx(-1);
		break;
	case VK_UP:
		cam.rotateOz(1);
		break;
	case VK_DOWN:
		cam.rotateOz(-1);
		break;
	case VK_RIGHT:
		cam.rotateOy(1);
		break;
	case VK_LEFT:
		cam.rotateOy(-1);
		break;
	case 'Z':
		cam.rotateOx(-1);
		break;
	case 'X':
		cam.rotateOx(1);
		break;
	case 'T':
		wired = true;
		break;
	case 'Y':
		wired = false;
		break;
	default:;
	}


}

void CleanUp()
{
	glDeleteBuffers(1, &model->vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	SceneManager sc;
	sc.Init();
	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	model;
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Gameloft", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw); //desenarea
	esRegisterUpdateFunc(&esContext, Update); //calculele
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();


	return 0;
}


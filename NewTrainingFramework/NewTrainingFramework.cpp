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


GLfloat alpha = 0.0f;
int width, height, bpp;
float timeLimit = 0.05f;
float cumulativeDeltaTime = 0.0f;

int Init(ESContext *esContext)
{
	ResourceManager::getInstance()->Init();
	SceneManager::getInstance()->Init();
	
	return 0;
}

void Draw(ESContext *esContext)
{
	/*
	Matrix P;
	P.SetPerspective(cam.getFOV(), (GLfloat)Globals::screenWidth / Globals::screenHeight, cam.getNearCam(), cam.getFarCam());
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
	*/
	SceneManager::getInstance()->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface); //desenez pe un buffer, il afisez, fac swap frameul urmator
}

void Update(ESContext *esContext, float deltaTime)
{
	
	
	//Limitare de framerate
	//Adun la cumulativ pana cand sare de limita; cand sare de limita, il dau inapoi cu limita
	cumulativeDeltaTime += deltaTime;
	if (cumulativeDeltaTime >= timeLimit)
	{
		SceneManager::getInstance()->Update(cumulativeDeltaTime);

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
		SceneManager::getInstance()->cam->moveOz(1);
		break;
	case 'S':
		SceneManager::getInstance()->cam->moveOz(-1);
		std::cout << "Z: " << SceneManager::getInstance()->cam->getPosition().z << std::endl;
		break;
	case 'D':
		SceneManager::getInstance()->cam->moveOx(1);
		break;
	case 'A':
		SceneManager::getInstance()->cam->moveOx(-1);
		break;
	case 'Q':
		SceneManager::getInstance()->cam->moveOy(1);
		break;
	case 'E':
		SceneManager::getInstance()->cam->moveOy(-1);
		break;
	case VK_UP:
		SceneManager::getInstance()->cam->rotateOz(1);
		break;
	case VK_DOWN:
		SceneManager::getInstance()->cam->rotateOz(-1);
		break;
	case VK_RIGHT:
		SceneManager::getInstance()->cam->rotateOy(1);
		break;
	case VK_LEFT:
		SceneManager::getInstance()->cam->rotateOy(-1);
		break;
	case 'Z':
		SceneManager::getInstance()->cam->rotateOx(-1);
		break;
	case 'X':
		SceneManager::getInstance()->cam->rotateOx(1);
		break;
	default:;
	}


}

void CleanUp()
{
	//glDeleteBuffers(1, &model->vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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


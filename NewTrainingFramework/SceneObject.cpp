#include "stdafx.h"
#include "SceneObject.h"
#include <vector>
#include "Globals.h"
#include <iostream>

SceneObject::SceneObject(std::string modelId_, std::string shaderId_, std::string type_, bool depthTest_, std::string name_, std::vector<unsigned int> textures_, Vector3 position_, Vector3 rotation_, Vector3 scale_, float selfRotateSpeed_, unsigned int followingCamera_, bool followOx_, bool followOy_, bool followOz_, std::vector<unsigned int> lights_)
{
	modelId = modelId_;
	shaderId = shaderId_;
	type = type_;
	depthTest = depthTest_;
	name = name_;
	textures = textures_;
	position = position_;
	rotation = rotation_;
	scale = scale_;
	selfRotateSpeed = selfRotateSpeed_;
	followingCamera = followingCamera_;
	followOx = followOx_;
	followOy = followOy_;
	followOz = followOz_;
	lights = lights_;
}

SceneObject::SceneObject()
{

}

SceneObject::SceneObject(Vector3 position, Vector3 scale, Vector3 rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

SceneObject::~SceneObject()
{

}

void SceneObject::doCommon()
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (loadedShader->textureUniform[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, loadedTextures.at(i)->textureId);
			glUniform1i(loadedShader->textureUniform[i], i);
		}
	}

	if (loadedShader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(loadedShader->positionAttribute);
		glVertexAttribPointer(loadedShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (loadedShader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(loadedShader->uvAttribute);
		glVertexAttribPointer(loadedShader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3)));
	}

	if (loadedShader->uvBlendAttribute != -1)
	{
		glEnableVertexAttribArray(loadedShader->uvBlendAttribute);
		glVertexAttribPointer(loadedShader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(4 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (loadedShader->matrixUniform != -1)
	{
		glUniformMatrix4fv(loadedShader->matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}

}

void SceneObject::Update()
{
	followingCam->updateWorldView();
	Matrix m, p;
	p = p.SetScale(Vector3(scale.x, scale.y, scale.z));
	p = p * m.SetRotationX(rotation.x);
	p = p * m.SetRotationY(rotation.y);
	p = p * m.SetRotationZ(rotation.z);
	p = p * m.SetTranslation(position);
	m = p;
	mvp = m * followingCam->getViewMatrix();
	Matrix P;
	P.SetPerspective(followingCam->getFOV(), (GLfloat)Globals::screenWidth / Globals::screenHeight, followingCam->getNearCam(), followingCam->getFarCam());
	mvp = mvp * P;

}

void SceneObject::Draw()
{
	
	glUseProgram(loadedShader->programId); //spunem ce shader folosim

	glBindBuffer(GL_ARRAY_BUFFER, loadedModel->vboId); //deschide bufferul
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedModel->iboId);

	doCommon();
	glDrawElements(GL_TRIANGLES, loadedModel->indices.size(), GL_UNSIGNED_INT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

#include "stdafx.h"
#include "TerrainObject.h"
#include <cmath>



TerrainObject::TerrainObject(int cellNumber, float cellSize, float offsetY, std::string modelType) : cellNumber(cellNumber), cellSize(cellSize), offsetY(offsetY), modelType(modelType)
{
	center = followingCam->getPosition();
	loadedModel = new Model();

	if (modelType == "generated")
	{
		for (int i = cellNumber / 2, uv_i = 0; i >= -cellNumber / 2; i--, uv_i++)
		{
			for (int j = -cellNumber / 2, uv_j = 0; j <= cellNumber / 2; j++, uv_j++)
			{
				Vertex *coord = new Vertex();
				coord->pos = Vector3(center.x + j * cellSize, offsetY, center.z + i * cellSize);
				coord->norm = Vector3(0.0f, 1.0f, 0.0f);
				coord->binorm = Vector3(0.0f, 1.0f, 0.0f);
				coord->tgt = Vector3(0.0f, 1.0f, 0.0f);
				coord->uv = Vector2(uv_i, uv_j);
				coord->uv_blend = Vector2((float)uv_i / cellNumber, (float)uv_j / cellNumber);
				loadedModel->points.push_back(*coord);
				delete coord;
			}
		}

		for (unsigned int i = 0; i < cellNumber; i++)
		{
			for (unsigned int j = 0; j < cellNumber; j++)
			{
				loadedModel->indices.push_back((i + 1) * (cellNumber + 1) + j);
				loadedModel->indices.push_back(i * (cellNumber + 1) + j + 1);
				loadedModel->indices.push_back(i * (cellNumber + 1) + j + 1);
				loadedModel->indices.push_back((i + 1) * (cellNumber + 1) + j);
				loadedModel->indices.push_back((i + 1) * (cellNumber + 1) + j + 1);
			}
		}

		glGenBuffers(1, &loadedModel->iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedModel->iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, loadedModel->indices.size() * sizeof(unsigned int), loadedModel->indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glGenBuffers(1, &loadedModel->vboId);
		glBindBuffer(GL_ARRAY_BUFFER, loadedModel->vboId);
		glBufferData(GL_ARRAY_BUFFER, loadedModel->points.size() * sizeof(Vertex), loadedModel->points.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void TerrainObject::Update()
{
	if (abs(followingCam->getPosition().z - center.z) > cellSize && followingCam->getPosition().z > center.z)
	{
		for (int i = 0; i < loadedModel->points.size(); i++)
		{
			loadedModel->points[i].pos.z += cellSize;
			loadedModel->points[i].uv_blend.x -= 1.0 / cellNumber;
		}
		center.z += cellSize;
	}
	else if (abs(followingCam->getPosition().z - center.z) > cellSize && followingCam->getPosition().z < center.z)
	{
		for (int i = 0; i < loadedModel->points.size(); i++)
		{
			loadedModel->points[i].pos.z -= cellSize;
			loadedModel->points[i].uv_blend.x += 1.0 / cellNumber;
		}
		center.z -= cellSize;
	}

	if (abs(followingCam->getPosition().x - center.x) > cellSize && followingCam->getPosition().x < center.x)
	{
		for (int i = 0; i < loadedModel->points.size(); i++)
		{
			loadedModel->points[i].pos.x += cellSize;
			loadedModel->points[i].uv_blend.y += 1.0 / cellNumber;
		}
		center.x -= cellSize;
	}
	else if (abs(followingCam->getPosition().x - center.x) > cellSize && followingCam->getPosition().x < center.x)
	{
		for (int i = 0; i < loadedModel->points.size(); i++)
		{
			loadedModel->points[i].pos.x -= cellSize;
			loadedModel->points[i].uv_blend.y -= 1.0 / cellNumber;
		}
		center.x -= cellSize;
	}
	glGenBuffers(1, &loadedModel->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, loadedModel->vboId);
	glBufferData(GL_ARRAY_BUFFER, loadedModel->points.size() * sizeof(Vertex), loadedModel->points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TerrainObject::Draw()
{
	glUseProgram(loadedShader->sr->id);
	glBindBuffer(GL_ARRAY_BUFFER, loadedModel->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, loadedModel->iboId);
	if (loadedShader->heightUniform != -1)
	{
		glUniform3f(loadedShader->heightUniform, height.x, height.y, height.z);
	}
	doCommon();

	glDrawElements(GL_TRIANGLES, loadedModel->indices.size(), GL_UNSIGNED_INT, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TerrainObject::setHeight(Vector3 height)
{
	this->height = height;
}

TerrainObject::~TerrainObject()
{
}

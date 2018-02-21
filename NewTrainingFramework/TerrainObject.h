#pragma once
#include "SceneObject.h"
class TerrainObject : SceneObject
{
	int cellNumber;
	float cellSize;
	float offsetY;
	std::string modelType;
	Vector3 center;
	Vector3 height;

public:
	TerrainObject();
	~TerrainObject();

	TerrainObject(int, float, float, std::string, Camera*);
	void setHeight(Vector3);
	void Draw();
	void Update();
};


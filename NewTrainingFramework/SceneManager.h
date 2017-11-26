#pragma once
#include <vector>
#include "SceneObject.h"
#include "Camera.h"
#include <map>

class SceneManager
{
public:
	std::map<unsigned int, SceneObject*> sceneObjectVector;
	std::map<unsigned int, Camera*> cameraMap;

	float r, g, b;
	int activeCamera;

	void Init();
	void Draw();
	void Update();
	SceneManager();
	~SceneManager();
};


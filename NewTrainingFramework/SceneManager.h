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
	static SceneManager* spInstance;
	static SceneManager* getInstance();
	float r, g, b;
	int activeCamera;
	Camera* cam;
	void Init();
	void Draw();
	void Update(float cumulativeDeltaTime);

	void parseBackgroundColors();
	void parseCamerasAndActiveCamera();
	SceneManager();
	~SceneManager();
};


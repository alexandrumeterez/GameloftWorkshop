#pragma once
#include "SceneObject.h"
class SkyboxObject :
	public SceneObject
{
public:
	SkyboxObject();
	~SkyboxObject();
	void Draw();
	void Update();
};


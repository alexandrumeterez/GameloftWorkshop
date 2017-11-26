#pragma once
#include "../Utilities/Math.h"
#include <string>
#include <vector>

class SceneObject
{
public:
	std::string modelId;
		std::string shaderId;
		std::string type;
		bool depthTest;
		std::string name;
		std::vector<unsigned int> textures;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		float selfRotateSpeed;
		unsigned int followingCamera;
		bool followOx; 
		bool followOy;

		bool followOz; 
		std::vector<unsigned int> lights;
	SceneObject(std::string modelId_, std::string shaderId_, std::string type_, bool depthTest_, std::string name_, std::vector<unsigned int> textures_, Vector3 position_, Vector3 rotation_, Vector3 scale_, float selfRotateSpeed_, unsigned int followingCamera_, bool followOx_, bool followOy_, bool followOz_, std::vector<unsigned int> lights_);
	~SceneObject();
};


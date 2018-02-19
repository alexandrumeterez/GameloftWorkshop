#pragma once
#include "../Utilities/Math.h"
#include <string>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
class SceneObject
{
public:
		std::string modelId;
		std::string shaderId;
		std::string type;
		bool depthTest;
		bool wired;
		std::string name;
		std::vector<GLuint> textures;
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		float selfRotateSpeed;
		unsigned int followingCamera;
		Camera *followingCam;
		bool followOx; 
		bool followOy;
		bool followOz;
		Model* loadedModel;
		Shader* loadedShader;
		std::vector<Texture*> loadedTextures;
		void Draw();
		void Update();
		void doCommon();
		Matrix mvp;
		std::vector<unsigned int> lights;
	SceneObject(std::string modelId_, std::string shaderId_, std::string type_, bool depthTest_, std::string name_, std::vector<unsigned int> textures_, Vector3 position_, Vector3 rotation_, Vector3 scale_, float selfRotateSpeed_, unsigned int followingCamera_, bool followOx_, bool followOy_, bool followOz_, std::vector<unsigned int> lights_);
	SceneObject();
	SceneObject(Vector3 position, Vector3 scale, Vector3 rotation);
	~SceneObject();
};


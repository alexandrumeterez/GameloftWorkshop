#include "stdafx.h"
#include "SceneObject.h"
#include <vector>


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


SceneObject::~SceneObject()
{
}

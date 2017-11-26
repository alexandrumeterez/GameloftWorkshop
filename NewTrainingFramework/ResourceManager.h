#pragma once
#include <map>
#include "TextureResource.h"
#include "ModelResource.h"
#include "ShaderResource.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include <map>

class ResourceManager
{
private:
	static ResourceManager* spInstance;
	ResourceManager();


public:
	std::map<unsigned int, ModelResource*> modelResourcesMap;
	std::map<unsigned int, TextureResource*> textureResourcesMap;
	std::map<unsigned int, ShaderResource*> shaderResourcesMap;
	std::vector<Model*> loadedModels;
	std::vector<Texture*> loadedTextures;
	std::vector<Shader*> loadedShaders;
	~ResourceManager();
	void Init();
	static ResourceManager* getInstance();
	void freeResources();
	Model* loadModel(ModelResource *mr);
	Texture* loadTexture(TextureResource *tr);
	Shader *loadShader(ShaderResource *sr);

};


#include "stdafx.h"
#include "../Resources/RapidXML/rapidxml.hpp"
#include "resourceManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../Utilities/utilities.h"

using namespace rapidxml;
using namespace std;

ResourceManager* ResourceManager::spInstance = NULL;

ResourceManager::ResourceManager()
{

}

void ResourceManager::Init()
{
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream file("../Resources/XMLFiles/resourceManager.xml");

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	root_node = doc.first_node();
	for (xml_node<> * pNode = root_node->first_node("models"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("model"); pTest; pTest = pTest->next_sibling())
		{
			ModelResource* temp = new ModelResource{ atoi(pTest->first_attribute("id")->value()), 
												     pTest->first_node("path")->value() };
			modelResourcesMap.insert(pair <unsigned int, ModelResource*>(temp->id, temp));
		}
	}
	for (xml_node<> * pNode = root_node->first_node("shaders"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("shader"); pTest; pTest = pTest->next_sibling())
		{
			ShaderResource* temp = new ShaderResource{ atoi(pTest->first_attribute("id")->value()), 
													   pTest->first_node("vs")->value(), 
													   pTest->first_node("fs")->value() };
			shaderResourcesMap.insert(pair <unsigned int, ShaderResource*>(temp->id, temp));
		}
	}

	for (xml_node<> * pNode = root_node->first_node("textures"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("texture"); pTest; pTest = pTest->next_sibling())
		{

			TextureResource* temp = new TextureResource{ atoi(pTest->first_attribute("id")->value()),
														 pTest->first_attribute("type")->value(), 
														 pTest->first_node("path")->value(), 
														 pTest->first_node("min_filter")->value(),
													     pTest->first_node("mag_filter")->value(), 
														 pTest->first_node("wrap_s")->value(), 
														 pTest->first_node("wrap_t")->value() };
			textureResourcesMap.insert(pair <unsigned int, TextureResource*>(temp->id, temp));
		}
	}
}

ResourceManager* ResourceManager::getInstance() {

	if (!spInstance) {
		spInstance = new ResourceManager();
	}

	return spInstance;
}

Model* ResourceManager::loadModel(ModelResource *mr)
{
	if (loadedModels.count(mr->id) > 0 && loadedModels.at(mr->id)->mr == mr)
	{
		return loadedModels.at(mr->id);
	}
	Model* m = new Model();
	m->mr = mr;
	m->Load();
	loadedModels.insert(pair<unsigned int, Model*>(mr->id, m));
	return m;
}

Texture* ResourceManager::loadTexture(TextureResource *tr)
{
	if (loadedTextures.count(tr->id) > 0 && loadedTextures.at(tr->id)->tr == tr)
	{
		return loadedTextures.at(tr->id);
	}
	Texture* t = new Texture();
	t->tr = tr;
	t->Load();
	loadedTextures.insert(pair<unsigned int, Texture*>(tr->id, t));
	return t;
}

Shader* ResourceManager::loadShader(ShaderResource *sr)
{
	if (loadedShaders.count(sr->id) > 0 && loadedShaders.at(sr->id)->sr == sr)
	{
		return loadedShaders.at(sr->id);
	}
	Shader* s = new Shader();
	s->sr = sr;
	s->Load();
	loadedShaders.insert(pair<unsigned int, Shader*>(sr->id, s));
	return s;
}

ResourceManager::~ResourceManager()
{
	delete spInstance;
}

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
	ifstream theFile("../Resources/resourceManager/resourceManager.xml");

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("resourceManager");
	for (xml_node<> * pNode = root_node->first_node("models"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("model"); pTest; pTest = pTest->next_sibling())
		{
			ModelResource* temp = new ModelResource{ pTest->first_node("path")->value() };
			modelResourcesMap.insert(pair <unsigned int, ModelResource*>(atoi(pTest->first_attribute("id")->value()), temp));
		}
	}
	for (xml_node<> * pNode = root_node->first_node("shaders"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("shader"); pTest; pTest = pTest->next_sibling())
		{
			ShaderResource* temp = new ShaderResource{ pTest->first_node("vs")->value(), pTest->first_node("fs")->value() };
			shaderResourcesMap.insert(pair <unsigned int, ShaderResource*>(atoi(pTest->first_attribute("id")->value()), temp));
		}
	}

	for (xml_node<> * pNode = root_node->first_node("textures"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("texture"); pTest; pTest = pTest->next_sibling())
		{

			TextureResource* temp = new TextureResource{ pTest->first_attribute("type")->value(), pTest->first_node("path")->value(), pTest->first_node("min_filter")->value(),
				pTest->first_node("mag_filter")->value(), pTest->first_node("wrap_s")->value(), pTest->first_node("wrap_t")->value() };
			textureResourcesMap.insert(pair <unsigned int, TextureResource*>(atoi(pTest->first_attribute("id")->value()), temp));
		}
	}
	theFile.close();
}

ResourceManager* ResourceManager::getInstance() {

	if (!spInstance) {
		spInstance = new ResourceManager();
	}

	return spInstance;
}

ResourceManager::~ResourceManager()
{
	spInstance = NULL;
}

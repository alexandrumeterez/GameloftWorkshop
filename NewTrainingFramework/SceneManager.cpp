#include "stdafx.h"
#include "SceneManager.h"
#include "../Resources/RapidXML/rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include "ResourceManager.h"
#include "Globals.h"
#include "TerrainObject.h"

using namespace rapidxml;
xml_node<> *pRoot;
SceneManager* SceneManager::spInstance = NULL;

SceneManager* SceneManager::getInstance() {

	if (!spInstance) {
		spInstance = new SceneManager();
	}

	return spInstance;
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	delete spInstance;
}

void SceneManager::parseBackgroundColors()
{
	//Parse background color
	xml_node<> *pNode = pRoot->first_node("backgroundColor");
	xml_node<> *redNode = pNode->first_node("r");
	xml_node<> *greenNode = pNode->first_node("g");
	xml_node<> *blueNode = pNode->first_node("b");

	std::string red = redNode->value();
	std::string green = greenNode->value();
	std::string blue = blueNode->value();

	r = std::atoi(red.c_str());
	g = std::atoi(green.c_str());
	b = std::atoi(blue.c_str());
}

void SceneManager::parseCamerasAndActiveCamera()
{
	//Parse cameras
	for (xml_node<> *pNode = pRoot->first_node("cameras"); pNode; pNode = pNode->next_sibling())
	{
		int posX, posY, posZ;
		int targetX, targetY, targetZ;
		int upX, upY, upZ;
		float translationSpeed;
		float rotationSpeed;
		float fov;
		float nearBase;
		float farBase;
		int camId;

		for (xml_node<> *cameraNode = pNode->first_node("camera"); cameraNode; cameraNode = cameraNode->next_sibling())
		{
			std::string cameraId = cameraNode->first_attribute("id")->value();
			camId = std::atoi(cameraId.c_str());

			//Parse camera position
			std::string xPos = cameraNode->first_node("position")->first_node("x")->value();
			std::string yPos = cameraNode->first_node("position")->first_node("y")->value();
			std::string zPos = cameraNode->first_node("position")->first_node("z")->value();
			posX = std::atoi(xPos.c_str());
			posY = std::atoi(yPos.c_str());
			posZ = std::atoi(zPos.c_str());

			//Parse camera target
			std::string xTarget = cameraNode->first_node("target")->first_node("x")->value();
			std::string yTarget = cameraNode->first_node("target")->first_node("y")->value();
			std::string zTarget = cameraNode->first_node("target")->first_node("z")->value();
			targetX = std::atoi(xTarget.c_str());
			targetY = std::atoi(yTarget.c_str());
			targetZ = std::atoi(zTarget.c_str());

			//Parse camera up
			std::string xUp = cameraNode->first_node("up")->first_node("x")->value();
			std::string yUp = cameraNode->first_node("up")->first_node("y")->value();
			std::string zUp = cameraNode->first_node("up")->first_node("z")->value();
			upX = std::atoi(xUp.c_str());
			upY = std::atoi(yUp.c_str());
			upZ = std::atoi(zUp.c_str());

			//Parse camera translationSpeed
			std::string camTranslationSpeed = cameraNode->first_node("translationSpeed")->value();
			translationSpeed = std::atof(camTranslationSpeed.c_str());

			//Parse camera rotationSpeed
			std::string camRotationSpeed = cameraNode->first_node("rotationSpeed")->value();
			rotationSpeed = std::atof(camRotationSpeed.c_str());

			//Parse camera fov
			std::string camFov = cameraNode->first_node("fov")->value();
			fov = std::atof(camFov.c_str());

			//Parse camera near
			std::string camNear = cameraNode->first_node("near")->value();
			nearBase = std::atof(camNear.c_str());

			std::cout << camNear << std::endl;
			//Parse camera far
			std::string camFar = cameraNode->first_node("far")->value();
			farBase = std::atof(camFar.c_str());

			Vector3 camPos(posX, posY, posZ);
			Vector3 camTarget(targetX, targetY, targetZ);
			Vector3 camUp(upX, upY, upZ);

			Camera *c = new Camera(camPos, camTarget, camUp, translationSpeed, rotationSpeed, nearBase, farBase, fov);

			cameraMap.insert(std::make_pair(camId, c));
		}
	}

	//Parse activeCamera
	xml_node<> *activeCameraNode = pRoot->first_node("activeCamera");
	std::string activeCamString = activeCameraNode->value();
	activeCamera = std::atoi(activeCamString.c_str());
}

void SceneManager::Init()
{
	//Open file
	xml_document<> doc;
	std::ifstream file;
	try
	{
		file.open("../Resources/XMLFiles/sceneManager.xml");
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Failure to open file" << std::endl;
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	pRoot = doc.first_node();

	parseBackgroundColors();
	parseCamerasAndActiveCamera();

	//Parse objects
	for (xml_node<> *pNode = pRoot->first_node("objects"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> *objectNode = pNode->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
		{
			SceneObject *so;
			//Parse object id
			std::string objectIdString = objectNode->first_attribute("id")->value();
			int objectId = std::atoi(objectIdString.c_str());

			//Scot tipul obiectului
			std::string objectType = objectNode->first_node("type")->value();

			if (objectType == "terrain")
			{
				

				// Parse number of cells
				xml_node<> *cellNumber = objectNode->first_node("cells");
				std::string cellNumberString = cellNumber->value();
				int numberOfCells = std::atoi(cellNumberString.c_str());

				// Parse cell size
				xml_node<> *cellWidth = objectNode->first_node("size");
				std::string cellWString = cellWidth->value();
				float cellSize = std::atof(cellWString.c_str());

				//Parse offsetY
				xml_node<> *offsetYNode = objectNode->first_node("offsetY");
				std::string offsetYString = offsetYNode->value();
				float offsetY = std::atof(offsetYString.c_str());

				TerrainObject *t = new TerrainObject(numberOfCells, cellSize, offsetY, objectType);
				so = (SceneObject*)t;
			}
			else if (objectType == "normal")
			{
				so = new SceneObject();
			}

			//Scot id-ul obiectului
			std::string modelId = objectNode->first_node("model")->value();

			//Scot shader-ul obiectului
			std::string shaderId = objectNode->first_node("shader")->value();

			//Scot valoarea pentru depthTest
			std::string depthTestString = objectNode->first_node("depthTest")->value();
			bool depthTest = (depthTestString == "true") ? true : false;

			//Scot valoarea pentru blend
			if (objectNode->first_node("blend") != NULL)
			{
				std::string blendString = objectNode->first_node("blend")->value();
				bool blend = (blendString == "true") ? true : false;
			}
			//Scot name(dar vad intai daca exista)
			std::string name;
			if (objectNode->first_node("name"))
			{
				name = objectNode->first_node("name")->value();
			}

			//Scot textures(dar vad intai daca exista)
			std::vector<unsigned int> textures;
			if (objectNode->first_node("textures"))
			{
				for (xml_node<> *textureNode = objectNode->first_node("textures")->first_node("texture"); textureNode; textureNode = textureNode->next_sibling())
				{
					std::string tId = textureNode->first_attribute("id")->value();
					unsigned int texId = std::atoi(tId.c_str());
					textures.push_back(texId);
				}
			}

			//Parsez position
			float posX, posY, posZ;
			std::string xPos = objectNode->first_node("position")->first_node("x")->value();
			std::string yPos = objectNode->first_node("position")->first_node("y")->value();
			std::string zPos = objectNode->first_node("position")->first_node("z")->value();
			posX = std::atof(xPos.c_str());
			posY = std::atof(yPos.c_str());
			posZ = std::atof(zPos.c_str());
			Vector3 position(posX, posY, posZ);

			//Parsez rotation
			float rotX, rotY, rotZ;
			std::string xRot = objectNode->first_node("rotation")->first_node("x")->value();
			std::string yRot = objectNode->first_node("rotation")->first_node("y")->value();
			std::string zRot = objectNode->first_node("rotation")->first_node("z")->value();
			rotX = std::atof(xRot.c_str());
			rotY = std::atof(yRot.c_str());
			rotZ = std::atof(zRot.c_str());
			Vector3 rotation(rotX, rotY, rotZ);

			//Parsez scale
			float scaleX, scaleY, scaleZ;
			std::string xScale = objectNode->first_node("scale")->first_node("x")->value();
			std::string yScale = objectNode->first_node("scale")->first_node("y")->value();
			std::string zScale = objectNode->first_node("scale")->first_node("z")->value();
			scaleX = std::atof(xScale.c_str());
			scaleY = std::atof(yScale.c_str());
			scaleZ = std::atof(zScale.c_str());
			Vector3 scale(scaleX, scaleY, scaleZ);

			//Parsez selfRotateSpeed(daca exista)
			float selfRotateSpeed = 0.0f;
			if (objectNode->first_node("selfRotateSpeed"))
			{
				std::string selfRotateSpeedString = objectNode->first_node("selfRotateSpeed")->value();
				selfRotateSpeed = std::atof(selfRotateSpeedString.c_str());
			}

			bool wiredMode = false;
			if (objectNode->first_node("wired"))
			{
				wiredMode = true;
			}

			//Parsez in continuare in functie de tipul obiectului

			//adaug obiect nou de tip sceneobject
			so->depthTest = depthTest;
			so->modelId = modelId;
			so->name = name;
			so->position = position;
			so->rotation = rotation;
			so->scale = scale;
			so->selfRotateSpeed = selfRotateSpeed;
			so->shaderId = shaderId;
			so->textures = textures;
			so->type = objectType;
			so->wired = false;
			so->followingCamera = activeCamera;
			so->followingCam = cameraMap.at(activeCamera);
			sceneObjectVector.insert(std::pair<unsigned int, SceneObject*>(objectId, so));
		}
	}

	glClearColor(r, g, b, 0.0f);
	glEnable(GL_DEPTH_TEST);


	for (std::map<unsigned int, SceneObject*>::iterator it = sceneObjectVector.begin(); it != sceneObjectVector.end(); ++it)
	{
		if (it->second->type == "normal")
		{
			it->second->loadedModel = ResourceManager::getInstance()->loadModel(ResourceManager::getInstance()->modelResourcesMap.at(std::atoi(it->second->modelId.c_str())));
			it->second->loadedShader = ResourceManager::getInstance()->loadShader(ResourceManager::getInstance()->shaderResourcesMap.at(std::atoi(it->second->shaderId.c_str())));
			for (std::vector<unsigned int>::iterator textureIdIterator = it->second->textures.begin(); textureIdIterator != it->second->textures.end(); ++textureIdIterator)
			{
				Texture* temp = ResourceManager::getInstance()->loadTexture(ResourceManager::getInstance()->textureResourcesMap.at(*textureIdIterator));
				it->second->loadedTextures.push_back(temp);
			}
		}
	}

	cam = cameraMap.at(activeCamera);
	//cam = new Camera(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 50.0f, 0.5f, 0.2f, 5000.0f, 45.0f);
}

void SceneManager::Draw()
{
	
	for (std::map<unsigned int, SceneObject*>::iterator it = sceneObjectVector.begin(); it != sceneObjectVector.end(); ++it)
	{
		//it->second->followingCam = cam;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //curatam bufferul
		it->second->Draw();
	}
}

void SceneManager::Update(float cumulativeDeltaTime)
{
	cam->setDeltaTime(cumulativeDeltaTime);
	for (std::map<unsigned int, SceneObject*>::iterator it = sceneObjectVector.begin(); it != sceneObjectVector.end(); ++it)
	{
		//it->second->followingCam = cam;
		it->second->Update();
	}
}

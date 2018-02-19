#include "stdafx.h"
#include "Model.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
Model::Model()
{
}


Model::~Model()
{
}

std::vector<std::string> splitString(std::string str, char delimiter) {
	std::vector<std::string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	std::string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

void Model::setNumberOfIndices(int nr)
{
	numberOfIndices = nr;
}

void Model::setNumberOfVertices(int nr)
{
	numberOfVertices = nr;
}

void Model::Load()
{
	std::string line;
	unsigned int numberOfVertices;
	std::ifstream input(mr->path);
	getline(input, line); //Citesc nrVertices
	numberOfVertices = std::stoi(line.substr(12, line.length() - 11));
	setNumberOfVertices(numberOfVertices);
	for (int i = 0; i < numberOfVertices; ++i)
	{
		Vertex auxVertex;

		getline(input, line); //citesc fiecare linie
		std::vector<std::string> result;
		result = splitString(line, ';'); //sparg dupa norm, pos etc

										 //Scot paranteza dreapta din dreapta la toate
		for (int j = 0; j < 5; ++j)
			result.at(j).pop_back();

		//Parsez pos
		std::string pos = splitString(result.at(0), '[').at(1);
		std::vector<std::string> coords = splitString(pos, ',');
		coords.at(1).erase(0, 1);
		coords.at(2).erase(0, 1);
		auxVertex.pos = Vector3(std::stof(coords.at(0)), std::stof(coords.at(1)), std::stof(coords.at(2)));

		//Parsez norm
		std::vector<std::string> norm = splitString(result.at(1).substr(7), ',');
		norm.at(1).erase(0, 1);
		norm.at(2).erase(0, 1);
		auxVertex.norm = Vector3(std::stof(norm.at(0)), std::stof(norm.at(1)), std::stof(norm.at(2)));

		//Parsez binorm
		std::vector<std::string> binorm = splitString(result.at(2).substr(9), ',');
		binorm.at(1).erase(0, 1);
		binorm.at(2).erase(0, 1);
		auxVertex.binorm = Vector3(std::stof(binorm.at(0)), std::stof(binorm.at(1)), std::stof(binorm.at(2)));

		//Parsez tgt
		std::vector<std::string> tgt = splitString(result.at(3).substr(6), ',');
		tgt.at(1).erase(0, 1);
		tgt.at(2).erase(0, 1);
		auxVertex.tgt = Vector3(std::stof(tgt.at(0)), std::stof(tgt.at(1)), std::stof(tgt.at(2)));

		//Parsez uv
		std::vector<std::string> uv = splitString(result.at(4).substr(5), ',');
		uv.at(1).erase(0, 1);
		auxVertex.uv = Vector2(std::stof(uv.at(0)), std::stof(uv.at(1)));

		points.push_back(auxVertex);
	}

	//Extrag number of indices
	getline(input, line);
	numberOfIndices = std::stoi(line.substr(11));
	setNumberOfIndices(numberOfIndices);
	for (int i = 0; i < numberOfIndices / 3; ++i)
	{

		getline(input, line);
		std::string goodLine = splitString(line, '.').at(1);
		goodLine.erase(std::remove(goodLine.begin(), goodLine.end(), ' '), goodLine.end());

		std::vector<std::string> parts = splitString(goodLine, ',');
		indices.push_back(stoi(parts.at(0)));
		indices.push_back(stoi(parts.at(1)));
		indices.push_back(stoi(parts.at(2)));
	}

	//primul, al doilea de 2 ori, al 3 lea de 2 ori, primu

	glGenBuffers(1, &iboId);

	glGenBuffers(1, &vboId);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &(indices)[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Vertex), &(points)[0], GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

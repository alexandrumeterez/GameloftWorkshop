#pragma once
#include "ModelResource.h"
#include "Vertex.h"
#include <vector>
class Model
{

public:
	ModelResource* mr; //structura pe baza careia e incarcat modelul
	GLuint iboId; //id-ul bufferului care contine indicii
	GLuint wiredIboId; //id-ul bufferului care contine indicii pentru afisarea wired
	GLuint vboId; //id-ul bufferului care contine vertecsii
	std::vector<unsigned int> indices;
	std::vector<unsigned int> wiredIndices;
	std::vector<Vertex> points;
	unsigned int numberOfIndices;
	unsigned int numberOfWiredIndices;
	unsigned int numberOfVertices;
	Model();
	~Model();
	void Load(); //incarca modelul din nfg
	void setNumberOfVertices(int numberOfVertices);
	void setNumberOfIndices(int numberOfIndices);
};


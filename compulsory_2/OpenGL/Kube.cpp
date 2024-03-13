#include "Kube.h"

Kube::Kube(float storrelse):
a(storrelse)
{
	//a=storrelse;
	//har 8 vertexer, 6 flater, må lage to trekanter for hver flate.
	//rød front
	//mVertices.push_back(?tok den bort? v0,v1,v2,v3(kantene til firkant fronten)
	vertex v0{ -a,-a, a,1.0f,0.0f,0.0f };
	vertex v1{ a,-a,-a,1.0f,0.0f,0.0f };
	vertex v2{ a, a, a,1.0f,0.0f,0.0f };
	vertex v3{ -a, a, a,1.0f,0.0f,0.0f };
	//lagre rød front
	mVertices.push_back(v0);
	mVertices.push_back(v1);
	mVertices.push_back(v3);
	mVertices.push_back(v3);
	mVertices.push_back(v1);
	mVertices.push_back(v2);

	//baksiden blir som front, men med -1 som 3 parameter. punktene v4,v5,v6,v7.
	}
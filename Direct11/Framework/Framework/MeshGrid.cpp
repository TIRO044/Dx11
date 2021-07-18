#include "Framework.h"
#include "MeshGrid.h"

MeshGrid::MeshGrid(Shader* shader, float offsetU, float offsetV)
: Mesh(shader), offsetU(offsetU), offsetV(offsetV)
{
}

MeshGrid::~MeshGrid()
{
}

void MeshGrid::Create()
{
	UINT countX = 10;
	UINT countY = 10;

	float w = (static_cast<float>(countX)) * 0.5f;
	float h = (static_cast<float>(countY)) * 0.5f;

	vector<MeshVertex> v;
	for (UINT z = 0; z <= countX; z++) {
		for (UINT x = 0; x <= countY; x++) {
			MeshVertex vertex;
			vertex.Position = Vector3(static_cast<float>(x) - w, 0, static_cast<float>(z) - h);
			vertex.Normal = Vector3(0, 1, 0);
			vertex.Uv = Vector2(static_cast<float>(x) / (float)countX, static_cast<float>(z) / (float)countY);

			v.push_back(vertex);
		}
	}
	
	vertexCount = v.size();
	vertices = new MeshVertex[vertexCount];
	
	copy(v.begin(), v.end(), stdext::checked_array_iterator<MeshVertex*>(vertices, vertexCount));

	int wid = countX + 1;
	vector<UINT> i;
	for(UINT z = 0; z < countX; z++)
	{
		for(UINT x = 0; x < countY; x++)
		{
			i.push_back(wid * z + x);
			i.push_back(wid * (z + 1) + x);
			i.push_back(wid * z + x + 1);
			i.push_back(wid * z + x + 1);
			i.push_back(wid * (z + 1) + x);
			i.push_back(wid * (z + 1) + x + 1);
		}
	}
	
	indexCount = i.size();
	indices = new UINT[indexCount];

	copy(i.begin(), i.end(), stdext::checked_array_iterator<UINT*>(indices, indexCount));
}

#pragma once
#include "Mesh.h"

class MeshGrid : public Mesh
{
public :
	MeshGrid(Shader* shader, float offsetU, float offsetV);
	~MeshGrid();

protected:
	float offsetU, offsetV;

private:
	void Create() override;
};


#pragma once
#include "Mesh.h"

class MeshSphere : public Mesh
{
public:
	MeshSphere(Shader* shader, UINT stackCount, UINT sliceCount, float radian);
	virtual ~MeshSphere();

protected:
	void Create() override;
	UINT _stackCount;
	UINT _sliceCount;
	float _radian;
};

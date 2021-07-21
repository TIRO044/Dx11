#pragma once
#include "Systems/IExecute.h"
#include "MeshQuad.h"
#include "MeshCube.h"
#include "MeshGrid.h"
#include "MeshSphere.h"

class MeshDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private :
	Shader* meshShader;

	MeshQuad* meshQuad;
	MeshCube* meshCube;
	MeshGrid* meshGrid;
	MeshSphere* meshSphere;
	
	Vector3 direction = Vector3(-1, -1, -1);
	ID3DX11EffectVectorVariable* sDirection;
};

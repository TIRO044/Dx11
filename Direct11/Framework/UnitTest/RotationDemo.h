#pragma once
#include "Systems/IExecute.h"

class RotationDemo : public IExecute
{
public:
	void Initialize() override;
	void Ready() override;
	void Destroy() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ResizeScreen() override;

private :
	Shader* shader;
	Vertex vertices[6];

	ID3D11Buffer* vertexBuffer;
	UINT Index;
	Matrix world[3];
};

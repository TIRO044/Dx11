#pragma once
#include "Systems/IExecute.h"

class CubeDemo : public IExecute
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

	UINT width = 256;
	UINT height = 256;

	UINT vertexCount;
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;
	
	Matrix world;
};

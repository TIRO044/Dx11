#pragma once
#include "Systems/IExecute.h"

class TextureDemo : public IExecute
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

	void LoadTexture(wstring file);
private :
	Shader* shader;
	VertexTexture vertices[6];
	ID3D11Buffer* vertexBuffer;

	UINT Indices[6] = { 0, 1, 2, 2, 1, 3};
	ID3D11Buffer* IndexBuffer;
	
	Matrix world;
	//ID3D11ShaderResourceView* srv;

	Texture* texture = NULL;
};

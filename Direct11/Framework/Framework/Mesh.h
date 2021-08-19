#pragma once
#include "Renderer.h"

class Mesh : public Renderer
{
public:
	typedef VertexTextureNormal MeshVertex;
protected:
	Mesh(Shader* shader);
	~Mesh();
public:
	void SetDiffuseMap(wstring file);

	void Render();
	void Update();

	// World s, r, v ������� �Ѵ�.
	void UpdateWorld();

	virtual void Create() = 0;
protected:

	MeshVertex* vertices;
	UINT* indices;
	
	Texture* texture = nullptr;
	ID3DX11EffectShaderResourceVariable* _sDiffuseMap;
};

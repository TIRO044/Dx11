#pragma once
#include "PerFrame.h"
#include "Transform.h"

class Renderer
{
public :
	Renderer(Shader* shader);
	Renderer(wstring shaderFile);
	virtual ~Renderer();

	Shader* GetShader() { return _shader; }

	UINT& Pass() { return pass; }
	void Pass(UINT val) {pass = val;}

	virtual void Update();
	virtual void Render();

	Transform* GetTransform() { return _transform; }
private:
	void Initialize();
protected:
	void Topology(const D3D11_PRIMITIVE_TOPOLOGY val) { _topology = val; }
	
protected:
	Shader* _shader;
	Transform* _transform;
	VertexBuffer* _vertexBuffer;
	IndexBuffer* _indexBuffer;

	UINT _vertexCount = 0;
	UINT _indexCount = 0;
	
private:
	bool _createShader;
	
	D3D11_PRIMITIVE_TOPOLOGY _topology;
	UINT pass = 0;

	PerFrame* _perFrame;
};
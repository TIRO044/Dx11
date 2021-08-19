#pragma once
#include "MeshSphere.h"


class CubeSky
{
public:
	CubeSky(wstring file);
	~CubeSky();
public:
	void Render();
	void Update() const;

protected:
	Shader* _shader;
	MeshSphere* _sphere;

	ID3D11ShaderResourceView* _srv;
	ID3DX11EffectShaderResourceVariable* _sSrv;
};
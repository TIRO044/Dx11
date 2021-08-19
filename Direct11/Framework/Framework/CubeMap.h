#pragma once

#include "MeshCube.h"
class CubeMap
{
public:
	CubeMap(Shader* shader);
	~CubeMap();
public:
	void SetTextrue(wstring file);

	void Update();
	void Render();

	Transform* GetTransform() const { return _cube->GetTransform(); }
private:
	UINT _pass;
	MeshCube* _cube;

	Shader* _shader;
	ID3D11ShaderResourceView* _srv;
	ID3DX11EffectShaderResourceVariable* _sSrv;
};

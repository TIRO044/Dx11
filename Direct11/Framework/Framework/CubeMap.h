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

	void Position(Vector3* Vector3);
	void Position(Vector3& Vector3);

	void Scale(Vector3* Vector3);
	void Scale(Vector3& Vector3);
	
	void Rotation(Vector3* Vector3);
	void Rotation(Vector3& Vector3);

	void Pass(UINT pass) {_pass = pass;}

private:
	UINT _pass;
	MeshCube* _cube;

	Shader* _shader;
	ID3D11ShaderResourceView* _srv;
	ID3DX11EffectShaderResourceVariable* _sSrv;
};

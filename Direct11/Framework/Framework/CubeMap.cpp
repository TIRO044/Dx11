#include "Framework.h"
#include "CubeMap.h"

CubeMap::CubeMap(Shader* shader)
{
	_cube = new MeshCube(shader);

	_sSrv = shader->AsSRV("CubeMap");
}

CubeMap::~CubeMap()
{
	SafeDelete(_cube);
	SafeRelease(_srv);
	SafeRelease(_sSrv);
}

void CubeMap::SetTextrue(wstring file)
{
	SafeRelease(_srv);

	file = L"../../_Textures/" + file;
	Check(D3DX11CreateShaderResourceViewFromFile(
		D3D::GetDevice(), file.c_str(), NULL, NULL, &_srv, NULL
		)
	);
}

void CubeMap::Update()
{
	_sSrv->SetResource(_srv);
	_cube->Update();
}

void CubeMap::Render()
{
	_cube->Render();
}

void CubeMap::Position(Vector3* Vector3)
{
	_cube->Position(Vector3);
}

void CubeMap::Position(Vector3& Vector3)
{
	_cube->Position(Vector3);
}

void CubeMap::Scale(Vector3* Vector3)
{
	_cube->Scale(Vector3);
}

void CubeMap::Scale(Vector3& Vector3)
{
	_cube->Scale(Vector3);
}

void CubeMap::Rotation(Vector3* Vector3)
{
	_cube->Rotate(Vector3);
}

void CubeMap::Rotation(Vector3& Vector3)
{
	_cube->Rotate(Vector3);
}

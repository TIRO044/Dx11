#include "stdafx.h"
#include "CubeMapDemo.h"

void CubeMapDemo::Initialize()
{
	_shader = new Shader(L"MeshCubeShader.fx");
	_cubeMap = new CubeMap(_shader);
	_cubeMap->SetTextrue(L"Environment/Earth.dds");
	_cubeMap->Position(Vector3(0, 20, 0));
	_cubeMap->Scale(Vector3(0, 20, 0));
}

void CubeMapDemo::Destroy()
{
	SafeDelete(_shader);
}

void CubeMapDemo::Update()
{
	_cubeMap->Update();
}

void CubeMapDemo::Render()
{
	_cubeMap->Render();
}

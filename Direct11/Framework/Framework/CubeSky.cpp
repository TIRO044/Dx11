#include "Framework.h"
#include "CubeSky.h"

CubeSky::CubeSky(wstring file)
{
	_shader = new Shader(L"CubeSkyShader.fx");

	_sphere = new MeshSphere(_shader, 10, 10, 5);
	file = L"../../_Textures/" + file;

	Check
	(
		D3DX11CreateShaderResourceViewFromFile(
			D3D::GetDevice(), file.c_str(), NULL, NULL, &_srv, NULL
		)
	);
	
	_sSrv = _shader->AsSRV("SkyCubeMap");
}

CubeSky::~CubeSky()
{
	SafeDelete(_shader);
	SafeDelete(_sphere);

	SafeDelete(_sSrv);
}

void CubeSky::Update() const
{
	Vector3 position;
	Context::Get()->GetCamera()->Position(&position);

	_sphere->Update();
	_sphere->GetTransform()->Position(position);
}

void CubeSky::Render()
{
	_sSrv->SetResource(_srv);
	_sphere->Render();
}
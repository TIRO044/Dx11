#include "stdafx.h"
#include "TerrainDemo.h"

void TerrainDemo::Initialize()
{
	shader = new Shader(L"TerrainShader.fx");
	terrain = new Terrain();
}

void TerrainDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void TerrainDemo::SetTexture(wstring file)
{
	terrain->SetTexture(shader, file);
	terrain->Pass(0);
}

void TerrainDemo::Update()
{
	if (ImGui::Button("Open") == true)
	{
		const function<void(wstring)> f = bind(&TerrainDemo::SetTexture, this, placeholders::_1);
		const auto desc = D3D::GetDesc();
		Path::OpenFileDialog(L"", Path::ImageFilter, L"../../_Textures/", f, desc.Handle);
	}

	terrain->Update();
}

void TerrainDemo::Render()
{
	terrain->Render();
}
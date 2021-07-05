#include "stdafx.h"
#include "GetHeightDemo.h"

void GetHeightDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0, 0);
	Context::Get()->GetCamera()->Position(35, 10, -55);

	{ // vertex
		shader = new Shader(L"WorldShader.fx");

		vertex[0].Position = Vector3(0, 1, 0);
		vertex[1].Position = Vector3(-1, 0, 0);
		vertex[2].Position = Vector3(1, 0, 0);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof desc);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * 3;

		D3D11_SUBRESOURCE_DATA subResourceData = { 0 };
		subResourceData.pSysMem = vertex;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResourceData, &vertexBuffer));
	}
	
	{	// terrain
		terrainShader = new Shader(L"TerrainShader.fx");
		terrain = new Terrain();
	}
}

void GetHeightDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrainShader);
	SafeRelease(vertexBuffer);
	SafeDelete(terrain);
}

void GetHeightDemo::Update()
{
	if (ImGui::Button("Open") == true)
	{
		const function<void(wstring)> f = bind(&GetHeightDemo::SetTexture, this, placeholders::_1);
		const auto desc = D3D::GetDesc();
		Path::OpenFileDialog(L"", Path::ImageFilter, L"../../_Textures/", f, desc.Handle);
	}
	
	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= 20.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_UP))
		position.z += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		position.z -= 20.0f * Time::Delta();

	terrain->Update();
	//position.y = terrain->GetHeight(position) + 1.0f;
	position.y = terrain->GetVertexRayCast(position) + 1.0f;
	Matrix r, p;
	D3DXMatrixRotationX(&r, Math::ToRadian(180));
	D3DXMatrixTranslation(&p, position.x, position.y, position.z);

	Matrix world = r * p;
	
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void GetHeightDemo::SetTexture(wstring file)
{
	terrain->SetTexture(terrainShader, file);
	terrain->Pass(0);
}

void GetHeightDemo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	shader->Draw(0, 1, 3, 0);

	terrain->Render();
}
#include "stdafx.h"
#include "TextureDemo.h"

void TextureDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -0.5);

	//shader = new Shader(L"TextureShader.fx");
	shader = new Shader(L"TextureSampleShader.fx");
	
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	/*vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 0);*/


	vertices[0].Uv = Vector2(0, 2);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(2, 2);
	vertices[3].Uv = Vector2(2, 0);

	
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexTexture) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = Indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &IndexBuffer));
	}

	D3DXMatrixIdentity(&world);
}

void TextureDemo::Ready()
{
	
}
void TextureDemo::PreRender()
{

}
void TextureDemo::PostRender()
{

}
void TextureDemo::ResizeScreen()
{

}

void TextureDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(IndexBuffer);

	SafeDelete(texture);
}

void TextureDemo::Update()
{
	if (ImGui::Button("Open") == true)
	{
		const function<void(wstring)> f = bind(&TextureDemo::LoadTexture, this, placeholders::_1);
		const auto desc = D3D::GetDesc();
		Path::OpenFileDialog(L"", Path::ImageFilter, L"../../_Textures/", f, desc.Handle);
	}

	ImGui::InputInt("Filter", reinterpret_cast<int*>(&filter));
	filter %= 2;

	ImGui::InputInt("Address", reinterpret_cast<int*>(&address));
	address %= 4;
}

void TextureDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	if(texture != nullptr)
	{
		shader->AsSRV("Map")->SetResource(texture->SRV());
		shader->AsScalar("Filter")->SetInt(filter);
		shader->AsScalar("Address")->SetInt(address);
	}
	
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;
	// IA는 파이프 라인이라는 것을 말한다
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	shader->DrawIndexed(0, 2, 6);
}

void TextureDemo::LoadTexture(wstring file)
{
	//D3DDesc desc = D3D::GetDesc();
	//MessageBox(desc.Handle, file.c_str(), L"", MB_OK);
	SafeDelete(texture);

	texture = new Texture(file);
}

#include "stdafx.h"
#include "TextureDemo.h"

void TextureDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(-1, 0, -5);

	shader = new Shader(L"TextureShader.fx");
	
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 0);

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

	Check(D3DX11CreateShaderResourceViewFromFile(
		D3D::GetDevice(), L"../../_Texture/test.jpg", NULL, NULL, &srv, NULL
	));
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
}

void TextureDemo::Update()
{
	
}

void TextureDemo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsSRV("Map")->SetResource(srv);
	
	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;

	// IA는 파이프 라인이라는 것을 말한다
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	shader->DrawIndexed(0, 1, 6);
}

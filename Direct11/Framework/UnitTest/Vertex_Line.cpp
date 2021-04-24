#include "stdafx.h"
#include "Vertex_Line.h"

void Vertex_Line::Initialize()
{
	shader = new Shader(L"01_Vertex.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(1.0f, 0.0f, 0.0f);

	// DESC는 내림 차순이라는 의미
	// https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 2;
	//BindFlages는 파이프라인에 어떻게 바인딩할거냐, 라는 것인데 이게 뭔데
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

void Vertex_Line::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void Vertex_Line::Update()
{
	
}

void Vertex_Line::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// 어떤 모양으로 그릴 것이냐?
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 2);
}




#include "stdafx.h"
#include "WorldDemo.h"

void World_Demo::Initialize()
{
	shader = new Shader(L"WorldShader.fx");

	vertices[0].Position = Vector3(-0.5f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.0f, 0.0f);

	vertices[3].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[4].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[5].Position = Vector3(0.5f, 0.0f, 0.0f);

	// DESC는 내림 차순이라는 의미
	// https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	//BindFlages는 파이프라인에 어떻게 바인딩할거냐, 라는 것인데 이게 뭔데
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Ram에서 vRam으로 복사한다. 실제로 GPU로 복사해주는 부분
	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));

	D3DXMatrixIdentity(&world);
}

void World_Demo::Ready()
{
	
}
void World_Demo::PreRender()
{

}
void World_Demo::PostRender()
{

}
void World_Demo::ResizeScreen()
{

}


void World_Demo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}


void World_Demo::Update()
{
	// 이 행위만 했을 땐 RAM메모리에만 존재하기 떄문에 의미가 없는 행위
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		world._12 += 2.0f * Time::Delta();
	}
	else if (Keyboard::Get()->Press(VK_LEFT))
	{
		world._13 -= 2.0f * Time::Delta();
	}
}

void World_Demo::Render()
{
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// IA는 파이프 라인이라는 것을 말한다
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// 어떤 모양으로 그릴 것이냐?
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6, 0);
}

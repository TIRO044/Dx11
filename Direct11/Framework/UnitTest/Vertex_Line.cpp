#include "stdafx.h"
#include "Vertex_Line.h"

void Vertex_Line::Initialize()
{
	shader = new Shader(L"01_VertexShader.fx");

	vertices[0].Position = Vector3(-0.5f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = Vector3(0.5f, 0.0f, 0.0f);

	vertices[3].Position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[4].Position = Vector3(0.5f, 0.5f, 0.0f);
	vertices[5].Position = Vector3(0.5f, 0.0f, 0.0f);

	// DESC�� ���� �����̶�� �ǹ�
	// https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 6;
	//BindFlages�� ���������ο� ��� ���ε��Ұų�, ��� ���ε� �̰� ����
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Ram���� vRam���� �����Ѵ�. ������ GPU�� �������ִ� �κ�
	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

void Vertex_Line::Ready()
{
	
}
void Vertex_Line::PreRender()
{

}
void Vertex_Line::PostRender()
{

}
void Vertex_Line::ResizeScreen()
{

}

void Vertex_Line::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void Vertex_Line::Update()
{
	// �� ������ ���� �� RAM�޸𸮿��� �����ϱ� ������ �ǹ̰� ���� ����
	static bool bOpen = false;
	if (Keyboard::Get()->Press(VK_RIGHT))
	{
		vertices[0].Position.x += 3.0f * Time::Delta();
	}
	else if (Keyboard::Get()->Press(VK_LEFT))
	{
		vertices[0].Position.x -= 3.0f * Time::Delta();
	} else if (Keyboard::Get()->Press(VK_SPACE))
	{
		bOpen = !bOpen;
	}
	if (bOpen) ImGui::ShowDemoWindow(&bOpen);
	// VRAM(gpu) ������ ���縦 �ؾ� �Ѵ�.

	static float y = 0.5f;
	ImGui::SliderFloat("Y", &y, -1, +1);
	vertices[1].Position.y = y;
	
	D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 6, 0);
}

void Vertex_Line::Render()
{
	
	
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// IA�� ������ �����̶�� ���� ���Ѵ�
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// � ������� �׸� ���̳�?
	//D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 3, 0);
	shader->Draw(0, 1, 3, 3);

	//shader->Draw(0, 0, 1, 0);
	//shader->Draw(0, 1, 1, 1);
	//shader->Draw(0, 2,1, 2);
	//shader->Draw(0, 0,6);
}

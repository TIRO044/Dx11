#include "stdafx.h"
#include "GridDemo.h"

void GridDemo::Initialize()
{
	shader = new Shader(L"MultiWorldShader.fx");

	// vertex
	{
		vertexCount = (width + 1) * (height + 1);
		vertices = new Vertex[vertexCount];
		 
		for(UINT h = 0 ; h < height + 1; h++)
		{
			for (UINT w = 0; w < width + 1; w++)
			{
				UINT index = (width + 1) * h + w;

				vertices[index].Position.x = 0;
				vertices[index].Position.y = (float)h;
				vertices[index].Position.z = (float)w;
			}
		}

		// VertexBuffer
		{
			// DESC는 내림 차순이라는 의미
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
			desc.ByteWidth = sizeof(Vertex) * vertexCount;
			//BindFlages는 파이프라인에 어떻게 바인딩할거냐, 라는 것인데 이게 뭔데
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			// Ram에서 vRam으로 복사한다. 실제로 GPU로 복사해주는 부분
			D3D11_SUBRESOURCE_DATA subResource = { 0 };
			subResource.pSysMem = vertices;

			Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
		}
	}

	// index
	{
		indexCount = width * height * 6;
		indices = new UINT[indexCount];

		UINT index = 0;
		for(UINT h = 0; h < height; h++)
		{
			for (UINT w = 0; w < width; w++)
			{
				indices[index + 0] = (width + 1) * h + w;
				indices[index + 1] = (width + 1) * (h + 1) + w;
				indices[index + 2] = (width + 1) * h + w + 1;
				indices[index + 3] = (width + 1) * h + w + 1;
				indices[index + 4] = (width + 1) * (h + 1) + w;
				indices[index + 5] = (width + 1) * (h + 1) + w + 1;

				index += 6;
			}
		}

		// IndexBuffer
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
			desc.ByteWidth = sizeof(UINT) * indexCount;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA subResource = { 0 };
			subResource.pSysMem = indices;

			Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
		}
	}

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	D3DXMatrixIdentity(&world);
}

void GridDemo::Ready()
{
	
}
void GridDemo::PreRender()
{

}
void GridDemo::PostRender()
{

}
void GridDemo::ResizeScreen()
{

}

void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void GridDemo::Update()
{
}

void GridDemo::Render()
{
	shader->AsScalar("Index")->SetInt(1);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	shader->DrawIndexed(0, 0, indexCount, 0);
}
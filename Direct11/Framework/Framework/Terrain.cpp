#include "Framework.h"
#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	SafeDelete(heightMap);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void Terrain::SetTexture(Shader* shader, wstring heightFile)
{
	myShader = shader;

	if (heightMap != nullptr)
	{
		SafeDelete(heightMap);
	}

	heightMap = new Texture(heightFile);

	SetVertexData();
	SetIndexData();
	SetNormalData();
	CreatBuffer();
}

void Terrain::Update()
{
	if (heightMap == nullptr) return;

	Matrix world;
	D3DXMatrixIdentity(&world);

	myShader->AsMatrix("World")->SetMatrix(world);
	myShader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	myShader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void Terrain::Render()
{
	if (heightMap == nullptr) return;

	UINT stride = sizeof(VertexNormal);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	myShader->DrawIndexed(0, pass, indexCount);
}

void Terrain::SetVertexData()
{
	vector<Color> heights;
	heightMap->ReadPixel(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	w = heightMap->GetWidth();
	h = heightMap->GetHeight();

	vertexCount = w * h;
	SafeDeleteArray(vertices);
	vertices = new TerrainVertex[vertexCount];

	for (UINT z = 0; z < h; z++)
	{
		for (UINT x = 0; x < w; x++)
		{
			auto index = w * z + x;
			auto pixelIndex = w * (h - 1 - z) + x;

			vertices[index].Position.x = static_cast<float>(x);
			vertices[index].Position.y = heights[pixelIndex].r * 255.0f / 10.0f;
			vertices[index].Position.z = static_cast<float>(z);
		}
	}
}

void Terrain::SetIndexData()
{
	indexCount = (w - 1) * (h - 1) * 6;

	auto curCount = 0;
	SafeDeleteArray(indices);
	indices = new UINT[indexCount];
	for (UINT y = 0; y < h - 1; y++)
	{
		for (UINT x = 0; x < w - 1; x++)
		{
			indices[curCount + 0] = w * y + x;
			indices[curCount + 1] = w * (y + 1) + x;
			indices[curCount + 2] = w * y + x + 1;
			indices[curCount + 3] = w * y + x + 1;
			indices[curCount + 4] = w * (y + 1) + x;
			indices[curCount + 5] = w * (y + 1) + x + 1;

			curCount += 6;
		}
	}
}

void Terrain::SetNormalData()
{
	for (UINT i = 0; i < indexCount / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		TerrainVertex v0 = vertices[index0];
		TerrainVertex v1 = vertices[index1];
		TerrainVertex v2 = vertices[index2];


		Vector3 a = v1.Position - v0.Position;
		Vector3 b = v2.Position - v0.Position;

		Vector3 normal;
		D3DXVec3Cross(&normal, &a, &b);

		vertices[index0].Normal += normal;
		vertices[index1].Normal += normal;
		vertices[index2].Normal += normal;
	}

	for (UINT i = 0; i < vertexCount; i++)
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal);
}

void Terrain::CreatBuffer()
{
	// vertet
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(VertexNormal) * vertexCount;

		D3D11_SUBRESOURCE_DATA subResourceData = {0};
		subResourceData.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResourceData, &vertexBuffer));
	}

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * indexCount;

		D3D11_SUBRESOURCE_DATA subResourceData = {0};
		subResourceData.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResourceData, &indexBuffer));
	}
}

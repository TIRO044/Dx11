#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader* shader) : myShader(shader)
{
	D3DXMatrixIdentity(&world);

	sWorld = myShader->AsMatrix("World");
	sView= myShader->AsMatrix("View");
	sProjection= myShader->AsMatrix("Projection");

	srv = myShader->AsSRV("DiffuseMap");
}

Mesh::~Mesh()
{
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	SafeDelete(texture);
}

void Mesh::SetDiffuseMap(wstring file)
{
	SafeDelete(texture);

	texture = new Texture(file);
}

void Mesh::Position(Vector3* position)
{
	*position = myPosition;
}

void Mesh::Position(Vector3& position)
{
	myPosition = position;
	Update();
}

void Mesh::Scale(Vector3* scale)
{
	*scale = myPosition;
}

void Mesh::Scale(Vector3& scale)
{
	myScale = scale;
	Update();
}

void Mesh::Rotate(Vector3* rotation)
{
	*rotation = myRotation;
}

void Mesh::Rotate(Vector3& rotation)
{
	myRotation = rotation;
}

Vector3 Mesh::Forward()
{
	return {world._31, world._32, world._33};
}

Vector3 Mesh::Up()
{
	return {world._21, world._22, world._23};
}

Vector3 Mesh::Right()
{
	return {world._11, world._12, world._13};
}

void Mesh::Render()
{
	if (vertexBuffer == NULL && indexBuffer == NULL)
	{
		Create();
		CreateBuffer();
	}
	
	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sWorld->SetMatrix(world);
	sView->SetMatrix(Context::Get()->View());
	sProjection->SetMatrix(Context::Get()->Projection());

	srv->SetResource(texture->SRV());

	myShader->DrawIndexed(0, 0, indexCount);
}

void Mesh::Update()
{
}

void Mesh::UpdateWorld()
{
	Matrix s, r, t;
	D3DXMatrixScaling(&s, myScale.x, myScale.y, myScale.z);
	D3DXMatrixRotationYawPitchRoll(&r, myRotation.x, myRotation.y, myRotation.z);
	D3DXMatrixTranslation(&t, myPosition.x, myPosition.y, myPosition.z);

	world = s * r * t;
}

void Mesh::CreateBuffer()
{
	// 버택스 만드는 건
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(MeshVertex) * vertexCount;

		D3D11_SUBRESOURCE_DATA subResource = {nullptr };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * indexCount;

		D3D11_SUBRESOURCE_DATA subResource = { nullptr };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}

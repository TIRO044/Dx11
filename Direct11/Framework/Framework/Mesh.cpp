#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader* shader)
	: Renderer(shader)
{
	_sDiffuseMap = _shader->AsSRV("DiffuseMap");
}

Mesh::~Mesh()
{
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(texture);
}

void Mesh::SetDiffuseMap(wstring file)
{
	SafeDelete(texture);

	texture = new Texture(file);
}

void Mesh::Render()
{
	if (_vertexBuffer == nullptr && _indexBuffer == nullptr)
	{
		Create();
		_vertexBuffer = new VertexBuffer(vertices, _vertexCount, sizeof(MeshVertex));
		_indexBuffer = new IndexBuffer(vertices, _indexCount);
	}

	Super::Render();
	
	if(texture != nullptr && _sDiffuseMap != nullptr)
		_sDiffuseMap->SetResource(texture->SRV());

	_shader->DrawIndexed(0, Pass(), _indexCount);
}

void Mesh::Update()
{
	if (_sDiffuseMap == nullptr) return;

	//int p = 0;
	//if(ImGui::InputInt("Pass", &p))
	//{
	//	Pass(p);
	//}

	Super::Update();
}
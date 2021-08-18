#include "Framework.h"
#include "Renderer.h"

Renderer::Renderer(Shader* shader):_shader(shader)
{
	Initialize();
}

Renderer::Renderer(wstring shaderFile): _createShader(true)
{
	_shader = new Shader(shaderFile);

	Initialize();
}

void Renderer::Update()
{
	_transform->Update();
	_perFrame->Update();
}

void Renderer::Render()
{
	if(_vertexBuffer != nullptr)
	{
		_vertexBuffer->Render();

		if(_indexBuffer != nullptr)
		{
			_indexBuffer->Render();
		}
	}
	
	D3D::GetDC()->IASetPrimitiveTopology(_topology);
	
	_transform->Render();
	_perFrame->Render();
}

Renderer::~Renderer()
{
	SafeDelete(_transform);
	SafeDelete(_perFrame);

	if (_createShader == true)
		SafeDelete(_shader);
}

void Renderer::Initialize()
{
	_perFrame = new PerFrame(_shader);
	_transform = new Transform(_shader);
}

#include "Framework.h"
#include "Context.h"

#include "Freedom.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	//assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);

	camera = new Freedom();
	Vector3 p;
	p.x = 70;
	p.y = 0;
	p.z = 0;
	
	camera->Position(p);
}

Context::~Context()
{
	SafeDelete(perspective);
	SafeDelete(viewport);
	SafeDelete(camera);
}

void Context::ResizeScreen()
{
	perspective->Set(D3D::Width(), D3D::Height());
	viewport->Set(D3D::Width(), D3D::Height());
}

void Context::Update()
{
	camera->Update();
}

Matrix Context::View()
{
	Matrix matrix;
	camera->GetMatrix(&matrix);

	return matrix;
}

void Context::Render()
{
	viewport->RSSetViewport();
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);

	return projection;
}

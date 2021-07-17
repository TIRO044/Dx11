#include "stdafx.h"
#include "MeshDemo.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 2, -11);

	meshShader = new Shader(L"MeshShader.fx");
	sDirection = meshShader->AsVector("Direction");

	meshQuad = new MeshQuad(meshShader);
	meshQuad->SetDiffuseMap(L"grgrg.PNG");
}

void MeshDemo::Destroy()
{
	SafeDelete(meshShader);
	SafeDelete(meshQuad);
}

void MeshDemo::Update()
{
	meshQuad->Update();
}

void MeshDemo::Render()
{
	sDirection->SetFloatVector(direction);
	meshQuad->Render();
}
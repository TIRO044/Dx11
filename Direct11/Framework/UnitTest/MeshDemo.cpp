#include "stdafx.h"
#include "MeshDemo.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 2, -11);

	meshShader = new Shader(L"MeshShader.fx");
	sDirection = meshShader->AsVector("Direction");

	//meshQuad = new MeshQuad(meshShader);
	//meshQuad->SetDiffuseMap(L"grgrg.PNG");

	//meshCube = new MeshCube(meshShader);
	//meshCube->SetDiffuseMap(L"grgrg.PNG");
	/*meshGrid = new MeshGrid(meshShader, 0, 0);
	meshGrid->SetDiffuseMap(L"grgrg.PNG");*/

	meshSphere = new MeshSphere(meshShader, 5, 5, 5);
	meshSphere->SetDiffuseMap(L"grgrg.PNG");
}

void MeshDemo::Destroy()
{
	SafeDelete(meshShader);
	SafeDelete(meshQuad);
	SafeDelete(meshCube);
	SafeDelete(meshGrid);
	SafeDelete(meshSphere);
}

void MeshDemo::Update()
{
	//meshQuad->Update();
	//meshCube->Update();
	//meshGrid->Update();
	meshSphere->Update();
}

void MeshDemo::Render()
{
	sDirection->SetFloatVector(direction);
	//meshQuad->Render();
	//meshCube->Render();
	//meshGrid->Render();
	meshSphere->Render();
}
#include "stdafx.h"
#include "MeshDemo.h"

#include "CubeMap.h"

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
	meshSphere->Position(Vector3(-10, -10, 0));
	meshSphere->Scale(Vector3(3, 3, 3));
	
	_cubeMapShader = new Shader(L"CubeMapShader.fx");
	_cubeMap = new CubeMap(_cubeMapShader);
	_cubeMap->SetTextrue(L"Environment/Earth.dds");
	_cubeMap->Position(Vector3(5, 5, 0));
	_cubeMap->Scale(Vector3(3, 3, 3));
}

void MeshDemo::Destroy()
{
	SafeDelete(meshShader);
	SafeDelete(meshQuad);
	SafeDelete(meshCube);
	SafeDelete(meshGrid);
	SafeDelete(meshSphere);
	SafeDelete(_cubeMapShader);
}

void MeshDemo::Update()
{
	//meshQuad->Update();
	//meshCube->Update();
	//meshGrid->Update();
	meshSphere->Update();
	_cubeMap->Update();

	ImGui::InputFloat3("Light Dir", direction);
}

void MeshDemo::Render()
{
	sDirection->SetFloatVector(direction);

	//meshQuad->Render();
	//meshCube->Render();
	//meshGrid->Render();
	meshSphere->Render();
	_cubeMap->Render();
}
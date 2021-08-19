#include "stdafx.h"
#include "MeshDemo.h"

#include "CubeMap.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 2, -11);

	meshShader = new Shader(L"MeshShader.fx");
	sDirection = meshShader->AsVector("Direction");
	auto t = meshShader->AsSRV("DiffuseMap");

	//meshQuad = new MeshQuad(meshShader);
	//meshQuad->SetDiffuseMap(L"grgrg.PNG");

	//meshCube = new MeshCube(meshShader);
	//meshCube->SetDiffuseMap(L"grgrg.PNG");
	/*meshGrid = new MeshGrid(meshShader, 0, 0);
	meshGrid->SetDiffuseMap(L"grgrg.PNG");*/

	//meshSphere = new MeshSphere(meshShader, 5, 5, 5);
	//meshSphere->SetDiffuseMap(L"grgrg.PNG");
	//meshSphere->GetTransform()->Position(Vector3(-10, -10, 0));
	//meshSphere->GetTransform()->Scale(Vector3(3, 3, 3));
	//
	//_cubeMapShader = new Shader(L"CubeMapShader.fx");
	//_cubeMap = new CubeMap(_cubeMapShader);
	//_cubeMap->SetTextrue(L"Environment/GrassCube1024.dds");
	//_cubeMap->GetTransform()->Position(Vector3(7, 7, 0));
	//_cubeMap->GetTransform()->Scale(Vector3(3, 3, 3));

	_cubeSky = new CubeSky(L"Environment/Earth.dds");
}


void MeshDemo::Destroy()
{
	SafeDelete(meshShader);
	SafeDelete(meshQuad);
	SafeDelete(meshCube);
	SafeDelete(meshGrid);
	SafeDelete(meshSphere);
	SafeDelete(_cubeMapShader);
	SafeDelete(_cubeSky);
}

void MeshDemo::Update()
{
	_cubeSky->Update();
	//meshQuad->Update();
	//meshCube->Update();
	//meshGrid->Update();
	//meshSphere->Update();
	//_cubeMap->Update();

	ImGui::InputFloat3("Light Dir", direction);
}

void MeshDemo::Render()
{
	sDirection->SetFloatVector(direction);
	_cubeSky->Render();
	
	//meshQuad->Render();
	//meshCube->Render();
	//meshGrid->Render();
	//meshSphere->Render();
	//_cubeMap->Render();
}
#pragma once
#include "Systems/IExecute.h"
#include "Terrain.h"

class TerrainDemo : public IExecute
{
public:
	void Initialize() override;
	void Ready() override;
	void Destroy() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void ResizeScreen() override;

	void SetTexture(wstring file);

private :
	Shader* shader;
	
	Matrix world;

	Terrain* terrain;
};

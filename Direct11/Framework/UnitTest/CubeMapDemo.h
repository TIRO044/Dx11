#pragma once
#include "Systems/IExecute.h"
#include "CubeMap.h"

class CubeMapDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}
protected:
	Shader* _shader;
	CubeMap* _cubeMap;
};


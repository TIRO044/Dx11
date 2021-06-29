#pragma once
class Terrain
{
public :
	typedef VertexNormal TerrainVertex;

public :
	Terrain();
	~Terrain();

	void Update();
	void Render();

	void Pass(int val) { pass = val; }

public :
	void SetVertexData();
	void SetIndexData();
	void SetNormalData();
	void CreatBuffer();
	void SetTexture(Shader* shader, wstring heightFile);

	float GetHeight(Vector3& position) const;

private:
	int pass = 0;
	Vector4 ShaderColor;
	
	Shader* myShader;
	Texture* heightMap;
	
	UINT w, h;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;
};
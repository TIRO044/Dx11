#pragma once
class Terrain
{
public :
	typedef Vertex TerrainVertex;

public :
	Terrain();
	~Terrain();

	void Update();
	void Render();

	void Pass(UINT val) { pass = val; }

public :
	void SetVertexData();
	void SetIndexData();
	void CreatBuffer();
	void SetTexture(Shader* shader, wstring heightFile);

private:
	UINT pass = 0;
	Shader* myShader;
	Texture* heightMap;
	
	UINT wVertexCount, hVertexCount;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;
};
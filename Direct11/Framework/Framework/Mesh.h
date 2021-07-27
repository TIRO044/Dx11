#pragma once

class Mesh
{
public:
	typedef VertexTextureNormal MeshVertex;
protected:
	Mesh(Shader* shader);
	~Mesh();
public:
	void SetPass(UINT pass) { Pass = pass; }

	void SetDiffuseMap(wstring file);

	void Render();
	void Update();

	Vector3 Forward();
	Vector3 Up();
	Vector3 Right();
	void Position(Vector3* position);
	void Position(Vector3& position);
	void Scale(Vector3* scale);
	void Scale(Vector3& scale);
	void Rotate(Vector3* rotation);
	void Rotate(Vector3& rotation);

	protected:
	
	// World s, r, v ∞ˆ«ÿ¡‡æﬂ «—¥Ÿ.
	void UpdateWorld();

	virtual void Create() = 0;
	void CreateBuffer();
	int Pass = 0;
protected:
	Matrix world;
	
	Vector3 myPosition;
	Vector3 myRotation;
	Vector3 myScale;
	
	Shader* myShader;

	UINT vertexCount;
	MeshVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT* indices;
	UINT indexCount;
	ID3D11Buffer* indexBuffer;
	
	ID3DX11EffectMatrixVariable* sWorld;
	ID3DX11EffectMatrixVariable* sView;
	ID3DX11EffectMatrixVariable* sProjection;

	Texture* texture = nullptr;
	ID3DX11EffectShaderResourceVariable* _sDiffuseMap;
};
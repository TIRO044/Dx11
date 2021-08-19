#include "Framework.h"
#include "MeshSphere.h"

MeshSphere::MeshSphere(Shader* shader, UINT stackCount, UINT sliceCount, float radian) : Mesh(shader)
{
	_stackCount = stackCount;
	_sliceCount = sliceCount;
	_radian = radian;
}

MeshSphere::~MeshSphere()
{
}

void MeshSphere::Create()
{
	vector<MeshVertex> v;
	v.push_back(MeshVertex(0, _radian, 0, 0, 0, 0, 1, 0));

	float phiStep = Math::PI / _stackCount;
	float thetaStep = Math::PI * 2.0f / _sliceCount;

	for (UINT i = 1; i <= _stackCount - 1; i++)
	{
		float phi = i * phiStep;

		for (UINT k = 0; k <= _sliceCount; k++)
		{
			float theta = k * thetaStep;

			Vector3 p = Vector3
			(
				(_radian * sinf(phi) * cosf(theta)),
				(_radian * cos(phi)),
				(_radian * sinf(phi) * sinf(theta))
			);

			Vector3 n;
			D3DXVec3Normalize(&n, &p);

			Vector2 uv = Vector2(theta / (Math::PI * 2), phi / Math::PI);

			v.push_back(MeshVertex(p.x, p.y, p.z, uv.x, uv.y, n.x, n.y, n.z));
		}
	}
	v.push_back(MeshVertex(0, -_radian, 0, 1, 1, 0, -1, 0));


	vertices = new MeshVertex[v.size()];
	_vertexCount = v.size();

	copy(v.begin(), v.end(), stdext::checked_array_iterator<MeshVertex*>(vertices, _vertexCount));

	vector<UINT> i;
	for (UINT k = 1; k <= _sliceCount; k++)
	{
		i.push_back(0);
		i.push_back(k + 1);
		i.push_back(k);
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = _sliceCount + 1;
	for (UINT k = 0; k < _stackCount - 2; k++)
	{
		for (UINT j = 0; j < _sliceCount; j++)
		{
			i.push_back(baseIndex + k * ringVertexCount + j);
			i.push_back(baseIndex + k * ringVertexCount + j + 1);
			i.push_back(baseIndex + (k + 1) * ringVertexCount + j);

			i.push_back(baseIndex + (k + 1) * ringVertexCount + j);
			i.push_back(baseIndex + k * ringVertexCount + j + 1);
			i.push_back(baseIndex + (k + 1) * ringVertexCount + j + 1);
		}
	}

	UINT southPoleIndex = v.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT k = 0; k < _sliceCount; k++)
	{
		i.push_back(southPoleIndex);
		i.push_back(baseIndex + k);
		i.push_back(baseIndex + k + 1);
	}

	indices = new UINT[i.size()];
	_indexCount = i.size();

	copy(i.begin(), i.end(), stdext::checked_array_iterator<UINT*>(indices, _indexCount));

	int a = 0;
}
#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matRotation);
}

Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::Position(Vector3& vec)
{
	position = vec;

	Move();
}

void Camera::Position(Vector3* vec)
{
	*vec = position;
}

void Camera::Rotation(float x, float y, float z)
{
	Rotation(new Vector3(x, y, z));
}

void Camera::Rotation(Vector3& vec)
{
	rotation = vec;

	Rotation();
}

void Camera::Rotation(Vector3* vec)
{
	*vec = rotation;
}

void Camera::RotationDegree(float x, float y, float z)
{
	RotationDegree(new Vector3(x, y, z));
}

void Camera::RotationDegree(Vector3& vec)
{
	//rotation = vec * Math::Pi / 180.f;
	rotation = vec * 0.01745328f;
	Rotation();
}

void Camera::RotationDegree(Vector3* vec)
{
	//rotation = vec * 180.f / Math::Pi ;

	*vec = rotation * 57.29577957f;
}

void Camera::GetMatrix(Matrix* matrix)
{
	//이렇게 하는 것 보다 memcpy가 더 빠르다 ?!
	//*matrix = matView;
	memcpy(matrix, &matView, sizeof(matView));
}

void Camera::Rotation()
{
	{
		Matrix X, Y, Z;
		D3DXMatrixRotationX(&X, rotation.x);
		D3DXMatrixRotationY(&Y, rotation.y);
		D3DXMatrixRotationZ(&Z, rotation.z);

		matRotation = X * Y * Z;

		D3DXVec3TransformNormal(&forward, &Vector3(0, 0, 1), &matRotation);
		D3DXVec3TransformNormal(&up, &Vector3(0, 1, 0), &matRotation);
		D3DXVec3TransformNormal(&right, &Vector3(1, 0, 0), &matRotation);
	}
}

void Camera::Move()
{
	View();
}

void Camera::View()
{
	// LH는 왼손 좌표라는 말
	D3DXMatrixLookAtLH(&matView, &position, &(position + forward), &up);
	// https://docs.microsoft.com/ko-kr/windows/win32/direct3d10/d3d10-d3dxmatrixlookatlh
}

void Camera::Position(float x, float y, float z)
{
	position = Vector3(x,y,z);
	Move();
}
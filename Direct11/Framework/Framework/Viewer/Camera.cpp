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
	Matrix x, y, z;
	
	D3DXMatrixRotationX(&x, rotation.x);
	D3DXMatrixRotationY(&y, rotation.y);
	D3DXMatrixRotationZ(&z, rotation.z);
	// 이것을 하는 이유는, 회전된 공간으로 방향을 바꾸기 위함 그림 (1번 참조)
		// 방향을 특정 공간으로 변환할 때 사용
			// 위치를 특정 공간으로 변환할 때 사용 (자매품)
			// D3DXVec3TransformCoord();

	// 회전이 되었으니 방향 normal들도 변경해주는 것
	matRotation = x + y + z;
	
	D3DXVec3TransformNormal(&forward, &Vector3(0, 0, 1), &matRotation);
	D3DXVec3TransformNormal(&up, &Vector3(0, 1, 0), &matRotation);
	D3DXVec3TransformNormal(&right, &Vector3(1, 0, 0), &matRotation);
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
	
}
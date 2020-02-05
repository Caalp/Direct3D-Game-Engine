#include "Camera.h"

Camera::Camera() :
	cam_pos(0.0f,0.0f,-3.0f),
	cam_right(1.0f,0.0f,0.0f),
	cam_up(0.0f,1.0f,0.0f),
	cam_look(0.0f,0.0f,1.0f)
{
	SetCameraLens(0.25f*3.14f, 800 / 600.0f, 1.0f, 1000.0f);
	theta = 0;
}

DirectX::XMVECTOR Camera::GetPositionXM() const
{
	return DirectX::XMLoadFloat3(&cam_pos);
}

DirectX::XMFLOAT3 Camera::GetPosition() const
{
	return cam_pos;
}

void Camera::SetPosition(float x, float y, float z)
{
	cam_pos = DirectX::XMFLOAT3(x, y, z);
}

void Camera::SetPosition(DirectX::XMFLOAT3 & v)
{
	cam_pos = v;
}


DirectX::XMVECTOR Camera::GetRightXM() const
{
	return DirectX::XMLoadFloat3(&cam_right);
}

DirectX::XMFLOAT3 Camera::GetRight() const
{
	return cam_right;
}

DirectX::XMVECTOR Camera::GetUpXM() const
{
	return DirectX::XMLoadFloat3(&cam_up);
}

DirectX::XMFLOAT3 Camera::GetUp() const
{
	return cam_up;
}

DirectX::XMVECTOR Camera::GetLookXM() const
{
	return DirectX::XMLoadFloat3(&cam_look);
}

DirectX::XMFLOAT3 Camera::GetLook() const
{
	return cam_look;
}

float Camera::GetNearZ() const
{
	return NearZ;
}

float Camera::GetFarZ() const
{
	return FarZ;
}

float Camera::GetAspect() const
{
	return AspectR;
}

float Camera::GetFovY() const
{
	return FovY;
}

float Camera::GetFovX() const
{
	float hw = 0.5f* GetNearPlaneWidth();
	return 2.0f * atan(hw / NearZ);
}

float Camera::GetNearPlaneWidth() const
{
	return AspectR*NearPlaneHeight;
}

float Camera::GetNearPlaneHeight() const
{
	return NearPlaneHeight;
}

float Camera::GetFarPlaneWidth() const
{
	return AspectR* FarPlaneHeight;
}

float Camera::GetFarPlaneHeight() const
{
	return FarPlaneHeight;
}

void Camera::SetCameraLens(float fY, float aspectRatio, float zn, float zf)
{
	//angle
	FovY = fY;
	AspectR = aspectRatio;

	//distance of near and far Z's from camera 
	NearZ = zn;
	FarZ = zf;

	NearPlaneHeight = 2.0f * NearZ * tanf(0.5f*FovY);
	FarPlaneHeight = 2.0f * FarZ * tanf(0.5f* FovY);
	DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovLH(FovY, AspectR, NearZ, FarZ);
	DirectX::XMStoreFloat4x4(&ProjXM, p);
		
}

void Camera::LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp)
{
	DirectX::XMVECTOR L = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, pos));
	DirectX::XMVECTOR R = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, L));
	DirectX::XMVECTOR U = DirectX::XMVector3Cross(L, R);

	DirectX::XMStoreFloat3(&cam_pos, pos);
	DirectX::XMStoreFloat3(&cam_look, L);
	DirectX::XMStoreFloat3(&cam_right, R);
	DirectX::XMStoreFloat3(&cam_up, U);

}

void Camera::LookAt(const DirectX::XMFLOAT3 & pos, const DirectX::XMFLOAT3 & target, const DirectX::XMFLOAT3 & worldUp)
{
	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&worldUp);
	
	LookAt(P, T, U);
}

DirectX::XMMATRIX Camera::GetViewXM() const
{
	return DirectX::XMLoadFloat4x4(&ViewXM);
}

DirectX::XMMATRIX Camera::GetProjXM() const
{
	return DirectX::XMLoadFloat4x4(&ProjXM);
}

DirectX::XMMATRIX Camera::ViewProjXM() const
{
	return DirectX::XMMatrixMultiply(GetViewXM(),GetProjXM());
}

void Camera::Walk(float d)
{
	

	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR l = DirectX::XMLoadFloat3(&cam_look);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&cam_pos);

	DirectX::XMStoreFloat3(&cam_pos, DirectX::XMVectorMultiplyAdd(s, l, p));
	
	
}

void Camera::Strafe(float d)
{
	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR r = DirectX::XMLoadFloat3(&cam_right);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&cam_pos);

	DirectX::XMStoreFloat3(&cam_pos, DirectX::XMVectorMultiplyAdd(s, r, p));

	
}

void Camera::Pitch(float angle)
{
	DirectX::XMMATRIX r = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&cam_right), angle);
	DirectX::XMStoreFloat3(&cam_up, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_up), r));
	DirectX::XMStoreFloat3(&cam_look, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_look), r));

}

void Camera::RotateY(float angle)
{
	DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
	DirectX::XMStoreFloat3(&cam_up, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_up), r));
	DirectX::XMStoreFloat3(&cam_look, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_look), r));
	DirectX::XMStoreFloat3(&cam_right, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_right), r));
	
	
	
}

void Camera::RotateAroundOrigin(float dt)
{
	theta += dt;
	DirectX::XMFLOAT3 l;
	 
	DirectX::XMVECTOR target = { 0.0f,0.0f,0.0f };
	DirectX::XMVECTOR worldUp = { 0.0f,1.0f,0.0f };
	DirectX::XMVECTOR pos = { cam_pos.x,cam_pos.y,cam_pos.z };
	DirectX::XMVECTOR right = { cam_right.x,cam_right.y,cam_right.z };
	DirectX::XMVECTOR dir = DirectX::XMVectorSubtract(target, pos);
	DirectX::XMVECTOR len = DirectX::XMVector3Length(dir);
	dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, pos));
	right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, dir));
	
	//DirectX::XMVector3Normalize(dir);
	DirectX::XMStoreFloat3(&l, len);
	float radius = l.x;
	float x = sin(theta)*radius;
	float z = cos(theta)*radius;
	//sqrt(1.0f - powf(x, x))
	cam_pos.x = x;
	cam_pos.z = z;

	DirectX::XMStoreFloat3(&cam_look, dir);
	DirectX::XMStoreFloat3(&cam_right, right);
}

void Camera::UpdateViewXM()
{
	DirectX::XMVECTOR R = DirectX::XMLoadFloat3(&cam_right);
	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&cam_up);
	DirectX::XMVECTOR L = DirectX::XMLoadFloat3(&cam_look);
	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&cam_pos);

	//  Normalize look vector
	L = DirectX::XMVector3Normalize(L);
	
	U = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(L, R));

	R = DirectX::XMVector3Cross(U, L);

	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));

	DirectX::XMStoreFloat3(&cam_right, R);
	DirectX::XMStoreFloat3(&cam_up, U);
	DirectX::XMStoreFloat3(&cam_look, L);


	ViewXM(0, 0) = cam_right.x;
	ViewXM(1, 0) = cam_right.y;
	ViewXM(2, 0) = cam_right.z;
	ViewXM(3, 0) = x;

	ViewXM(0, 1) = cam_up.x;
	ViewXM(1, 1) = cam_up.y;
	ViewXM(2, 1) = cam_up.z;
	ViewXM(3, 1) = y;

	ViewXM(0, 2) = cam_look.x;
	ViewXM(1, 2) = cam_look.y;
	ViewXM(2, 2) = cam_look.z;
	ViewXM(3, 2) = z;

	ViewXM(0, 3) = 0.0f;
	ViewXM(1, 3) = 0.0f;
	ViewXM(2, 3) = 0.0f;
	ViewXM(3, 3) = 1.0f;

}

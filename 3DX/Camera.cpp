#include "Camera.h"

Camera::Camera() 
{
	
	pos_x = 0;
	pos_y = 0;
	pos_z = 0;

	rot_x = 0;
	rot_y = 0;
	rot_z = 0;
}

void Camera::SetPos(float x, float y, float z)
{
	pos_x = x;
	pos_y = y;
	pos_z = z;
}

void Camera::SetRotation(float rx, float ry, float rz)
{
	rot_x = rx;
	rot_y = ry;
	rot_z = rz;
}

DirectX::XMFLOAT3 Camera::GetPos() const
{
	return DirectX::XMFLOAT3(pos_x,pos_y,pos_z);
}

DirectX::XMFLOAT3 Camera::GetRotation() const
{
	return DirectX::XMFLOAT3(rot_x,rot_y,rot_z);
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return viewMatrix_;
}


void Camera::Render()
{
	DirectX::XMVECTOR up = { 0.0f,1.0f,0.0f,1.0f };
	DirectX::XMVECTOR pos = { pos_x,pos_y,pos_z,1.0f };
	DirectX::XMVECTOR look = { 0.0f,0.0f,1.0f,1.0f };

	float pitch, yaw, roll;

	DirectX::XMMATRIX rotMatrix_;

	/*up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	pos.x = pos_x;
	pos.y = pos_y;
	pos.z = pos_z;


	look.x = 0.0f;
	look.y = 0.0f;
	look.z = 1.0f;*/

	pitch = rot_x * 0.0174532925f;
	yaw = rot_y * 0.0174532925f;
	//roll = rot_z * 0.0174532925f;

	rotMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f);

	look = DirectX::XMVector3Transform(look, rotMatrix_);
	up = DirectX::XMVector3Transform(up, rotMatrix_);

	look = DirectX::XMVectorAdd(pos, look);

	viewMatrix_ = DirectX::XMMatrixLookAtLH(pos, look, up);
}


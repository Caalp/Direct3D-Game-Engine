#include "CameraComponent.h"




//CameraComponent::CameraComponent(const CameraType& camType) : m_camType(camType),
//cam_pos(0.0f, 0.0f, -30.0f),
//cam_right(1.0f, 0.0f, 0.0f),
//cam_up(0.0f, 1.0f, 0.0f),
//cam_look(0.0f, 0.0f, 1.0f)
//{
//
//}
//
//DirectX::XMVECTOR CameraComponent::GetPositionXM() const
//{
//	return DirectX::XMLoadFloat3(&cam_pos);
//}
//
//DirectX::XMFLOAT3 CameraComponent::GetPosition() const
//{
//	return cam_pos;
//}
//
//void CameraComponent::SetPosition(float x, float y, float z)
//{
//	cam_pos = DirectX::XMFLOAT3(x, y, z);
//}
//
//void CameraComponent::SetPosition(DirectX::XMFLOAT3& v)
//{
//	cam_pos = v;
//}
//
//void CameraComponent::SetCamType(CameraType type, float aspectR)
//{
//	m_camType = type;
//	switch (type)
//	{
//	case CameraType::CAM_PERSPECTIVE:
//		// Set as is for now ...
//		SetCameraLens(0.25f * 3.1415926535f, aspectR, 1.0f, 1000.0f);
//		break;
//	case CameraType::CAM_ORTO:
//		InitOrtoProjXM();
//		break;
//	default:
//		break;
//	}
//}
//
//
//DirectX::XMVECTOR CameraComponent::GetRightXM() const
//{
//	return DirectX::XMLoadFloat3(&cam_right);
//}
//
//DirectX::XMFLOAT3 CameraComponent::GetRight() const
//{
//	return cam_right;
//}
//
//DirectX::XMVECTOR CameraComponent::GetUpXM() const
//{
//	return DirectX::XMLoadFloat3(&cam_up);
//}
//
//DirectX::XMFLOAT3 CameraComponent::GetUp() const
//{
//	return cam_up;
//}
//
//DirectX::XMVECTOR CameraComponent::GetLookXM() const
//{
//	return DirectX::XMLoadFloat3(&cam_look);
//}
//
//DirectX::XMFLOAT3 CameraComponent::GetLook() const
//{
//	return cam_look;
//}
//
//float CameraComponent::GetNearZ() const
//{
//	return NearZ;
//}
//
//float CameraComponent::GetFarZ() const
//{
//	return FarZ;
//}
//
//float CameraComponent::GetAspect() const
//{
//	return AspectR;
//}
//
//float CameraComponent::GetFovY() const
//{
//	return FovY;
//}
//
//float CameraComponent::GetFovX() const
//{
//	float hw = 0.5f * GetNearPlaneWidth();
//	return 2.0f * atan(hw / NearZ);
//}
//
//float CameraComponent::GetNearPlaneWidth() const
//{
//	return AspectR * NearPlaneHeight;
//}
//
//float CameraComponent::GetNearPlaneHeight() const
//{
//	return NearPlaneHeight;
//}
//
//float CameraComponent::GetFarPlaneWidth() const
//{
//	return AspectR * FarPlaneHeight;
//}
//
//float CameraComponent::GetFarPlaneHeight() const
//{
//	return FarPlaneHeight;
//}
//
//void CameraComponent::InitOrtoProjXM()
//{
//	DirectX::XMFLOAT4X4 ortographicXM;
//	ortographicXM(0, 0) = 2.0f / NearPlaneWidth;
//	ortographicXM(0, 1) = 0.0f;
//	ortographicXM(0, 2) = 0.0f;
//	ortographicXM(0, 3) = 0.0f;
//
//	ortographicXM(1, 0) = 0.0f;
//	ortographicXM(1, 1) = 2.0f / NearPlaneHeight;
//	ortographicXM(1, 2) = 0.0f;
//	ortographicXM(1, 3) = 0.0f;
//
//	ortographicXM(2, 0) = 0.0f;
//	ortographicXM(2, 1) = 0.0f;
//	ortographicXM(2, 2) = 1.0f / FarZ - NearZ;
//	ortographicXM(2, 3) = 0.0f;
//
//	ortographicXM(3, 0) = 0.0f;
//	ortographicXM(3, 1) = 0.0f;
//	ortographicXM(3, 2) = NearZ / NearZ - FarZ;
//	ortographicXM(3, 3) = 1;
//	//ProjXM = ortographicXM;
//	DirectX::XMLoadFloat4x4(&ProjXM);
//}
//
//CameraComponent::CameraType CameraComponent::GetCamType() const
//{
//	return m_camType;
//}
//
//void CameraComponent::SetCameraLens(float fY, float aspectRatio, float zn, float zf)
//{
//	FovY = fY;
//	AspectR = aspectRatio;
//
//	NearZ = zn;
//	FarZ = zf;
//
//	NearPlaneHeight = 2.0f * NearZ * tanf(0.5f * FovY);
//	FarPlaneHeight = 2.0f * FarZ * tanf(0.5f * FovY);
//	DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovLH(FovY, AspectR, NearZ, FarZ);
//	DirectX::XMStoreFloat4x4(&ProjXM, p);
//
//}
//
//void CameraComponent::LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp)
//{
//	DirectX::XMVECTOR L = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, pos));
//	DirectX::XMVECTOR R = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, L));
//	DirectX::XMVECTOR U = DirectX::XMVector3Cross(L, R);
//
//	DirectX::XMStoreFloat3(&cam_pos, pos);
//	DirectX::XMStoreFloat3(&cam_look, L);
//	DirectX::XMStoreFloat3(&cam_right, R);
//	DirectX::XMStoreFloat3(&cam_up, U);
//
//}
//
//void CameraComponent::LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& worldUp)
//{
//	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&pos);
//	DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&target);
//	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&worldUp);
//
//	LookAt(P, T, U);
//}
//
//DirectX::XMMATRIX CameraComponent::GetViewXM() const
//{
//	return DirectX::XMLoadFloat4x4(&ViewXM);
//}
//
//DirectX::XMMATRIX CameraComponent::GetProjXM() const
//{
//	return DirectX::XMLoadFloat4x4(&ProjXM);
//}
//
//DirectX::XMMATRIX CameraComponent::ViewProjXM() const
//{
//
//	return DirectX::XMMatrixMultiply(GetViewXM(), GetProjXM());
//}
//
//void CameraComponent::Walk(float d)
//{
//	//cam_pos += d * cam_look;
//
//	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
//	DirectX::XMVECTOR l = DirectX::XMLoadFloat3(&cam_look);
//	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&cam_pos);
//
//	DirectX::XMStoreFloat3(&cam_pos, DirectX::XMVectorMultiplyAdd(s, l, p));
//}
//
//void CameraComponent::Strafe(float d)
//{
//	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
//	DirectX::XMVECTOR r = DirectX::XMLoadFloat3(&cam_right);
//	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&cam_pos);
//
//	DirectX::XMStoreFloat3(&cam_pos, DirectX::XMVectorMultiplyAdd(s, r, p));
//}
//
//void CameraComponent::Pitch(float angle)
//{
//	DirectX::XMMATRIX r = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&cam_right), angle);
//	DirectX::XMStoreFloat3(&cam_up, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_up), r));
//	DirectX::XMStoreFloat3(&cam_look, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_look), r));
//
//}
//
//void CameraComponent::RotateY(float angle)
//{
//	DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
//	DirectX::XMStoreFloat3(&cam_up, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_up), r));
//	DirectX::XMStoreFloat3(&cam_look, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_look), r));
//	DirectX::XMStoreFloat3(&cam_right, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_right), r));
//
//}
//
//void CameraComponent::Yaw(float angle)
//{
//	DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
//	DirectX::XMStoreFloat3(&cam_up, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_up), r));
//	DirectX::XMStoreFloat3(&cam_look, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_look), r));
//	DirectX::XMStoreFloat3(&cam_right, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&cam_right), r));
//}
//
//void CameraComponent::UpdateViewXM()
//{
//	DirectX::XMVECTOR R = DirectX::XMLoadFloat3(&cam_right);
//	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&cam_up);
//	DirectX::XMVECTOR L = DirectX::XMLoadFloat3(&cam_look);
//	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&cam_pos);
//
//	//  Normalize look vector
//	L = DirectX::XMVector3Normalize(L);
//
//	U = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(L, R));
//
//	R = DirectX::XMVector3Cross(U, L);
//
//	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
//	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
//	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));
//
//	DirectX::XMStoreFloat3(&cam_right, R);
//	DirectX::XMStoreFloat3(&cam_up, U);
//	DirectX::XMStoreFloat3(&cam_look, L);
//
//
//	ViewXM(0, 0) = cam_right.x;
//	ViewXM(1, 0) = cam_right.y;
//	ViewXM(2, 0) = cam_right.z;
//	ViewXM(3, 0) = x;
//
//	ViewXM(0, 1) = cam_up.x;
//	ViewXM(1, 1) = cam_up.y;
//	ViewXM(2, 1) = cam_up.z;
//	ViewXM(3, 1) = y;
//
//	ViewXM(0, 2) = cam_look.x;
//	ViewXM(1, 2) = cam_look.y;
//	ViewXM(2, 2) = cam_look.z;
//	ViewXM(3, 2) = z;
//
//	ViewXM(0, 3) = 0.0f;
//	ViewXM(1, 3) = 0.0f;
//	ViewXM(2, 3) = 0.0f;
//	ViewXM(3, 3) = 1.0f;
//
//}

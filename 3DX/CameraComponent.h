#pragma once
#include "Component.h"
#include "TransformationBuffer.h"


enum CameraType
{
	CAM_PERSPECTIVE,
	CAM_ORTO
};
class MainCamera : public Component
{

};


struct CameraBuffer
{
	DirectX::XMMATRIX viewXM;
	DirectX::XMMATRIX projXM;
	DirectX::XMFLOAT3 cameraPos;
	float padding;
};
class CameraComponent : public Component
{
public:
	CameraComponent();

	void Init();
	/* Components should be move constructable and assignable */
	CameraComponent(CameraComponent&& rhs);

	CameraComponent& operator=(CameraComponent&& rhs);


	void UpdateXM(float dt);

	void SetCameraLens(float fY, float aspectRatio, float zn, float zf);


	void LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& worldUp);


	void Walk(float d);


	void Strafe(float d);

	void Pitch(float angle);


	void RotateY(float angle);


	void Yaw(float angle);


	DirectX::XMMATRIX ViewProjXM() const;

	void UpdateAndBindCameraBuffer();

	void DrawImgui() override;

public:
	CameraBuffer camBuff;
	std::vector<char> bytes;
	U16 tBuffer;
	//VSConstBuff<std::vector<char>> tBuffer{ sizeof(CameraBuffer) };
	std::string m_Name;
	CameraType m_CamType;

	DirectX::XMFLOAT3 m_CamPos;
	DirectX::XMFLOAT3 m_CamRight;
	DirectX::XMFLOAT3 m_CamUp;
	DirectX::XMFLOAT3 m_CamLook;

	// Frustum properties
	float m_NearZ;
	float m_FarZ;
	float m_AspectR;
	float m_FovY;
	float m_NearPlaneHeight;
	float m_FarPlaneWidth;
	float m_FarPlaneHeight;
	float m_NearPlaneWidth;
	// Matrices
	DirectX::XMFLOAT4X4 m_ViewXM;
	DirectX::XMFLOAT4X4 m_ProjXM;
	DirectX::XMMATRIX m_ViewProjXM;

};
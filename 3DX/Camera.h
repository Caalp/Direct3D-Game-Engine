#pragma once

#include <DirectXMath.h>
#include <memory>

class Camera 
{
public:
	Camera();
	Camera(const Camera&) = delete;
	// Getter and setters for camera position
	DirectX::XMVECTOR GetPositionXM() const;
	DirectX::XMFLOAT3 GetPosition() const;
	void SetPosition(float, float, float);
	void SetPosition(DirectX::XMFLOAT3& v);
	

	// Camera base vectors
	DirectX::XMVECTOR GetRightXM() const;
	DirectX::XMFLOAT3 GetRight() const;
	DirectX::XMVECTOR GetUpXM() const;
	DirectX::XMFLOAT3 GetUp() const;
	DirectX::XMVECTOR GetLookXM() const;
	DirectX::XMFLOAT3 GetLook() const;

	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspect() const;
	float GetFovY() const;
	float GetFovX() const;

	float GetNearPlaneWidth() const;
	float GetNearPlaneHeight() const;
	float GetFarPlaneWidth() const;
	float GetFarPlaneHeight() const;


	void SetCameraLens(float fY, float aspectRatio, float zn, float zf);

	void LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp);
	void LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& worldUp);

	DirectX::XMMATRIX GetViewXM() const;
	DirectX::XMMATRIX GetProjXM() const;
	DirectX::XMMATRIX ViewProjXM() const;

	//walk or strafe

	void Walk(float d);
	void Strafe(float d);

	//Rotation
	void Pitch(float angle);
	void RotateY(float angle);

	void UpdateViewXM();
	//void Render();
	
	
	

private:
	DirectX::XMFLOAT3 cam_pos;
	DirectX::XMFLOAT3 cam_right;
	DirectX::XMFLOAT3 cam_up;
	DirectX::XMFLOAT3 cam_look;
	
	// Frustum properties
	float NearZ;
	float FarZ;
	float AspectR;
	float FovY;
	float NearPlaneHeight;
	float FarPlaneWidth;
	float FarPlaneHeight;
	float NearPlaneWidth;
	// Matrices
	DirectX::XMFLOAT4X4 ViewXM;
	DirectX::XMFLOAT4X4 ProjXM;

	
	
	
};


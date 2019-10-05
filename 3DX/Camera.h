#pragma once

#include <DirectXMath.h>
#include <memory>



class Camera 
{
	friend class TransCB_;
public:
	Camera();
	Camera(const Camera&) = delete;
		
	void SetPos(float, float, float);
	void SetRotation(float, float, float);

	DirectX::XMFLOAT3 GetPos() const;
	DirectX::XMFLOAT3 GetRotation() const;
	DirectX::XMMATRIX GetViewMatrix() const;
	void Render();
	
	
	

private:
	float pos_x, pos_y, pos_z;
	float rot_x, rot_y, rot_z;

	DirectX::XMMATRIX viewMatrix_;
	
	
};


#pragma once
#include "Component.h"


template<typename T>
class VSConstBuff;



class TransformComponent : public Component
{
	friend class Entity;
public:

	struct TransformBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldInverseTranspose;
	};


public:
	TransformComponent() : m_TBuffer(std::make_shared<VSConstBuff<std::vector<char>>>(sizeof(TransformComponent::TransformBuffer))),
		m_Translation({0.0f,0.0f,0.0f}),
		m_Rotation({0.0f,0.0f,0.0f}),
		m_Scaling({1.0f,1.0f,1.0f})
					
	{

	}
	TransformComponent(const TransformComponent& rhs);
	TransformComponent(TransformComponent&& rhs);
	TransformComponent& operator=(TransformComponent& rhs) = default;
	TransformComponent& operator=(TransformComponent&& rhs) = default;
	void SetTranslation(DirectX::XMFLOAT3 t);
	void SetRotation(DirectX::XMFLOAT3 r);
	void SetScaling(DirectX::XMFLOAT3 s);
	void SetBuffer(std::shared_ptr<VSConstBuff<std::vector<char>>> buff);
	std::shared_ptr<VSConstBuff<std::vector<char>>>& GetTransformBuffer()
	{
		return m_TBuffer;
	}
	inline const DirectX::XMMATRIX& GetInverseTransform() const;

	inline const DirectX::XMMATRIX& GetMatrix() const;
	

	virtual void DrawImgui() override;

public:
	std::shared_ptr<VSConstBuff<std::vector<char>>> m_TBuffer;
protected:
	
	DirectX::XMFLOAT3 m_Translation;
	DirectX::XMFLOAT3 m_Rotation;
	DirectX::XMFLOAT3 m_Scaling;
};

inline const DirectX::XMMATRIX& TransformComponent::GetInverseTransform() const
{
	DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(this->GetMatrix());
	return DirectX::XMMatrixInverse(&determinant, this->GetMatrix());

}
inline const DirectX::XMMATRIX& TransformComponent::GetMatrix() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z) *
		DirectX::XMMatrixTranslation(m_Translation.x, m_Translation.y, m_Translation.z) *
		DirectX::XMMatrixScaling(m_Scaling.x, m_Scaling.y, m_Scaling.z);
}
#pragma once
#include <directxmath.h>
#include <memory>
#include "additional_headers.h"
#include "Technique.h"
#include "Imgui/imgui.h"
#include "ImguiHandler.h"
#include "TransformationBuffer.h"

// Is there any benefit for each component being able to have its own update method??
// Every object should define its own update method
// We need Position, Rotation, Scaling for each object
// We should be able to alter each component seperately or with matrix
// Model component can be created and attached to the object to be used later for drawing purpose
// How to decouple submition process from component??

struct Component
{
	virtual void Draw(){};
};


#pragma region Renderable
struct Renderable :public Component
{

	Renderable() = default;
	Renderable(Renderable&& rhs)
	{
		this->vertexBuffer = std::move(rhs.vertexBuffer);
		this->primitiveTopology = std::move(rhs.primitiveTopology);
		this->indexBuffer = std::move(rhs.indexBuffer);
		this->techniques = std::move(rhs.techniques);
	
	}
	Renderable(const Renderable& rhs) = default;
	Renderable& operator=(Renderable&& rhs) = default;
	Renderable& operator=(const Renderable& rhs) = default;


	void AppendTechnique(const Technique& tech)
	{
		for (const auto& tec : techniques)
		{
			if (tec.GetName() == tech.GetName())
			{
				return;
			}
		}


		techniques.push_back(tech);
	}
	void Bind(Graphics& gfx) const
	{
		vertexBuffer->Bind(gfx);
		primitiveTopology->Bind(gfx);
		indexBuffer->Bind(gfx);
	}

	
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<PrimitiveTopology> primitiveTopology;
	std::unique_ptr<IndexBuff> indexBuffer;
	std::vector<Technique> techniques;
};
#pragma endregion

#pragma region Transformation
struct TransformationComponent: public Component
{

	TransformationComponent() = default;

	TransformationComponent(const TransformationComponent& rhs)
	{
		this->translation = rhs.translation;
		this->rotation = rhs.rotation;
		this->scaling = rhs.scaling;
		this->tBuffer = rhs.tBuffer;
	}
	TransformationComponent& operator=(TransformationComponent& rhs) = default;
	TransformationComponent(TransformationComponent&& rhs)
	{

		this->translation = std::move(rhs.translation);
		this->rotation = std::move(rhs.rotation);
		this->scaling = std::move(rhs.scaling);
		this->tBuffer = std::move(tBuffer);
	}
	TransformationComponent& operator=(TransformationComponent&& rhs) = default;

	inline const DirectX::XMMATRIX& GetInverseTransform() const
	{
		DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(this->GetMatrix());
		return DirectX::XMMatrixInverse(&determinant, this->GetMatrix());
	}
	inline const DirectX::XMMATRIX& GetMatrix() const
	{
		
		return DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
				DirectX::XMMatrixTranslation(translation.x, translation.y, translation.z) *
					DirectX::XMMatrixScaling(scaling.x, scaling.y, scaling.z);

	}


	void Draw() override
	{
		ImGui::DragFloat3("##Position", &translation.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Position"))
		{
			translation = { 0.0f, 0.0f, 0.0f };
		}

		ImGui::DragFloat3("##Rotation", &rotation.x, 0.01f);

		ImGui::SameLine();
		if (ImGui::Button("Rotation"))
		{
			translation = { 0.0f, 0.0f, 0.0f };
		}

		ImGui::DragFloat3("##Scaling", &scaling.x, 0.01f);

		ImGui::SameLine();
		if (ImGui::Button("Scaling"))
		{
			scaling = { 1.0f, 1.0f, 1.0f };
		}

		/*static bool lockedFirstFrame = false;
		if (m_LockScale)
		{
			static Vector3 lockedScale;
			static float scaleRatioYX;
			static float scaleRatioZX;
			if (!lockedFirstFrame)
			{
				lockedScale = m_TransformBuffer.m_Scale;
				scaleRatioYX = lockedScale.y / lockedScale.x;
				scaleRatioZX = lockedScale.z / lockedScale.x;
				lockedFirstFrame = true;
			}

			if (lockedScale.x - m_TransformBuffer.m_Scale.x)
			{
				lockedScale.y = lockedScale.x * scaleRatioYX;
				lockedScale.z = lockedScale.x * scaleRatioZX;
			}
			else if (lockedScale.y - m_TransformBuffer.m_Scale.y)
			{
				lockedScale.x = lockedScale.y / scaleRatioYX;
				lockedScale.z = lockedScale.y * scaleRatioZX / scaleRatioYX;
			}
			else if (lockedScale.z - m_TransformBuffer.m_Scale.z)
			{
				lockedScale.x = lockedScale.z / scaleRatioZX;
				lockedScale.y = lockedScale.z * scaleRatioYX / scaleRatioZX;
			}

			m_TransformBuffer.m_Scale = { lockedScale.x, lockedScale.y, lockedScale.z };
			ImGui::DragFloat3("##Scale", &lockedScale.x, 0.01f, 0.0f, 0.0f);
		}
		else
		{
			lockedFirstFrame = false;
			ImGui::DragFloat3("##Scale", &m_TransformBuffer.m_Scale.x, 0.01f, 0.0f, 0.0f);
		}*/

		/*ImGui::SameLine();
		if (ImGui::Button("Scale"))
		{
			m_TransformBuffer.m_Scale = { 1.0f, 1.0f, 1.0f };
		}

		ImGui::Checkbox("Lock Scale", &m_LockScale);

		ImGui::DragFloat3("##Center", &m_TransformBuffer.m_BoundingBox.Center.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Center"))
		{
			m_TransformBuffer.m_BoundingBox.Center = { 0.0f, 0.0f, 0.0f };
		}

		ImGui::DragFloat3("##Bounds", &m_TransformBuffer.m_BoundingBox.Extents.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Extents"))
		{
			m_Owner->onAllComponentsAdded();
		}*/

		/*if (ImGui::TreeNode("Pass Down"))
		{
			ImGui::CheckboxFlags("All", &m_TransformPassDown, (int)TransformPassDown::All);
			ImGui::CheckboxFlags("Position", &m_TransformPassDown, (int)TransformPassDown::Position);
			ImGui::CheckboxFlags("Rotation", &m_TransformPassDown, (int)TransformPassDown::Rotation);
			ImGui::CheckboxFlags("Scale", &m_TransformPassDown, (int)TransformPassDown::Scale);

			ImGui::TreePop();
		}*/

	}
	// 
	std::shared_ptr<VSConstBuff<TransformBuffer>> tBuffer;
	DirectX::XMFLOAT3 translation;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scaling;
};
#pragma endregion 
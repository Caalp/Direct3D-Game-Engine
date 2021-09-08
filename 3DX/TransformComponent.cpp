#include "TransformComponent.h"
#include "Imgui/imgui.h"
#include "TransformationBuffer.h"

TransformComponent::TransformComponent(const TransformComponent& rhs)
{
	this->m_Translation = rhs.m_Translation;
	this->m_Rotation = rhs.m_Rotation;
	this->m_Scaling = rhs.m_Scaling;
	this->m_TBuffer = rhs.m_TBuffer;
}

TransformComponent::TransformComponent(TransformComponent&& rhs)
{
	this->m_Translation = std::move(rhs.m_Translation);
	this->m_Rotation = std::move(rhs.m_Rotation);
	this->m_Scaling = std::move(rhs.m_Scaling);
	this->m_TBuffer = std::move(rhs.m_TBuffer);
}

void TransformComponent::SetTranslation(DirectX::XMFLOAT3 t)
{
	m_Translation = std::move(t);
}

void TransformComponent::SetRotation(DirectX::XMFLOAT3 r)
{
	m_Rotation = std::move(r);
}

void TransformComponent::SetScaling(DirectX::XMFLOAT3 s)
{
	m_Scaling = std::move(s);
}

void TransformComponent::SetBuffer(std::shared_ptr<VSConstBuff<std::vector<char>>> buff)
{
	m_TBuffer = std::move(buff);
}


void TransformComponent::DrawImgui()
{

	if (ImGui::BeginTabItem("TransformComponent", nullptr, ImGuiTabItemFlags_NoCloseWithMiddleMouseButton))
	{


		ImGui::DragFloat3("##Position", &m_Translation.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Position"))
		{
			m_Translation = { 0.0f, 0.0f, 0.0f };
		}

		ImGui::DragFloat3("##Rotation", &m_Rotation.x, 0.01f);

		ImGui::SameLine();
		if (ImGui::Button("Rotation"))
		{
			m_Rotation = { 0.0f, 0.0f, 0.0f };
		}

		ImGui::DragFloat3("##Scaling", &m_Scaling.x, 0.01f);

		ImGui::SameLine();
		if (ImGui::Button("Scaling"))
		{
			m_Scaling = { 1.0f, 1.0f, 1.0f };
		}

		ImGui::EndTabItem();

	}
	
}

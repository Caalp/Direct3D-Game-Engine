#pragma once
#include "Components.h"

enum CameraType
{
	CAM_PERSPECTIVE,
	CAM_ORTO
};
struct MainCamera : public Component
{

};
struct CameraComponent : public Component
{
	CameraComponent() = default;

	/* Components should be move constructable and assignable */
	CameraComponent(CameraComponent&& rhs)
	{
		m_Name = std::move(rhs.m_Name);
		m_CamType = std::move(rhs.m_CamType);
		m_CamUp = std::move(rhs.m_CamUp);
		m_CamRight = std::move(rhs.m_CamRight);
		m_CamLook = std::move(rhs.m_CamLook);
		m_CamPos = std::move(rhs.m_CamPos);
		m_AspectR = std::move(rhs.m_AspectR);
		m_FovY = std::move(rhs.m_FovY);
		m_FarZ = std::move(rhs.m_FarZ);
		m_FarPlaneHeight = std::move(rhs.m_FarPlaneHeight);
		m_FarPlaneWidth = std::move(rhs.m_FarPlaneWidth);
		m_NearZ = std::move(rhs.m_NearZ);
		m_NearPlaneHeight = std::move(rhs.m_NearPlaneHeight);
		m_NearPlaneWidth = std::move(rhs.m_NearPlaneWidth);
		m_ProjXM = std::move(rhs.m_ProjXM);



	}
	CameraComponent& operator=(CameraComponent&& rhs)
	{
		m_Name = std::move(rhs.m_Name);
		m_CamType = std::move(rhs.m_CamType);
		m_CamUp = std::move(rhs.m_CamUp);
		m_CamRight = std::move(rhs.m_CamRight);
		m_CamLook = std::move(rhs.m_CamLook);
		m_CamPos = std::move(rhs.m_CamPos);
		m_AspectR = std::move(rhs.m_AspectR);
		m_FovY = std::move(rhs.m_FovY);
		m_FarZ = std::move(rhs.m_FarZ);
		m_FarPlaneHeight = std::move(rhs.m_FarPlaneHeight);
		m_FarPlaneWidth = std::move(rhs.m_FarPlaneWidth);
		m_NearZ = std::move(rhs.m_NearZ);
		m_NearPlaneHeight = std::move(rhs.m_NearPlaneHeight);
		m_NearPlaneWidth = std::move(rhs.m_NearPlaneWidth);
		m_ProjXM = std::move(rhs.m_ProjXM);

		return *this;

	}

	void UpdateXM(float dt)
	{
		DirectX::XMVECTOR R = DirectX::XMLoadFloat3(&m_CamRight);
		DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&m_CamUp);
		DirectX::XMVECTOR L = DirectX::XMLoadFloat3(&m_CamLook);
		DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&m_CamPos);

		//  Normalize look vector
		L = DirectX::XMVector3Normalize(L);

		U = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(L, R));

		R = DirectX::XMVector3Cross(U, L);

		float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
		float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
		float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));

		DirectX::XMStoreFloat3(&m_CamRight, R);
		DirectX::XMStoreFloat3(&m_CamUp, U);
		DirectX::XMStoreFloat3(&m_CamLook, L);


		m_ViewXM(0, 0) = m_CamRight.x;
		m_ViewXM(1, 0) = m_CamRight.y;
		m_ViewXM(2, 0) = m_CamRight.z;
		m_ViewXM(3, 0) = x;

		m_ViewXM(0, 1) = m_CamUp.x;
		m_ViewXM(1, 1) = m_CamUp.y;
		m_ViewXM(2, 1) = m_CamUp.z;
		m_ViewXM(3, 1) = y;

		m_ViewXM(0, 2) = m_CamLook.x;
		m_ViewXM(1, 2) = m_CamLook.y;
		m_ViewXM(2, 2) = m_CamLook.z;
		m_ViewXM(3, 2) = z;

		m_ViewXM(0, 3) = 0.0f;
		m_ViewXM(1, 3) = 0.0f;
		m_ViewXM(2, 3) = 0.0f;
		m_ViewXM(3, 3) = 1.0f;

		m_ViewProjXM = DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&m_ViewXM), DirectX::XMLoadFloat4x4(&m_ProjXM));
	}
	void SetCameraLens(float fY, float aspectRatio, float zn, float zf)
	{
		m_FovY = fY;
		m_AspectR = aspectRatio;

		m_NearZ = zn;
		m_FarZ = zf;

		m_NearPlaneHeight = 2.0f * m_NearZ * tanf(0.5f*m_FovY);
		m_FarPlaneHeight = 2.0f * m_FarZ * tanf(0.5f* m_FovY);
		DirectX::XMMATRIX p = DirectX::XMMatrixPerspectiveFovLH(m_FovY, m_AspectR, m_NearZ, m_FarZ);
		DirectX::XMStoreFloat4x4(&m_ProjXM, p);
		
	}

	void LookAt(const DirectX::XMFLOAT3 & pos, const DirectX::XMFLOAT3 & target, const DirectX::XMFLOAT3 & worldUp)
	{
		DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&pos);
		DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&target);
		DirectX::XMVECTOR UP = DirectX::XMLoadFloat3(&worldUp);
		


		DirectX::XMVECTOR L = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(T, P));
		DirectX::XMVECTOR R = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(UP, L));
		DirectX::XMVECTOR U = DirectX::XMVector3Cross(L, R);
		
		DirectX::XMStoreFloat3(&m_CamPos, P);
		DirectX::XMStoreFloat3(&m_CamLook, L);
		DirectX::XMStoreFloat3(&m_CamRight, R);
		DirectX::XMStoreFloat3(&m_CamUp, U);

	}

	void Walk(float d)
	{

		DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
		DirectX::XMVECTOR l = DirectX::XMLoadFloat3(&m_CamLook);
		DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&m_CamPos);

		DirectX::XMStoreFloat3(&m_CamPos, DirectX::XMVectorMultiplyAdd(s, l, p));
	}

	void Strafe(float d)
	{
		DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
		DirectX::XMVECTOR r = DirectX::XMLoadFloat3(&m_CamRight);
		DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&m_CamPos);

		DirectX::XMStoreFloat3(&m_CamPos, DirectX::XMVectorMultiplyAdd(s, r, p));
	}

	void Pitch(float angle)
	{
		DirectX::XMMATRIX r = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&m_CamRight), angle);
		DirectX::XMStoreFloat3(&m_CamUp, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamUp), r));
		DirectX::XMStoreFloat3(&m_CamLook, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamLook), r));

	}

	void RotateY(float angle)
	{
		DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
		DirectX::XMStoreFloat3(&m_CamUp, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamUp), r));
		DirectX::XMStoreFloat3(&m_CamLook, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamLook), r));
		DirectX::XMStoreFloat3(&m_CamRight, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamRight), r));

	}

	void Yaw(float angle)
	{
		DirectX::XMMATRIX r = DirectX::XMMatrixRotationY(angle);
		DirectX::XMStoreFloat3(&m_CamUp, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamUp), r));
		DirectX::XMStoreFloat3(&m_CamLook, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamLook), r));
		DirectX::XMStoreFloat3(&m_CamRight, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&m_CamRight), r));
	}

	DirectX::XMMATRIX ViewProjXM() const
	{

		return DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&m_ViewXM), DirectX::XMLoadFloat4x4(&m_ProjXM));
	}

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

	void DrawImgui()
	{

		static bool showMatrices = false;
		ImGui::Begin(m_Name.c_str());
		ImGui::DragFloat3("##Position", &m_CamPos.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Position"))
		{
			m_CamPos = { 0.0f, 0.0f, -30.0f };
		}
		ImGui::DragFloat3("##Right", &m_CamRight.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Right"))
		{
			m_CamRight = { 1.0f, 0.0f, 0.0f };
		}
		ImGui::DragFloat3("##Up", &m_CamUp.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Up"))
		{
			m_CamUp = { 0.0f, 1.0f, 0.0f };
		}

		ImGui::DragFloat3("##Look", &m_CamLook.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::Button("Look"))
		{
			m_CamLook = { 0.0f, 0.0f, 1.0f };
		}
		ImGui::Checkbox("Show Matrices", &showMatrices);

		if (showMatrices)
		{
			if (ImGui::CollapsingHeader("View Matrix"))
			{
				ImGui::DragFloat3("##ViewXM1", &m_ViewXM._11, 0.01f);
				ImGui::DragFloat3("##ViewXM2", &m_ViewXM._21, 0.01f);
				ImGui::DragFloat3("##ViewXM3", &m_ViewXM._31, 0.01f);
				ImGui::DragFloat3("##ViewXM4", &m_ViewXM._41, 0.01f);
			}
			if (ImGui::CollapsingHeader("Projection Matrix"))
			{
				ImGui::DragFloat3("##ViewXM1", &m_ProjXM._11, 0.01f);
				ImGui::DragFloat3("##ViewXM2", &m_ProjXM._21, 0.01f);
				ImGui::DragFloat3("##ViewXM3", &m_ProjXM._31, 0.01f);
				ImGui::DragFloat3("##ViewXM4", &m_ProjXM._41, 0.01f);
			}
		

		}

		std::vector<const char*> camNames;
		auto  t = ECSFactory::GetComponents<CameraComponent>();

		for (auto e : t)
		{
			const auto& cam = t.get(e);
			camNames.emplace_back(cam.m_Name.c_str());
		}

		//ImGui::Separator();
		//ImGui::PopStyleColor();
		static int item_current_idx = 0;                    
		const char* combo_label = camNames[item_current_idx];  
		if (ImGui::BeginCombo("Active Camera", combo_label, 0))
		{
			for (int n = 0; n < camNames.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(camNames[n], is_selected))
					item_current_idx = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		auto cc = ECSFactory::GetComponents<CameraComponent,MainCamera>();
		auto mainCam = cc.front();

		if (cc.get<CameraComponent>(mainCam).m_Name != camNames[item_current_idx])
		{

			ECSFactory::RemoveComponent<MainCamera>(mainCam);
			auto allCameras = ECSFactory::GetComponents<CameraComponent>();
			for (auto id : allCameras)
			{
				auto& cam = allCameras.get(id);
				if (cam.m_Name == camNames[item_current_idx])
				{
					ECSFactory::AddComponent<MainCamera>(id);
					break;
				}
				
			}
		}

		ImGui::End();
	}

};
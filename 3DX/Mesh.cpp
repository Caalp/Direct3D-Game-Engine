#include "Mesh.h"
#include "additional_headers.h"
#include "Imgui/imgui.h"
#include "ImguiHandler.h"
#include <iostream>

void  Mesh::ParseMesh(const aiMesh& mesh, const aiMaterial* const* pMaterials,std::string texIncludeDir)
{


	
	//vertices.resize(mesh.mNumVertices);
	
	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		Vertices vertices;
		vertices.pos.x = mesh.mVertices[i].x;
		vertices.pos.y = mesh.mVertices[i].y;
		vertices.pos.z = mesh.mVertices[i].z;

		//if (mesh.mNormals != NULL)
		//{
		//	vertices.normal.x = mesh.mNormals[i].x;
		//	vertices.normal.y = mesh.mNormals[i].y;
		//	vertices.normal.z = mesh.mNormals[i].z;
		//}
		
		if (mesh.mTextureCoords[0])
		{
			vertices.texCoordinates.x = mesh.mTextureCoords[0][i].x;
			vertices.texCoordinates.y =mesh.mTextureCoords[0][i].y;
			vertices.texCoordinates.z = mesh.mMaterialIndex;
			
		}
		else
		{
			vertices.texCoordinates = DirectX::XMFLOAT3(0.0f, 0.0f, mesh.mMaterialIndex);
		}
		vertices.weights.x = 0.0f;
		vertices.weights.y = 0.0f;
		vertices.weights.z = 0.0f;
		vertices.weights.w = 0.0f;
		
		vertices.boneIndices[0] = 0;
		vertices.boneIndices[1] = 0;
		vertices.boneIndices[2] = 0;
		vertices.boneIndices[3] = 0;

		m_vertices.push_back(vertices);
	}
	
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		aiFace face = mesh.mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}
	std::string pathEntry = texIncludeDir;
	aiString textureName;

	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_UNKNOWN))
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
		textureName.Clear();
	}

	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE))
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), textureName);
		textures.emplace_back(aiTextureType_DIFFUSE, pathEntry + textureName.C_Str());
		textureName.Clear();

	}

	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), textureName);
		textures.emplace_back(aiTextureType_SPECULAR, pathEntry + textureName.C_Str());
		textureName.Clear();
	}
	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_AMBIENT) > 0)
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), textureName);
		textures.emplace_back(aiTextureType_AMBIENT, pathEntry + textureName.C_Str());
		textureName.Clear();
	}
	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_HEIGHT) > 0)
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_HEIGHT, 0), textureName);
		textures.emplace_back(aiTextureType_HEIGHT, pathEntry + textureName.C_Str());
		textureName.Clear();
	}
	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NORMALS) > 0)
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), textureName);
		textures.emplace_back(aiTextureType_NORMALS, pathEntry + textureName.C_Str());
		textureName.Clear();
	}
	if (pMaterials[mesh.mMaterialIndex]->GetTextureCount(aiTextureType_NONE) > 0)
	{
		pMaterials[mesh.mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_NONE, 0), textureName);
		textures.emplace_back(aiTextureType_NONE, pathEntry + textureName.C_Str());
		textureName.Clear();
	}

	ImguiHandler& instance = ImguiHandler::GetInstance();
	if (instance.IsImguiEnabled())
	{
		static bool init = true;
		if (init)
		{
			ImguiHandler& imguiHandler = ImguiHandler::GetInstance();
			imguiHandler.BindCallback<Mesh, &Mesh::ImguiLoadTexture>(this);
			init = false;
		}

	}

}


void Mesh::ImguiLoadTexture()
{
	static std::vector<std::string> myItems;
	static bool init = true;
	if (init)
	{
		namespace fs = std::filesystem;
		std::string path = "../Models/player/";
		for (const auto& entry : fs::directory_iterator(path))
		{
			//std::string name(entry.path().c_str());
			//printf("%s\n",name);

			std::string filePath(entry.path().generic_u8string());
			myItems.push_back(filePath);
			std::cout << filePath << std::endl;
		}

		init = false;

	}
	static int item_current_idx = 0;                    // Here our selection data is an index.
	const char* combo_label = myItems[item_current_idx].c_str();  // Label to preview before opening the combo (technically it could be anything)
	ImGui::Begin("ComboBox");
	if (ImGui::BeginCombo("combo 1", combo_label))
	{
		for (int n = 0; n < myItems.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(myItems[n].c_str(), is_selected))
			{
				item_current_idx = n;
				std::cout << "You have selected: " << myItems[item_current_idx] << std::endl;
			}
				

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::End();


	//ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
	//ImGui::Image(, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);

}


void Mesh::InitDrawable(Graphics& gfx,const Technique& tech,std::string name,uint32_t id)
{
	db.SetName(derivedNodeName);
	db.SetID(id);
	InitBuffers(gfx);
	db.AppendTechnique(tech);
}

void Mesh::Submit(size_t channel)
{
	db.Submit(channel);
}

void Mesh::LinkTechnique(RenderGraph& fg)
{
	db.LinkTechnique(fg);
}

void Mesh::SetName(std::string name)
{
	derivedNodeName = name;
}

std::string Mesh::GetName() const
{
	return derivedNodeName;
}

void Mesh::InitBuffers(Graphics& gfx)
{
	db.indexBuffer = std::make_unique<IndexBuff>(gfx, indices);
	db.vertexBuffer = std::make_unique<VertexBuffer>(gfx, m_vertices);
	db.primitiveTopology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


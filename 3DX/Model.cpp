#include "Model.h"
#include "additional_headers.h"
#include "MatHelper.h"
#include <sstream>
#include "Texture.h"
#include "TextureLoader.h"

Model::Model(Graphics& gfx,const std::string & filename, unsigned int flags)
{
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(filename, flags);
	
	// check if loading fails 
	// might return 0 or scene data might be incomplete or might not have root node
	if (pScene == nullptr || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || pScene->mRootNode == nullptr)
	{
		return;
	}
	
	for (size_t i = 0; i < pScene->mNumMeshes; i++)
	{
		pMesh.push_back(ParseMesh(gfx, *pScene->mMeshes[i], pScene->mMaterials));
	}
		
	int nextId = 0;
	pRootNode = ParseNode(nextId, *pScene->mRootNode);
	
}

void Model::Draw(Graphics & gfx)
{
	pRootNode->Draw(gfx, DirectX::XMMatrixIdentity());
}



std::unique_ptr<Mesh> Model::ParseMesh(Graphics & gfx, const aiMesh& mesh, const aiMaterial * const * pMaterials)
{
	std::vector<std::unique_ptr<Bindables>> bindablePtrs;
	std::vector<V> vertices;
	std::vector<WORD> indices;
	std::vector<Texture> textures;
	TextureInfo txInfo;
	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		V vertex;
		vertex.pos.x = mesh.mVertices[i].x;
		vertex.pos.y = mesh.mVertices[i].y;
		vertex.pos.z = mesh.mVertices[i].z;
		vertex.normal.x = mesh.mNormals[i].x;
		vertex.normal.y = mesh.mNormals[i].y;
		vertex.normal.z = mesh.mNormals[i].z;
		if (mesh.mTextureCoords[0])
		{
			vertex.texCoordinates.x = mesh.mTextureCoords[0][i].x;
			vertex.texCoordinates.y = mesh.mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texCoordinates = DirectX::XMFLOAT2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		aiFace face = mesh.mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);

	}
	bool hasSpecularMap = false;
	float shininess = 32.0f;
	const unsigned int mIndex = mesh.mMaterialIndex;
	using namespace std::string_literals;
	const auto base = "Models\\nano_textured\\"s;
	
	//matIndex at least can be zero otherwise not found
	if (mIndex >= 0)
	{
		aiString texFileName;
		
		if (pMaterials[mIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texFileName) == aiReturn_SUCCESS)
		{
			TextureLoader th((base + texFileName.C_Str()).c_str());
			bindablePtrs.push_back(std::make_unique<Texture>(gfx, th));
		}
		if (pMaterials[mIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &texFileName) == aiReturn_SUCCESS)
		{

			TextureLoader th((base + texFileName.C_Str()).c_str());
			bindablePtrs.push_back(std::make_unique<Texture>(gfx, th));
			hasSpecularMap = true;
		}
		else
		{
			pMaterials[mIndex]->Get(AI_MATKEY_SHININESS, shininess);
				
		}
		 
		
		
		
		bindablePtrs.push_back(std::make_unique<SamplerState>(gfx));

	}
	
	
	
	
	bindablePtrs.push_back(std::make_unique<VertexBuffer>(gfx, vertices));
	if (hasSpecularMap)
	{
		bindablePtrs.push_back(std::make_unique<PixelShader>(gfx, L"SpecPhongPS.cso"));
	}
	else
	{
		bindablePtrs.push_back(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
	}
	
	auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
	auto vsBlob = vs->GetVBlob();
	bindablePtrs.push_back(std::move(vs));
	
	bindablePtrs.push_back(std::make_unique<IndexBuff>(gfx, indices));
	
	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	bindablePtrs.push_back(std::make_unique<InputLayout>(gfx, ied,vsBlob));
	struct MaterialConstantPS
	{

		DirectX::XMFLOAT4 amb;
		DirectX::XMFLOAT4 diff;
		DirectX::XMFLOAT4 spec;

	}matConst;

	matConst.amb = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	matConst.spec = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, shininess);

	bindablePtrs.push_back(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
	
	return std::make_unique<Mesh>(gfx, std::move(bindablePtrs));
			
}

std::unique_ptr<Node> Model::ParseNode(int & nextId, const aiNode & node)
{
	const auto transformation = DirectX::XMMatrixTranspose(
		DirectX::XMLoadFloat4x4(reinterpret_cast<const DirectX::XMFLOAT4X4*>(&node.mTransformation)));

	std::vector<Mesh*> curMeshPtrs;

	curMeshPtrs.reserve(node.mNumMeshes);
	for (size_t i = 0; i < node.mNumMeshes; i++)
	{
		const auto meshIdx = node.mMeshes[i];
		curMeshPtrs.push_back(pMesh.at(meshIdx).get());

	}

	auto pNode = std::make_unique<Node>(nextId++, node.mName.C_Str(), std::move(curMeshPtrs), transformation);
	for (size_t i = 0; i < node.mNumChildren; i++)
	{
		pNode->AddChild(ParseNode(nextId, *node.mChildren[i]));
	}
	return pNode;
}

Mesh::Mesh(Graphics & gfx, std::vector<std::unique_ptr<Bindables>> bindables)
{
	AddBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	for (auto& elem : bindables)
	{
		AddBind(std::move(elem));
	}
	AddBind(std::make_unique<TransformationBuffer>(gfx, *this));
}

void Mesh::Draw(Graphics & gfx, DirectX::FXMMATRIX acumTrans)
{
	DirectX::XMStoreFloat4x4(&transformation, acumTrans);
	Drawable::Draw(gfx);
}

void Mesh::Update(float dt)
{
}

DirectX::XMMATRIX Mesh::GetTransformation() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(pos.x,pos.y,pos.z);
}

Node::Node(int id, const std::string& name, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX & transform) :
	id(id),
	meshPtrs(std::move(meshPtrs)),
	name(name)
{
	DirectX::XMStoreFloat4x4(&transformation, transform);
	DirectX::XMStoreFloat4x4(&appliedTransform, DirectX::XMMatrixIdentity());

}

void Node::Draw(Graphics & gfx, DirectX::FXMMATRIX acumTrans)
{
	const auto built = DirectX::XMLoadFloat4x4(&appliedTransform) * DirectX::XMLoadFloat4x4(&transformation) * acumTrans;
	for (const auto pm : meshPtrs)
	{
		pm->Draw(gfx, built);
	}
	for (const auto& pc : childPtrs)
	{
		pc->Draw(gfx, built);
	}
}

void Node::AddChild(std::unique_ptr<Node> pChild)
{
	childPtrs.push_back(std::move(pChild));
}

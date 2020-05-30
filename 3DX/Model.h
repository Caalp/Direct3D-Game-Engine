//#pragma once
//#include "additional_headers.h"
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include "assimp/scene.h"
//#include <string>
//#include <vector>
//#include "Drawable.h"
//
//
//struct V
//{
//	DirectX::XMFLOAT3 pos;
//	DirectX::XMFLOAT3 normal;
//	DirectX::XMFLOAT2 texCoordinates;
//};
//struct Texture2
//{
//	unsigned int id;
//	std::string type;
//	std::string path;
//};
//
//class Mesh : public Drawable
//{
//public:
//	
//	Mesh(Graphics& gfx,std::vector<std::unique_ptr<Bindable>> Bindable);
//	void Draw(Graphics& gfx,DirectX::FXMMATRIX acumTrans);
//	void Update(float dt) override;
//	DirectX::XMMATRIX GetTransformation() const override;
//
//private:
//	mutable DirectX::XMFLOAT4X4 transformation;
//	float pitch;
//	float yaw;
//	float roll;
//	DirectX::XMFLOAT3 pos;
//};
//class Node
//{
//	friend class Model;
//public:
//	Node(int id, const std::string& name,std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform);
//	void Draw(Graphics& gfx, DirectX::FXMMATRIX acumTrans);
//	void AddChild(std::unique_ptr<Node> pChild);
//
//private:
//	int id;
//	std::string name;
//	DirectX::XMFLOAT4X4 transformation;
//	DirectX::XMFLOAT4X4 appliedTransform;
//	std::vector<std::unique_ptr<Node>> childPtrs;
//	std::vector<Mesh*> meshPtrs;
//};
//class Model 
//{
//
//	
//public:
//	
//	Model(Graphics& gfx,const std::string& filename, unsigned int flags = aiProcess_Triangulate | aiProcess_MakeLeftHanded);
//	void Draw(Graphics& gfx);
//	/*virtual void SetScene(std::unique_ptr<aiScene>& scene) = 0;;
//	virtual const aiScene* & GetScene() const;*/
//	
//
//private:
//	std::unique_ptr<Mesh> ParseMesh(Graphics& gfx, const aiMesh& mesh, const aiMaterial* const* pMaterials);
//	std::unique_ptr<Node> ParseNode(int& nextId, const aiNode& node);
//private:
//	std::unique_ptr<Node> pRootNode;
//	std::vector<std::unique_ptr<Mesh>> pMesh;
//
//	
//	
//};

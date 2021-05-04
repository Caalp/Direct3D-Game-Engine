//#pragma once
//#include <string>
//#include <vector>
//#include <map>
//#include "assimp/Importer.hpp"
//#include "assimp/postprocess.h"
//#include "assimp/scene.h"
//#include "Drawable.h"
//#include "DynamicVertex.h"
//
//class Graphics;
//class Technique;
//class RenderGraph;
//class Drawable;
//
////struct TextureData
////{
////	//unsigned int id;
////	TextureData(uint8_t t, std::string p) :type(t), path(p) {}
////	uint8_t type;
////	std::string path;
////};
//struct BoneVertexWeightInfo
//{
//	uint32_t boneVertexID; //vertexid where bone has affect on
//	float boneVertexWeight;
//};
//struct BoneData
//{
//
//	DirectX::XMMATRIX offsetMatrix; // Transforms mesh space to bone space
//	DirectX::XMMATRIX finalTransform;
//};
//
//class Mesh : public Drawable
//{
//public:
//	Mesh() = default;
//	void ParseMesh(const aiMesh& mesh, const aiMaterial* const* pMaterials, std::string texIncludeDir);
//
//public:
//	//std::vector<TextureData> textures;
//
//};
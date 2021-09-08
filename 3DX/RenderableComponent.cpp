//#include "RenderableComponent.h"
//
//#include "Imgui/imgui.h"
//#include <shobjidl.h> 
//#include <sstream>
//#include "json/json.hpp"
//#include <fstream>
//#include <vector>
//
//#include "SamplerState.h"
//#include "VertexShader.h"
//#include "Texture.h"
//#include "PixelShader.h"
//#include "InputLayout.h"
//#include "Channels.h"
////
////RenderableComponent::RenderableComponent(RenderableComponent&& rhs)
////{
////	std::cout << "moveee" << std::endl;
////	this->vertexBuffer = std::move(rhs.vertexBuffer);
////	this->primitiveTopology = std::move(rhs.primitiveTopology);
////	this->indexBuffer = std::move(rhs.indexBuffer);
////	this->m_TBuffer = std::move(rhs.m_TBuffer);
////	this->techniques = std::move(rhs.techniques);
////}
//
//void RenderableComponent::SetVertexBuffer(std::unique_ptr<VertexBuffer> vb)
//{
//	vertexBuffer = std::move(vb);
//}
//
//void RenderableComponent::SetTopology(std::unique_ptr<PrimitiveTopology> pt)
//{
//	primitiveTopology = std::move(pt);
//}
//
//void RenderableComponent::SetIndexBuffer(std::unique_ptr<IndexBuff> ib)
//{
//	indexBuffer = std::move(ib);
//
//}
//
//U32 RenderableComponent::IndexCount() const
//{
//	return indexBuffer->GetIndexCount();
//}
//
//void RenderableComponent::AppendTechnique(const Technique& tech)
//{
//	for (const auto& tec : techniques)
//	{
//		if (tec.GetName() == tech.GetName())
//		{
//			return;
//		}
//	}
//
//
//	techniques.push_back(tech);
//}
//
//void RenderableComponent::Bind() const
//{
//	//vertexBuffer->Bind();
//	//primitiveTopology->Bind();
//	//indexBuffer->Bind();
//	//if (auto pref = m_TBuffer.lock())
//	//{
//
//	//	pref->Bind(0u,1u);
//	//}
//	//for (auto s : techniques[0].steps)
//	//{
//	//	s.Bind();
//	//	s.Draw();
//	//}
//}
//
//RenderableComponent RenderableComponent::Load(const char* filepath)
//{
//	std::ifstream in(filepath);
//	if (in.is_open())
//	{
//		json tempJson;
//		in >> tempJson;
//
//		// Add check here if it is actually renderable
//
//		std::string targetRG = tempJson["RenderGraph"].get<std::string>();
//		std::string targetPass = tempJson["TargetPass"].get<std::string>();
//		std::string stepName = tempJson["StepName"].get<std::string>();
//
//
//		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//		{
//			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
//			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
//		};
//		std::string vsName = tempJson["VertexShader"].get<std::string>();
//		std::string psName = tempJson["PixelShader"].get<std::string>();
//		 // Sampler state here
//		std::string drawFunc = tempJson["DrawFunction"].get<std::string>();
//
//		// Create technique
//		Technique boxDefault("TestGraph", "boxDefault", channel1::defaultChannel, true);
//		{
//			{
//
//				Step s1{ stepName };
//
//
//				s1.AddBind(std::make_shared<PixelShader>(psName));
//				auto vs = std::make_shared<VertexShader>(vsName);
//				auto vsBlob = vs->GetVBlob();
//				s1.AddBind(std::move(vs));
//				const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
//				{
//					{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
//					{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
//				};
//
//				s1.AddBind(std::make_shared<InputLayout>(ied, vsBlob));
//
//
//
//
//				s1.AddBind(std::make_shared<SamplerState>());
//				s1.AddBind(std::make_shared<Texture>("../Textures/WoodCrate01.dds"));
//
//				//s1.AddBind(std::make_shared<DrawIndexed>(0, render.IndexCount()));
//				//s1.AddBind(std::make_shared<TransformationBuffer>();
//
//				boxDefault.AddStep(s1);
//			}
//
//		}
//		return RenderableComponent();
//	}
//}
//
//void RenderableComponent::DrawImgui()
//{
//	//PWSTR pszFilePath = nullptr;
//	//std::wstringstream ss;
//	if (ImGui::BeginTabItem("RenderableComponent"))
//	{
//	//	if (ImGui::Button("Open"))
//	//	{
//	//		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
//	//			COINIT_DISABLE_OLE1DDE);
//	//		if (SUCCEEDED(hr))
//	//		{
//	//			IFileOpenDialog* pFileOpen;
//
//	//			// Create the FileOpenDialog object.
//	//			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
//	//				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
//
//	//			if (SUCCEEDED(hr))
//	//			{
//	//				// Show the Open dialog box.
//	//				hr = pFileOpen->Show(NULL);
//
//	//				// Get the file name from the dialog box.
//	//				if (SUCCEEDED(hr))
//	//				{
//	//					IShellItem* pItem;
//	//					hr = pFileOpen->GetResult(&pItem);
//	//					if (SUCCEEDED(hr))
//	//					{
//	//						
//	//						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//
//	//						// Display the file name to the user.
//	//						if (SUCCEEDED(hr))
//	//						{
//	//							//s << pszFilePath;
//	//							// If successfull read json file
//	//							using json = nlohmann::json;
//
//	//							std::ifstream in(pszFilePath);
//	//							if (in.is_open())
//	//							{
//	//								json test;
//	//								in >> test;
//	//								std::cout << test["RenderGraph"].get<std::string>() << std::endl;
//	//								std::cout << test["TargetPass"].get<std::string>() << std::endl;
//	//								std::cout << test["StepName"].get<std::string>() << std::endl;
//	//								std::cout << test["InputLayout"][0] << std::endl;
//	//								std::cout << test["InputLayout"][1] << std::endl;
//	//								std::cout << test["VertexShader"].get<std::string>() << std::endl;
//	//								std::cout << test["PixelShader"].get<std::string>() << std::endl;
//	//								std::cout << test["SamplerState"].get<std::string>() << std::endl;
//	//								std::cout << test["DrawFunction"].get<std::string>() << std::endl;
//	//							}
//	//							
//	//							
//	//							CoTaskMemFree(pszFilePath);
//	//						}
//	//						pItem->Release();
//	//					}
//	//				}
//	//				pFileOpen->Release();
//	//			}
//	//			CoUninitialize();
//	//		}
//	//	}
//	//	ImGui::Text("RenderGraph:"); ImGui::SameLine(); ImGui::Text(techniques[0].m_TargetGraphName.c_str());
//	////ImGui::Text("TargetPass: ");  ImGui::SameLine(); ImGui::Text(techniques[0]..c_str());
//	//ImGui::Text("StepName: ");
//	//ImGui::Text("Primitive Topology: "); //ImGui::SameLine();
//	//ImGui::Text("VertexShader: ");
//	//ImGui::Text("PixelShader: ");
//	//ImGui::Text("DrawFunction: ");
//	//ImGui::Text("SamplerState: ");
//
//		ImGui::EndTabItem();
//	}
//}
//

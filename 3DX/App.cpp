#include "App.h"
#include <random>
#include <chrono>
#include "StaticTimer.h"
#include "json/json.hpp"
#include <fstream>
//#include "ModelResource.h"
#include "ResourceManager.h"
#include "CommandBucket.h"
//#include "TestShape.h"
#include "buckets.h"
#include "Loader.h"
//TestShape testShape;
#include "HandleAlloc.h"

#include "TextureDB.h"
App::App() :
	skyBox("SkyBox", 500, 30, 30),
	m_imguiInstance(ImguiHandler::GetInstance())
	//wnd(1600, 900, "Hello"),
	//m_SceneLoader(SceneLoader::GetSingleton()),
	//imguiHandler(ImguiHandler::GetInstance())
{



	//FixedHandleAlloc<10> m_handleAlloc;
	//ShaderHandle handle;
	//handle = { m_handleAlloc.Alloc() };


	FixedHandleAlloc<10> m_handleAlloc;

	ShaderHandle handle[5];
	for (int i = 0; i < 5; i++)
	{
		handle[i] = { m_handleAlloc.Alloc() };
	}

	bool vv = m_handleAlloc.IsValid(handle[5].idx);
	bool vv1 = m_handleAlloc.IsValid(handle[2].idx);
	m_handleAlloc.Free(handle[3].idx);
	bool vv2 = m_handleAlloc.IsValid(3);
	ShaderHandle myHandle = { m_handleAlloc.Alloc() };
	m_handleAlloc.print();

	backend::InitInfo init;
	init.height = 900u;
	init.width =1600u;
	init.vsync = 1;
	init.windowName = "Test";
	init.renderer = backend::D3D11;

	backend::Init(init);
	backend::CreateViewport(1600.0f,900.0f,1.0f,0.0f,0.0f,0.0f);
	//bucket::testBucket.Init();
	
	//m_depth = backend::CreateDepthBuffer();
	//backend::m_renderer->BindRenderTarget({});
	
	Loader::GetInstance()->AddList(&TextureDB::Init, &TextureDB::Shutdown);
	Loader::GetInstance()->Init();
	
	m_mainCamera.Init();

	testShape_1.Init(TextureDB::GetInstance()->GetHandleToTexture(L"WoodCrate01.dds"), {0.0f,0.0f,0.0f});
	testShape_2.Init(TextureDB::GetInstance()->GetHandleToTexture(L"WireFence.dds"), { 3.0f,0.0f,0.0f });
	skyBox.Init();



	//TextureHandle testHandle = TextureDB::GetInstance()->GetHandleToTexture(L"checkboard.dds");
	//ResourceManager& rm = ResourceManager::GetSingleton();
	//MeshResource* r1 = rm.CreateResource("boblamb",ResourceManager::TypeMeshResource)->get<MeshResource*>();
	//r1->Load("../Models/boblamp/boblampclean.md5mesh");
	//ResourceManager* mr = static_cast<ResourceManager*>(r1);

	//ModelResource* newModel = new ModelResource("../Models/boblamp/boblampclean.md5mesh");
	
	//using json = nlohmann::json;

	//std::ifstream in("../jsons/default_technique.json");
	//json test;
	//in >> test;

	//std::cout << test["InputLayout"][0][1].get<UINT>() << std::endl;
	//json j;
	//j["pi"] = 3.141;
	//j["answer"]["everyting"] = 42;

	//json j2 = "{ \"happy\": true, \"pi\": 3.141 }"_json;

	//std::cout << j2.dump(4) << std::endl;

	//m_SceneLoader->GetSingleton()->CreateRootScene();
	
	//TestRenderGraph trg = { wnd.gfx(), "TestGraph" };
	//m_RenderSystem.AddGraph();
	//Renderer::AddGraph(std::make_shared<TestRenderGraph>(wnd.gfx(), "TestGraph"));

	/* Test ImguiHandler callback functionality here for now*/
	//imguiHandler.BindCallback<App, &App::ImguiStatistic>(this);



	//int i = 0;
	//Scene* model = new Scene(new Entity,"TestBoxes");
	//
	//for (auto& e : testBox)
	//{
	//	//e = new TestBox(wnd.gfx())
	//	Scene* ss = new Scene(new TestBox(wnd.gfx()), "TestBox");
	//	
	//	ss->GetEntity()->GetComponent<TransformComponent>().SetTranslation({ dis(gen),dis(gen),dis(gen) });
	//	model->AddChild(ss);

	//	i++;
	//}
	//SceneLoader::GetRootScene()->AddChild(model);
	
	//m_RenderSystem.LinkTechniques();
	//Renderer::LinkTechniques();

	//Deletion attemp on object allocated on stack (for bug producing purpose)
	//Mesh red;
	//delete Renderer::GetRenderer();
	//Renderer::
}

App::~App()
{
	
}

int App::Go()
{
	auto ss = sizeof(command::DrawIndexed);
	
	timer.StartTimer();
	while (true)
	{
		if (const auto error_code = Window::ProcessMessages())
		{
			return *error_code;
		}
		timer.StopTimer();
		float b = timer.GetTime();
		float a = timer.GetTime() / 1000;

		//wnd.gfx().BeginFrame();
		// Enable dockspace before everything get processed
		
		backend::BeginFrame();
		//m_imguiInstance.EnableDockspace();
		
		Update(a);

		//imguiHandler.ProcessImguiCalls();
		
		
		//wnd.gfx().EndFrame();
		backend::EndFrame();
		

	}
	backend::ShutDown();
}
//void App::ImguiStatistic()
//{
//	ImGui::Begin("Info");
//
//	ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
//	ImGui::Text("FPS: (%.1f FPS)",ImGui::GetIO().Framerate);
//
//	ImGui::End();
//
//
//
//}

void App::Update(float dt)
{
	// A nice color
	//float color[] = { 1.0f,0.5f,0.2f,1.0f };

	m_mainCamera.DrawImgui();
	m_mainCamera.UpdateAndBindCameraBuffer();

	testShape_1.Update(dt);
	testShape_2.Update(dt);

	bucket::testBucket.Submit();
	//	CommandPacket cmd_pack;
//	for (auto cmd : buckets::testCommandBucket->mCommands)
//	{
//		cmd_pack = cmd.second;
//		do
//		{
//			SubmitCommand(cmd_pack);
//			cmd_pack = commandpacket::GetNextCommandPacket(cmd_pack);
//		} while (cmd_pack != nullptr);
//
//	}
	
	//Renderer::SubmitObjects();
	
	//m_RenderSystem.SubmitObjects();
	
	
	/*--------------------------------------------------------------------------------------------------*/

	// Takes around 7 ms with 10,000 boxes
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	/*std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] --" << 
		std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[mics]" <<std::endl;*/


	
	//begin = std::chrono::steady_clock::now();

	/* To Do : If object is released may leave dangling pointers */
	//m_RenderSystem.Execute(wnd.gfx());
	//Renderer::Render(wnd.gfx());
	//end = std::chrono::steady_clock::now();
	/*std::cout << "Rendering Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] --" <<
		std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[mics]" << std::endl;*/

	/*---------------------------- Do ImGui drawing business here --------------------------------------*/
	// Do ImGui drawing business here 
	//m_SceneLoader->GetSingleton()->GetRootScene()->DrawImgui();
	

	/*--------------------------------------------------------------------------------------------------*/
	//static bool demoWnd = false;
	//ImGui::ShowDemoWindow(&demoWnd);

	
	//m_RenderSystem.Reset();
	//Renderer::Reset();
	
}

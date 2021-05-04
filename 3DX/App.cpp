#include "App.h"
#include "Box.h"
#include <random>
#include "Channels.h"
#include <Xinput.h>
#include <sstream>
#include "Events.h"
#include "StaticTimer.h"
#include <fstream>
#include "Imgui/imgui.h"
#include "ImguiUtils.h"
#include "DynamicVertex.h"
#include <memory>
#include "Scene.h"
#include <chrono>
#include "CommandBucket.h"
#include "json/json.h"

App::App() :
	wnd(1600, 900, "Hello"),last_x(0),last_y(0),
	m_RenderSystem(RenderSystem::GetSingleton()),
	m_CameraSystem(CameraSystem::GetSigleton()),
	cam1("main","MainCamera"),
	cam2("main","Cam2"),
	mPhi(1.5f*3.1415926535f),mTheta(1.5f*3.1415926535f),mRadius(80.0f), imguiHandler(ImguiHandler::GetInstance())
	
{

	/*std::ifstream ifs("../jsons/test.json");
	if (!ifs.is_open())
	{
		std::cout << "Failed to open file!" << std::endl;
	}
	Json::Value root;


	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		
	}
	std::cout << root["Anna"]["age"].asInt() << std::endl;*/
	//Json::Value obj;
	//reader.parse(ifs);


	m_RenderSystem.AddGraph(std::make_shared<TestRenderGraph>(wnd.gfx(), cam1, "TestGraph"));

	CameraComponent data;
	data.m_Name = "MainCamera";
	data.m_CamType = CAM_PERSPECTIVE;
	data.m_CamPos = { 0.0f,0.0f,-30.0f };
	data.m_CamRight = { 1.0f,0.0f,0.0f };
	data.m_CamUp = {0.0f,1.0f,0.0f};
	data.m_CamLook = { 0.0f,0.0f,1.0f };
	data.SetCameraLens(0.25f * 3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);

	cam1.AddComponent<CameraComponent>(std::move(data));
	cam1.AddComponent<MainCamera>();

	data.m_Name = "Cam2";
	data.m_CamType = CAM_PERSPECTIVE;
	data.m_CamPos = { -30.0f,0.0f,0.0f };
	data.m_CamRight = { 0.0f,0.0f,-1.0f };
	data.m_CamUp = { 0.0f,1.0f,0.0f };
	data.m_CamLook = { 1.0f,0.0f,0.0f };
	cam2.AddComponent<CameraComponent>(std::move(data));
	

	//cam.SetCamType(Camera::CameraType::CAM_PERSPECTIVE);
	//cam.SetCameraLens(0.25f*3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);

	imguiHandler.BindCallback<App, &App::ImguiStatistic>(this);

	
	dvbuff::VertexLayout test;
	test.Add<dvbuff::Position3D>();
	//test.Add<dvbuff::Position2D>();
	//test.Add<dvbuff::TextureCoord>();

	dvbuff::VertexBuffer vbuff(test);
	
	

	//vbuff.Insert<dvbuff::Position2D>(0,DirectX::XMFLOAT2(3.0f, 4.0f));

	
	vbuff.PushBack<dvbuff::Position3D>(DirectX::XMFLOAT3(1.0f,2.0f,6.0f));
	vbuff.PushBack<dvbuff::Position3D>(DirectX::XMFLOAT3(2.0f,2.0f,6.0f));
	vbuff.PushBack<dvbuff::Position3D>(DirectX::XMFLOAT3(3.0f,2.0f,6.0f));
	vbuff.PushBack<dvbuff::Position3D>(DirectX::XMFLOAT3(4.0f,2.0f,6.0f));
	vbuff.PushBack<dvbuff::Position3D>(DirectX::XMFLOAT3(5.0f,2.0f,6.0f));
	//vbuff.PushBack<dvbuff::Position2D>(DirectX::XMFLOAT2(3.0f, 4.0f));

	auto dataTest = vbuff.Data();
	auto testOp = vbuff[0].Get<dvbuff::Position3D>();
	vbuff[0][0] = DirectX::XMFLOAT3(11.0f, 2.0f, 6.0f);
	vbuff[1][2] = DirectX::XMFLOAT3(12.0f, 2.0f, 6.0f);
	auto testOp2 = vbuff[0].Get<dvbuff::Position3D>();
	auto testOp3 = vbuff[1].Get<dvbuff::Position3D>();
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 10.0f);
	testBox.resize(100);
	// Init testBoxes here
	
	int i = 0;
	for (auto& e : testBox)
	{
		e = new TestBox{ wnd.gfx(),"main"};
		e->GetComponent<TransformationComponent>().translation = { dis(gen),dis(gen),dis(gen) };
		i++;
	}

	m_RenderSystem.LinkTechniques();

	

}

App::~App()
{
	
	for (auto& e : testBox)
	{

		delete e;
	}
}

int App::Go()
{
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

		wnd.gfx().BeginFrame();
		// Enable dockspace before everything get processed
		imguiHandler.EnableDockspace();
		Update(a);

		imguiHandler.ProcessImguiCalls();
		
		
		wnd.gfx().EndFrame();
		
		

	}
}
void App::ImguiStatistic()
{
	ImGui::Begin("Info");

	ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("FPS: (%.1f FPS)",ImGui::GetIO().Framerate);

	ImGui::End();



}

void App::Update(float dt)
{


	ImguiUtils::DrawMatrix();
	static float alpha = dt*10.0f;
	if (alpha < 1.0f)
	{
		alpha -= dt;
	}
	


	static float v = 30.0f;
	float dtheta = 0.2f;


	
	m_RenderSystem.SubmitObjects();
	m_CameraSystem.DrawImgui();
	/*cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());*/
	m_CameraSystem.UpdateViewXM(dt);

	Scene* s = Scene::CreateScene("main");
	s->PrintEnttities();
	/*spotLight.Update();
	pointLight.Update();
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());*/
		
	//if (wnd.kbd.KeyIsPressed('W'))
	//{
	//	//printf("W pressed\n");
	//	cam.Walk(v*dt);
	//}
	//if (wnd.kbd.KeyIsPressed('S'))
	//{
	//	cam.Walk(v*-dt);
	//}
	//if (wnd.kbd.KeyIsPressed('A'))
	//{
	//	cam.Strafe(v*-dt);
	//}
	//if (wnd.kbd.KeyIsPressed('D'))
	//{
	//	cam.Strafe(v*dt);
	//}


	//
	//if (wnd.mouse.IsInWindow())
	//{
	//	//NOTE: Left mouse button and imgui in intereacting fix!!!
	//	if (wnd.mouse.IsInWindow() && wnd.mouse.RightIsPressed())
	//	{

	//		float dx = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosX() - last_x));
	//		float dy = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosY() - last_y));

	//		cam.Pitch(dy);
	//		cam.Yaw(dx);
	//	}
	//	last_x = (float)wnd.mouse.GetPosX();
	//	last_y = (float)wnd.mouse.GetPosY();

	//}
/*
	//chr.GetFinalTransforms("defaultAnim_0", animTimer);
	//chr.GetFinalTransforms("Spider_Armature|Attack", animTimer);
	//chr.GetFinalTransforms("Walk", 0.5f);
	//chr.GetFinalTransforms("Salute", animTimer);
	//chr.GetFinalTransforms("Aim", 0.9f);
	//chr.GetFinalTransforms("Human Armature|Jump", 0.0f);
	
	
	//chr.GetFinalTransforms("Run", animTimer);
	//chr.GetFinalTransforms("mixamo.com", 0.05f);
	//chr.GetFinalTransforms("defaultAnim_0", dt);
	//chr.Update(wnd.gfx());
	//chr.UpdateXM();
	
	
	//spotLight.Submit(channel1::defaultChannel);
	//pointLight.Submit(channel1::defaultChannel);
	//
	////chr.Submit(channel1::defaultChannel);
	//box0.Submit(channel1::defaultChannel);
	////floor.Submit(channel1::defaultChannel);
	////mirror.Submit(channel1::defaultChannel);
	//sky.Submit(channel1::defaultChannel);
	//centerSphere.Submit(channel1::defaultChannel);

	////spotLight.Submit(channel1::dynamicCubeMap);
	////pointLight.Submit(channel1::dynamicCubeMap);
	//box0.Submit(channel1::dynamicCubeMap);
	//floor.Submit(channel1::dynamicCubeMap);
	//mirror.Submit(channel1::dynamicCubeMap);
	//sky.Submit(channel1::dynamicCubeMap);
	//emgr->ProcessEvents();
	//testScene.UpdateTest(alpha);
	//testCube.Submit(channel1::defaultChannel); // only submitting this w/o linking technique causing vector error!!!

	m_RenderSystem.SubmitObjects();

	
	//if (ImGui::BeginMainMenuBar())
	//{
	//	
	//	if (ImGui::MenuItem("Screenshot"))
	//	{
	//		//rgTest.SaveBufferToFile(wnd.gfx(), "imgui_ss_Demo", "offScreenRT");
	//		printf("Screenshot Clicked!\n");

	//	}
	//	ImGui::EndMainMenuBar();
	//}
	*/
	/*--------------------------------------------------------------------------------------------------*/

	// Takes around 7 ms with 10,000 boxes
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	ts.Update(wnd.gfx(), 0.5f);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	/*std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] --" << 
		std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[mics]" <<std::endl;*/


	
	begin = std::chrono::steady_clock::now();
	m_RenderSystem.Execute(wnd.gfx());
	end = std::chrono::steady_clock::now();
	/*std::cout << "Rendering Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms] --" <<
		std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[mics]" << std::endl;*/

	/*--------------------------------------------------------------------------------------------------*/
	static bool demoWnd = false;
	ImGui::ShowDemoWindow(&demoWnd);


	m_RenderSystem.Reset();

	
	
}

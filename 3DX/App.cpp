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

App::App() 
	: wnd(800, 600, "Hello")
	, last_x(0)
	, last_y(0)
	, dirLight(wnd.gfx())
	, pointLight(wnd.gfx())
	, mPhi(1.5f * 3.1415926535f)
	, mTheta(1.5f * 3.1415926535f)
	, mRadius(80.0f)
{
	cam.SetCameraLens(0.25f * 3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);
	spotLight.LinkTechnique(rg);
	pointLight.LinkTechnique(rg);
	chr.LinkTechnique(rg);
	box0.LinkTechnique(rg);
	//testCube.LinkTechnique(rg);
	floor.LinkTechnique(rg);
	box0.LinkTechnique(rgMirror);
	mirror.LinkTechnique(rgMirror);
	sky.LinkTechnique(rg);
}

App::~App()
{}

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
		Update(a);
		wnd.gfx().EndFrame();
	}
}

void App::Update(float dt)
{
	ImGui::Begin("Info");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / (1 / dt), 1 / dt);
	ImGui::End();

	ImGui::Begin("AnimSpeed");
	ImGui::SliderFloat("dt", &animTimer, 0.0f, 2.0f, "%.5f", 2.0f);
	ImGui::End();
	// Xinput experiment code here
	static float alpha = dt * 10.0f;
	if (alpha < 1.0f)
	{
		alpha -= dt;
	}
	//DWORD dwResult;
	//XINPUT_STATE state{0};
	//dwResult = XInputGetState(0, &state); // if 0 then connected
	//float LX = state.Gamepad.sThumbLX;
	//float LY = state.Gamepad.sThumbLY;
	//float magnitude = sqrt(LX * LX + LY * LY);

	//float normalizedLX = LX / magnitude;
	//float normalizedLY = LY / magnitude;
	//std::ostringstream ss;
	//ss << normalizedLX << " " << normalizedLY<<std::endl;
	//std::string s(ss.str());
	//OutputDebugString(s.c_str());
	//XINPUT_VIBRATION vibration{0};
	//vibration.wLeftMotorSpeed = 65000;
	//XInputSetState(0, &vibration);

	static float v = 30.0f;
	float dtheta = 0.2f;

	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());
	spotLight.Update();
	pointLight.Update();
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());

	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Walk(v * dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Walk(v * -dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Strafe(v * -dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Strafe(v * dt);
	}
	if (wnd.mouse.IsInWindow())
	{
		//NOTE: Left mouse button and imgui in intereacting fix!!!
		if (wnd.mouse.IsInWindow() && wnd.mouse.RightIsPressed())
		{
			float dx = DirectX::XMConvertToRadians(0.25f * static_cast<float>(wnd.mouse.GetPosX() - last_x));
			float dy = DirectX::XMConvertToRadians(0.25f * static_cast<float>(wnd.mouse.GetPosY() - last_y));
			cam.Pitch(dy);
			cam.Yaw(dx);
		}
		last_x = (float)wnd.mouse.GetPosX();
		last_y = (float)wnd.mouse.GetPosY();
	}
	chr.GetFinalTransforms("defaultAnim_0", animTimer);
	//chr.GetFinalTransforms("Spider_Armature|Attack", animTimer);
	//chr.GetFinalTransforms("Walk", 0.5f);
	//chr.GetFinalTransforms("Salute", animTimer);
	//chr.GetFinalTransforms("Aim", 0.9f);
	//chr.GetFinalTransforms("Human Armature|Jump", 0.0f);
	//chr.GetFinalTransforms("Run", animTimer);
	//chr.GetFinalTransforms("mixamo.com", 0.05f);
	//chr.GetFinalTransforms("defaultAnim_0", dt);
	chr.Update(wnd.gfx());
	//chr.UpdateXM();

	spotLight.Submit(channel1::defaultChannel);
	pointLight.Submit(channel1::defaultChannel);

	chr.Submit(channel1::defaultChannel);
	box0.Submit(channel1::defaultChannel);
	floor.Submit(channel1::defaultChannel);
	mirror.Submit(channel1::defaultChannel);
	sky.Submit(channel1::defaultChannel);
	//emgr->ProcessEvents();
	//testScene.UpdateTest(alpha);
	//testCube.Submit(channel1::defaultChannel); // only submitting this w/o linking technique causing vector error!!!
	rg.Execute(wnd.gfx());
	rgMirror.Execute(wnd.gfx());

	rg.Reset();
	rgMirror.Reset();
}
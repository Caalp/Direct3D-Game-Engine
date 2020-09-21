#include "App.h"
#include "Box.h"
#include <random>
#include "Channels.h"
#include <Xinput.h>
#include <sstream>
#include "Events.h"
#include "StaticTimer.h"

App::App() :
	wnd(800, 600, "Hello") ,x(0.5f),y(-4.5f),z(0.0f),last_x(0),last_y(0),
	//(wnd.gfx()),
	dirLight(wnd.gfx()),spotLight(wnd.gfx()),
	pointLight(wnd.gfx()),
	mPhi(1.5f*3.1415926535f),mTheta(1.5f*3.1415926535f),mRadius(80.0f)//m(wnd.gfx(),"suzanne.obj")
	
{
	
	cam.SetCameraLens(0.25f*3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);

	

	
	spotLight.LinkTechnique(rg);
	box0.LinkTechnique(rg);
	//testCube.LinkTechnique(rg);
	floor.LinkTechnique(rg);
	box0.LinkTechnique(rgMirror);
	mirror.LinkTechnique(rgMirror);
	sky.LinkTechnique(rg);
}

App::~App()
{
	

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
		float a = timer.GetTime() / 1000;
		
		Update(a);


	}
}

void App::Update(float dt)
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	// Xinput experiment code here
	static float alpha = dt*10.0f;
	if (alpha < 1.0f)
	{
		alpha -= dt;
	}
	
	
	//DWORD dwResult;
	//XINPUT_STATE state{0};
	//dwResult = XInputGetState(0, &state); // if 0 then connected

	//float LX = state.Gamepad.sThumbLX;
	//float LY = state.Gamepad.sThumbLY;
	//
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
	

	static float v = 70.0f;
	float dtheta = 0.2f;
	/*dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());*/
	
	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());

	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
		
	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Walk(v*dt);
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		cam.Walk(v*-dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		cam.Strafe(v*-dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Strafe(v*dt);
	}


	
	if (wnd.mouse.IsInWindow())
	{

		if (wnd.mouse.IsInWindow() && wnd.mouse.LeftIsPressed())
		{

			float dx = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosX() - last_x));
			float dy = DirectX::XMConvertToRadians(0.25f*static_cast<float>(wnd.mouse.GetPosY() - last_y));

			cam.Pitch(dy);
			cam.Yaw(dx);
		}
		last_x = (float)wnd.mouse.GetPosX();
		last_y = (float)wnd.mouse.GetPosY();

	}

	
	


	spotLight.DrawLightImgui();
	
	spotLight.Submit(channel1::defaultChannel);
	box0.Submit(channel1::defaultChannel);
	floor.Submit(channel1::defaultChannel);
	mirror.Submit(channel1::defaultChannel);
	sky.Submit(channel1::defaultChannel);
	emgr->ProcessEvents();
	//testScene.UpdateTest(alpha);
	//testCube.Submit(channel1::defaultChannel); // only submitting this w/o linking technique causing vector error!!!
	
	
	
	
	rg.Execute(wnd.gfx());
	rgMirror.Execute(wnd.gfx());
	
	//static bool show_demo_window = false;

	
	wnd.gfx().EndFrame();
	rg.Reset();
	rgMirror.Reset();
}

#include "App.h"
#include "Box.h"
#include <random>
#include "Channels.h"
App::App() :
	wnd(800, 600, "Hello") ,x(0.5f),y(-4.5f),z(0.0f),last_x(0),last_y(0),
	//(wnd.gfx()),
	dirLight(wnd.gfx()),spotLight(wnd.gfx()),
	pointLight(wnd.gfx()),
	mPhi(1.5f*3.1415926535f),mTheta(1.5f*3.1415926535f),mRadius(80.0f)//m(wnd.gfx(),"suzanne.obj")
	
{
	
	cam.SetCameraLens(0.25f*3.1415926535f, 800.0f / 600.0f, 1.0f, 1000.0f);

	//d1 = new Box(wnd.gfx(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 1.0f);
	
	vb.resize(100);
	
	//box0.LinkBucket(&bucket0);
	box0.LinkTechnique(rg);
}

App::~App()
{
	
	for (auto& elem : vb)
	{
		delete elem;
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
		float a = timer.GetTime() / 1000;
		Update(a);


	}
}

void App::Update(float dt)
{
	static float v = 70.0f;
	float dtheta = 0.2f;
	
	
	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());
		
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


	if (wnd.kbd.KeyIsPressed('Q'))
	{
		cam.Pitch((float)-0.1*dtheta);
	}
	
	if (wnd.kbd.KeyIsPressed('E'))
	{
		cam.Pitch((float)0.1*dtheta);
	}
	if (wnd.kbd.KeyIsPressed('Z'))
	{
		cam.RotateY((float)-0.1*dtheta);
	}

	if (wnd.kbd.KeyIsPressed('C'))
	{
		cam.RotateY((float)0.1*dtheta);
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
	box0.Update(dt);
	box0.Submit(channel1::defaultChannel);
	
	//bucket0.ProcessBucket(wnd.gfx());
	
	/*dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());*/
	
	
	rg.Execute(wnd.gfx());
	
	
	//static bool show_demo_window = false;
	
	//wnd.gfx().DrawCube(45.0f, wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
	
	wnd.gfx().EndFrame();
	rg.Reset();
}

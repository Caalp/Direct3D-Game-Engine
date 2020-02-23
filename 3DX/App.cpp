#include "App.h"
#include "Box.h"
#include "Model.h"
#include <random>
#include "Surface.h"


App::App() :
	wnd(800, 600, "Hello") ,x(0.5f),y(-4.5f),z(0.0f),last_x(0),last_y(0),
	//(wnd.gfx()),
	dirLight(wnd.gfx()),spotLight(wnd.gfx()),
	pointLight(wnd.gfx()),
	mPhi(1.5f*3.1415926535f),mTheta(1.5f*3.1415926535f),mRadius(80.0f),
	m(wnd.gfx(),"Models\\nano_textured\\nanosuit.obj"),
	b1(wnd.gfx(), cam.GetPosition(), 50, 50, 120.0f, 120.0f),
	d1(wnd.gfx(), -2.5f, 0.0f, 0.0f)
	
	
{
	
	
	water.Init(wnd.gfx(), 160, 160, 1.0f,0.03f,3.25f,0.4f);
	
	
}

App::~App()
{
	
}

int App::Go()
{
	while (true)
	{
		if (const auto error_code = Window::ProcessMessages())
		{
			return *error_code;
		}
		Update();
	}
	
}

void App::Update()
{
	float dt = 0.190f;
	float dtheta = 0.5f;
	//float dtt = timer.Mark();
	
	wnd.gfx().ClearFrame(0.2f, 0.4f, 0.5f);
	
	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());
	
  	if (wnd.kbd.KeyIsPressed('W'))
	{
		cam.Walk(dt);
	}
 	if (wnd.kbd.KeyIsPressed('S'))
	{
		
		cam.Walk(-dt);
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		
		cam.Strafe(-dt);
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		cam.Strafe(dt);
	}

	float totalTime = 1.0f;
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
	
	static float t_base = 0.0f;
	if ((totalTime - t_base) >= 0.25f)
	{
		t_base += 0.25f;

		DWORD i = 5 + rand() % (water.GetRowCount() - 10);
		DWORD j = 5 + rand() % (water.GetColumnCount() - 10);
		
		float r = MatHelper::randF(1.0f, 2.0f);

		water.Disturb(i, j, r);
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
	
	
	b1.Draw(wnd.gfx());
	
	//d1.Update(0.015f);
	d1.Draw(wnd.gfx());

	
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());

	water.Update(wnd.gfx(), 0.000648);
	water.Draw(wnd.gfx());
	
	
	
	

	
	
	wnd.gfx().EndFrame();
}

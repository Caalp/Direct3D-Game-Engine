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
	th("Models\\nano_textured\\glass_dif.png")
	
{
	
	
	water.Init(wnd.gfx(), 160, 160, 1.0f,0.03f,3.25f,0.4f);
	//d1 = new Box(wnd.gfx(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, 1.0f);
	Surface surf("");
	vb.resize(100);
	
	
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
	
	/*lastMousePos.x = wnd.mouse.GetPosX();
	lastMousePos.y = wnd.mouse.GetPosY();
	*/
	
	//if (wnd.mouse.Read().has_value()&& (wnd.mouse.Read().value().GetType() == Mouse::Event::Type::LPress) && (wnd.mouse.Read().value().GetType() == Mouse::Event::Type::Enter) )
	//{
	//	lastMousePos.x = wnd.mouse.GetPosX();
	//	lastMousePos.y = wnd.mouse.GetPosY();

	//	//SetCapture(wnd.getMainWindow());
	//}
	//if (wnd.mouse.Read().has_value() && (wnd.mouse.Read().value().GetType() == Mouse::Event::Type::Move) && wnd.mouse.Read().value().GetType() == Mouse::Event::Type::Enter )
	//{
	//	
	//	if (wnd.mouse.Read().has_value() && (wnd.mouse.Read().value().GetType() == Mouse::Event::Type::LPress) && wnd.mouse.Read().value().GetType() == Mouse::Event::Type::Enter )
	//	{
	//		float dx = DirectX::XMConvertToRadians(0.25f*static_cast<float>(x - lastMousePos.x));
	//		float dy = DirectX::XMConvertToRadians(0.25f*static_cast<float>(y - lastMousePos.y));

	//		cam.Pitch(dy);
	//		cam.RotateY(dx);
	//	}
	//	lastMousePos.x = wnd.mouse.GetPosX();
	//	lastMousePos.y = wnd.mouse.GetPosY();
	//}
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
	//water movement Test!
	if (wnd.kbd.KeyIsPressed('H'))
	{
		water.updatePosX(-dt);
	}
	if(wnd.kbd.KeyIsPressed('K'))
	{
		water.updatePosX(dt);
	}
	if(wnd.kbd.KeyIsPressed('U'))
	{
		water.updatePosY(dt);
	}
	if (wnd.kbd.KeyIsPressed('J'))
	{
		water.updatePosY(-dt);
	}
	if (wnd.kbd.KeyIsPressed('I'))
	{
		water.updatePosZ(dt);
	}
	if (wnd.kbd.KeyIsPressed('K'))
	{
		water.updatePosZ(-dt);
	}
	/*if (wnd.mouse.IsInWindow())
	{
		
		float dx = DirectX::XMConvertToRadians(0.0305f*static_cast<float>(((float)(last_x-wnd.mouse.GetPosX()))));
		float dy = DirectX::XMConvertToRadians(0.0305f*static_cast<float>(((float)(last_y-wnd.mouse.GetPosY()))));
		last_x =(float) wnd.mouse.GetPosX();
		last_y = (float)wnd.mouse.GetPosY();
		
		cam.Pitch(dy);
		cam.RotateY(dx);
	}*/
	
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_int_distribution<int> rnd(0, 800);
	
	
	/*for (int i = 0; i < 100; i++)
	{
		vb[i] = new Box(wnd.gfx(), rnd(rng), rnd(rng), 10.0f);
	}*/
	
	water.Update(wnd.gfx(), 0.000648);
	
	b1.Draw(wnd.gfx());
	
	
	
	//d1.Update(0.015f);
	d1.Draw(wnd.gfx());

	
	/*for (auto& elem : vb)
	{
		
		elem->Draw(wnd.gfx());
		elem->Update(0.015f);
	}*/
	//m.Draw(wnd.gfx());
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
	
	water.Draw(wnd.gfx());
	
	
	

	//wnd.gfx().DrawCube(45.0f, wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
	
	wnd.gfx().EndFrame();
}

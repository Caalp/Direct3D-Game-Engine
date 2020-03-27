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
	m(wnd.gfx(),"\\Models\\nano_textured\\nanosuit.obj"),
	b1(wnd.gfx(), cam.GetPosition(), 50, 50, 120.0f, 120.0f),
	d1(wnd.gfx(), -2.5f, 0.0f, 0.0f),
	crate(wnd.gfx(),0.0f,1.0f,-5.0f)
	
	
{
	
	//  bbInitializations 
	water.Init(wnd.gfx(), 160, 160, 1.0f,0.03f,3.25f,0.4f);
	wall.GenerateGrid(wnd.gfx(), "Textures\\brick01.dds", 20, 20, 1.0f, 0.03f, 0,3.0f);
	floor.GenerateGrid(wnd.gfx(), "Textures\\checkboard.dds", 30.0f, 30.0f, 1.0f, 0.03f,0, 4.0f);
	mirror.GenerateGrid(wnd.gfx(), "Textures\\ice.dds", 10.0f, 10.0f, 1.0f, 0.03f, 0.0f, 1.0f);
	cylinder.GenerateCylinder(wnd.gfx(), "Textures\\BoltAnim2", 1, 1, 1, 30, 30,2.0f);

	//Init Rotations
	wall.RotateGeometry(0.0f, -1.5708f, 1.5708f);
	mirror.RotateGeometry(0.0f, -1.5708f, 1.5708f);
	mirror.TranslateGeometry(-0.05f, 4.0f, -0.05f);
	floor.TranslateGeometry(0.0f, 0.0f, -14.5f);
	cylinder.TranslateGeometry(0.0f, 5.0f, -5.0f);
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
	
	wnd.gfx().ClearFrame(0.75f, 0.75f, 0.75f);
	
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
	if (wnd.kbd.KeyIsPressed('O'))
	{

		crate.MoveBox(dt, 0.0f, 0.0f);

	}
	
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
	//b1.Draw(wnd.gfx());
	floor.Draw(wnd.gfx());
	//wall.Draw(wnd.gfx());
	
	crate.Draw(wnd.gfx());
	

	
	//d1.Update(0.015f);
	//d1.Draw(wnd.gfx());
	

	mirror.SetBS(wnd.gfx(), BlendState::BlendType::NoRenderTargetWrite);
	mirror.SetDSS(wnd.gfx(), DSS::DSSType::Mirror);
	//mirror.Draw(wnd.gfx());
	wnd.gfx().ResetDSS();
	wnd.gfx().ResetBlendState();

	cylinder.SetDSS(wnd.gfx(), DSS::DSSType::NoDepthWrite);
	cylinder.SetRS(wnd.gfx(), RasterizerState::RasterizerType::NoCull);
	cylinder.SetBS(wnd.gfx(), BlendState::BlendType::Additive);
	cylinder.UpdateTex(0.0f);
	cylinder.Draw(wnd.gfx());
	wnd.gfx().ResetBlendState();
	wnd.gfx().ResetRS();
	wnd.gfx().ResetDSS();

	floor.ReflactionOn(true);
	floor.SetRS(wnd.gfx(), RasterizerState::RasterizerType::CullClockwise);
	floor.SetDSS(wnd.gfx(), DSS::DSSType::DrawReflaction);
	floor.Draw(wnd.gfx());

	floor.ReflactionOn(false);

	crate.ReflactionOn(true);
	//crate.SetRS(wnd.gfx(), RasterizerState::RasterizerType::CullClockwise);
	//crate.SetDSS(wnd.gfx(), DSS::DSSType::DrawReflaction);
	crate.Draw(wnd.gfx());
	wnd.gfx().ResetRS();
	wnd.gfx().ResetDSS();
	crate.ReflactionOn(false);

	

	

	//water.Update(wnd.gfx(), 0.000648);
	//water.Draw(wnd.gfx());
	
	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
	
	mirror.SetBS(wnd.gfx(), BlendState::BlendType::Transparent);
	mirror.Draw(wnd.gfx());
	wnd.gfx().ResetDSS();
	
	
	crate.ShadowOn(true);
	crate.SetDSS(wnd.gfx(), DSS::DSSType::NoDoubleBlend);
	crate.Draw(wnd.gfx());
	wnd.gfx().ResetDSS();
	wnd.gfx().ResetBlendState();
	crate.ShadowOn(false);

	
	wnd.gfx().EndFrame();
}

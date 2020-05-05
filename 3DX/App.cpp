#include "App.h"
#include "Box.h"
#include "Model.h"
#include <random>
#include "Surface.h"




App::App() :
	wnd(800,600, "Hello"), x(0.5f), y(-4.5f), z(0.0f), last_x(0), last_y(0),
	//(wnd.gfx()),
	dirLight(wnd.gfx()), spotLight(wnd.gfx()),
	pointLight(wnd.gfx()),
	mPhi(1.5f*3.1415926535f), mTheta(1.5f*3.1415926535f), mRadius(80.0f),
	m(wnd.gfx(), "\\Models\\nano_textured\\nanosuit.obj"),
	b1(wnd.gfx(), cam.GetPosition(), 50, 50, 120.0f, 120.0f),
	d1(wnd.gfx(), -2.5f, 0.0f, 0.0f),
	crate(wnd.gfx(), 0.0f, 1.0f, -5.0f),
	tree(wnd.gfx(), { "Textures\\tree0.dds","Textures\\tree1.dds","Textures\\tree2.dds","Textures\\tree3.dds" }),
	sky(wnd.gfx(), "Textures\\snowcube1024.dds",5000.0f)
	
	
{
	//server = new Server(8);
	//server->CreateServerInterface();
	//server->StartupServer();
	//  bbInitializations 
	water.Init(wnd.gfx(), 160, 160, 1.0f,0.03f,3.25f,0.4f);
	wall.GenerateGrid(wnd.gfx(), "Textures\\brick01.dds", 20, 20, 1.0f, 0.03f, 0,3.0f);
	floor.GenerateGrid(wnd.gfx(), "Textures\\checkboard.dds", 30.0f, 30.0f, 1.0f, 0.03f,0, 4.0f);
	mirror.GenerateGrid(wnd.gfx(), "Textures\\ice.dds", 10.0f, 10.0f, 1.0f, 0.03f, 0.0f, 1.0f);
	//cylinder.GenerateCylinder(wnd.gfx(), "Textures\\BoltAnim2", 1, 1, 1, 30, 30,2.0f);
	icosahedron.GenerateIcosahedron(wnd.gfx(), "Textures\\brick01.dds");
	
	
	//Init Rotations
	wall.RotateGeometry(0.0f, -1.5708f, 1.5708f);
	mirror.RotateGeometry(0.0f, -1.5708f, 1.5708f);
	mirror.TranslateGeometry(-0.05f, 4.0f, -0.05f);
	floor.TranslateGeometry(0.0f, 0.0f, -14.5f);
	//cylinder.TranslateGeometry(0.0f, 5.0f, -5.0f);
}

App::~App()
{
	//server->ShutdownServer();
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

	static float d = 0;
	d += dt;
	//server->ReceivePackets();
	crate.Update(dt);
	
	float dtheta = 0.5f;
	float v = 10.0f;
	
	
	wnd.gfx().ClearFrame(0.75f, 0.75f, 0.75f);
	
	
	
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


	{
		using namespace DirectX;
		float x(0.0f), y(0.0f), z(0.0f);
		XMFLOAT3 cameraPos(x, y, z);
		XMFLOAT3 worldUp(0.0f, 1.0f, 0.0f);

		XMFLOAT3 cameraTargets[6] =
		{
			XMFLOAT3(x + 1.0f,y,z),
			XMFLOAT3(x - 1.0f,y,z),
			XMFLOAT3(x,y + 1.0f,z),
			XMFLOAT3(x,y - 1.0f,z),
			XMFLOAT3(x,y,z + 1.0f),
			XMFLOAT3(x,y,z - 1.0f),
		};

		XMFLOAT3 cameraUps[6] =
		{
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,0.0f,-1.0f),
			XMFLOAT3(0.0f,0.0f,1.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
			XMFLOAT3(0.0f,1.0f,0.0f),
		};

		for (int i = 0; i < 6; i++)
		{
			dynamicCubeMapCamera[i].LookAt(cameraPos, cameraTargets[i], cameraUps[i]);
			dynamicCubeMapCamera[i].SetCameraLens(0.5f*3.141592654f, 1.0f, 0.1f, 1000.0f);
			dynamicCubeMapCamera[i].UpdateViewXM();
		}
	}
	for (int i = 0; i < 6; i++)
	{
		wnd.gfx().BuildDynamicCubeMapViews(i);
		wnd.gfx().SetCamera(dynamicCubeMapCamera[i].ViewProjXM());
		wnd.gfx().SetView(dynamicCubeMapCamera[i].GetViewXM());
		wnd.gfx().SetCameraPos(dynamicCubeMapCamera[i].GetPosition());

		/*dirLight.Bind(wnd.gfx());
		pointLight.Bind(wnd.gfx());
		spotLight.Bind(wnd.gfx());
		*/
		crate.Draw(wnd.gfx());
		/*sky.SetRS(wnd.gfx(), RasterizerState::RasterizerType::NoCull);
		sky.SetDSS(wnd.gfx(), DSS::DSSType::LessOrEqual);
		sky.Draw(wnd.gfx());
		wnd.gfx().ResetDSS();
		wnd.gfx().ResetRS();*/
	}

	wnd.gfx().SetDefaultRenderTarget();
	wnd.gfx().SetDefaultViewport();
	wnd.gfx().GenerateMIPsCubeMap();
	wnd.gfx().ClearFrame(0.75f, 0.75f, 0.75f);
	cam.UpdateViewXM();
	wnd.gfx().SetCamera(cam.ViewProjXM());
	wnd.gfx().SetView(cam.GetViewXM());
	wnd.gfx().SetCameraPos(cam.GetPosition());

	dirLight.Bind(wnd.gfx());
	pointLight.Bind(wnd.gfx());
	spotLight.Bind(wnd.gfx());
	//b1.Draw(wnd.gfx());
	//floor.Draw(wnd.gfx());
	////wall.Draw(wnd.gfx());
	//
	//crate.Draw(wnd.gfx());
	//

	//
	////d1.Update(0.015f);
	////d1.Draw(wnd.gfx());
	//

	//mirror.SetBS(wnd.gfx(), BlendState::BlendType::NoRenderTargetWrite);
	//mirror.SetDSS(wnd.gfx(), DSS::DSSType::Mirror);
	//mirror.Draw(wnd.gfx());
	//wnd.gfx().ResetDSS();
	//wnd.gfx().ResetBlendState();

	////cylinder.SetDSS(wnd.gfx(), DSS::DSSType::NoDepthWrite);
	////cylinder.SetRS(wnd.gfx(), RasterizerState::RasterizerType::NoCull);
	////cylinder.SetBS(wnd.gfx(), BlendState::BlendType::Additive);
	////cylinder.UpdateTex(0.0f);
	////cylinder.Draw(wnd.gfx());
	////wnd.gfx().ResetBlendState();
	////wnd.gfx().ResetRS();
	////wnd.gfx().ResetDSS();

	//floor.ReflactionOn(true);
	//floor.SetRS(wnd.gfx(), RasterizerState::RasterizerType::CullClockwise);
	//floor.SetDSS(wnd.gfx(), DSS::DSSType::DrawReflaction);
	//floor.Draw(wnd.gfx());

	//floor.ReflactionOn(false);

	//crate.ReflactionOn(true);
	//crate.SetRS(wnd.gfx(), RasterizerState::RasterizerType::CullClockwise);
	//crate.SetDSS(wnd.gfx(), DSS::DSSType::DrawReflaction);
	//crate.Draw(wnd.gfx());
	//wnd.gfx().ResetRS();
	//wnd.gfx().ResetDSS();
	//crate.ReflactionOn(false);

	//

	//

	////water.Update(wnd.gfx(), 0.000648);
	////water.Draw(wnd.gfx());
	//
	//dirLight.Bind(wnd.gfx());
	//pointLight.Bind(wnd.gfx());
	//spotLight.Bind(wnd.gfx());
	//
	//mirror.SetBS(wnd.gfx(), BlendState::BlendType::Transparent);
	//mirror.Draw(wnd.gfx());
	//wnd.gfx().ResetDSS();
	//
	//
	//crate.ShadowOn(true);
	//crate.SetDSS(wnd.gfx(), DSS::DSSType::NoDoubleBlend);
	//crate.Draw(wnd.gfx());
	//wnd.gfx().ResetDSS();
	//wnd.gfx().ResetBlendState();
	//crate.ShadowOn(false);
	//tree.SetBS(wnd.gfx(), BlendState::BlendType::AlphaToCoverage);
	/*if (wnd.kbd.KeyIsPressed('R'))
	{
		wnd.gfx().ResetBlendState();
	}
	if (wnd.kbd.KeyIsPressed('T'))
	{
		tree.SetBS(wnd.gfx(), BlendState::BlendType::AlphaToCoverage);
	}
	tree.Draw(wnd.gfx());*/
	//icosahedron.SetRS(wnd.gfx(), RasterizerState::RasterizerType::Default);
	//icosahedron.Draw(wnd.gfx());

	//sphere.SetRS(wnd.gfx(), RasterizerState::RasterizerType::Default);
	//sphere.EnableTexture(true);
	//sphere.EnableReflaction(true);
	//crate.Update(dt);
	crate.Draw(wnd.gfx());
	sphere.EnableReflaction(true);
	sphere.GenerateSphere(wnd.gfx(), "Textures\\stone.dds", 3.0f, 20, 20);
	sphere.Draw(wnd.gfx());

	sky.SetRS(wnd.gfx(), RasterizerState::RasterizerType::NoCull);
	sky.SetDSS(wnd.gfx(), DSS::DSSType::LessOrEqual);
	sky.Draw(wnd.gfx());
	
	wnd.gfx().ResetDSS();
	wnd.gfx().ResetRS();

	

	//wnd.gfx().ResetGS();
	wnd.gfx().EndFrame();
}

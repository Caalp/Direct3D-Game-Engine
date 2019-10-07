#include "App.h"
#include <time.h>
#include "Box.h"
#include "TerrainClass.h"

App::App() :
	wnd(800, 600, "Hello") ,x(0.5f),y(0.5f),z(-2.0f)
	
{
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
	//wnd.gfx().DrawTestTriangle();
	dt = 0.5f;
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f));
	wnd.gfx().ClearFrame(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 pos;
	//cam.SetPos(0.2175, 0.1275, 25.0f);
	
  	if (wnd.kbd.KeyIsPressed('W'))
	{
		x -= 0.5f;
	}
 	if (wnd.kbd.KeyIsPressed('S'))
	{
		
		x += 0.5f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		
		z += 0.5;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{

		z -= 0.5f;
	}
	if (wnd.kbd.KeyIsPressed('Q'))
	{

		y -= 0.5f;
	}
	if (wnd.kbd.KeyIsPressed('E'))
	{

		y += 0.5f;
	}
	
	if (wnd.kbd.KeyIsPressed('Z'))
	{

		cam.SetRotation(dt,0.0f , 0.0f);
	}
	if (wnd.kbd.KeyIsPressed('X'))
	{

		cam.SetRotation(0.0f, dt, z);
	}
	cam.SetPos(x, y, z);
	//cam.SetRotation(x, y, z);
	//cam.Render();
	auto m = cam.GetViewMatrix();
	//Box b1 = Box(wnd.gfx(), cam, 0.2175, 0.1275);
	TerrainClass t1 = TerrainClass(wnd.gfx(), cam, 10, 10);
	//b1.Update(1);
	cam.Render();
	t1.Draw(wnd.gfx());
	
	//wnd.gfx().DrawCube(timer.Peek(), 0.2175, 0.1275);
	
	wnd.gfx().EndFrame();

}

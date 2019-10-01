#include "App.h"
#include <time.h>
#include "Box.h"

App::App() :
	wnd(800, 600, "Hello")
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
	
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f));
	wnd.gfx().ClearFrame(c, 0.4f, 0.5f);
	cam.SetPos(0.2175, 0.1275, 25.0f);
  	if (wnd.kbd.KeyIsPressed(65))
	{
		cam.SetPos((cam.GetPos().x+100.0f/400.0f -1.0f), cam.GetPos().y, cam.GetPos().z);

	}
 	if (wnd.kbd.KeyIsPressed(68))
	{
		cam.SetPos((cam.GetPos().x + 100.0f / 400.0f + 1.0f), cam.GetPos().y, cam.GetPos().z);

	}
	if (wnd.kbd.KeyIsPressed(87))
	{
		cam.SetPos(cam.GetPos().x, cam.GetPos().y, cam.GetPos().z + 1.0f);

	}
	if (wnd.kbd.KeyIsPressed(83))
	{
		cam.SetPos((cam.GetPos().x ),cam.GetPos().y, cam.GetPos().z - 1.0f);

	}
	//cam.SetRotation(wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, -4.0f);
	cam.Render();
	Box b1 = Box(wnd.gfx(), 0.2175, 0.1275);
	b1.Update(c*2);
	b1.Draw(wnd.gfx());
	
	//wnd.gfx().DrawCube(timer.Peek(), 0.2175, 0.1275);
	
	wnd.gfx().EndFrame();

}

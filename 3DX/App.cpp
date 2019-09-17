#include "App.h"
#include <time.h>


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
	
	wnd.gfx().ClearFrame(c, 0.4f, 0.5f);
	
	
	wnd.gfx().DrawCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
	
	wnd.gfx().EndFrame();

}

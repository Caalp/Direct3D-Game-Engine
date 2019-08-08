#include "App.h"

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
	wnd.gfx().EndFrame();
	wnd.gfx().ClearFrame(0.1f, 0.1f, 1.0f);
	

}

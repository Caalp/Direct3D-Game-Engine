#include <Windows.h>
#include "Window.h"
#include "App.h"

int CALLBACK WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	
	App{}.Go();
	// error chatching required
}
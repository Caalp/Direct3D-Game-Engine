#include <Windows.h>
#include "Window.h"
#include "App.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int CALLBACK WinMain(
					HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	FILE* stream = nullptr;
	if (!GetConsoleWindow()) {
		
		AllocConsole();
		freopen_s(&stream,"CONOUT$", "wt", stdout);
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		
	}
	
		

	App{}.Go();
	
	fclose(stream);

	// error chatching required
}
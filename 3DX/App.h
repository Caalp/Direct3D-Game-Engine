#pragma once
#include "Window.h"
#include "ImguiHandler.h"
#include "TestRenderGraph.h"
#include "RenderGraph.h"
#include "TestBox.h"
#include "TransformationSystem.h"
#include "RenderSystem.h"
#include "CameraSystem.h"
#include "SceneLoader.h"

class App
{
public:

	App();
	~App();
	int Go();
private:
	void Update(float dt);
	void ImguiStatistic();
private:

	ImguiHandler& imguiHandler;
	Window wnd;
	SceneLoader* m_SceneLoader;
	/*--------------------- Systems-------------------------------*/


	/*---------------------------------------------------------*/
	


	bool updated = false;
	
};
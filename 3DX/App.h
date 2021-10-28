#pragma once
#include "CameraComponent.h"
#include "SkyBox.h"
#include "TestShape.h"
#include "ImguiHandler.h"
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
	CameraComponent m_mainCamera;
	bool updated = false;
	ImguiHandler& m_imguiInstance;
	SkyBox skyBox;
	TestShape testShape_1;
	TestShape testShape_2;
};
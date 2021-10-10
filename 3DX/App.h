#pragma once
#include "CameraComponent.h"
#include "SkyBox.h"
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
	
	SkyBox skyBox;
};
#pragma once
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
#include "Model.h"
#include "CommandBucket.h"
#include "Timer.h"
class App
{
public:
	App();
	~App();
	int Go();
private:
	void Update(float dt);
private:
	
	Window wnd;
	Camera cam;
	DirectionalLight dirLight;
	PointLight pointLight;
	SpotLight spotLight;
	float x, y, z,dt;
	float last_x;
	float last_y;
	float mPhi, mTheta,mRadius;
	CommandBucket bucket0;
	//Model m;
	//TerrainClass b1{ wnd.gfx(), cam.GetPosition(), 50, 50, 160.0f, 160.0f };
	Box box0{ wnd.gfx(),0.0f,0.0f,0.0f };
	std::vector<Box*> vb;
	Timer timer;
};
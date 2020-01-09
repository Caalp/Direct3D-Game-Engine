#pragma once
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
class App
{
public:
	App();
	~App();
	int Go();
private:
	void Update();
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
	//Model m;
	TerrainClass b1{ wnd.gfx(), cam.GetPosition(), 50, 50, 160.0f, 160.0f };
	Box d1{ wnd.gfx(),300.0f,400.0f,0.0f };
	std::vector<Box*> vb;

};
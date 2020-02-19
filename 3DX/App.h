#pragma once
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
#include "Model.h"
#include "TextureLoader.h"
//#include "Timer.h"
#include "Water.h"
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
	Model m;
	//Timer timer;
	TerrainClass b1{ wnd.gfx(), cam.GetPosition(), 50, 50, 120.0f, 120.0f };
	Box d1{ wnd.gfx(),0.0f,10.0f,0.0f };
	std::vector<Box*> vb;
	TextureLoader th;
	Water water;
	POINT lastMousePos;
};
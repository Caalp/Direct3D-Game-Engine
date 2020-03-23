#pragma once
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
#include "Model.h"
#include "TextureLoader.h"
#include "GeometryGenerator.h"
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
	TerrainClass b1;
	Box d1;
	Water water;
	POINT lastMousePos;
	GeometryGenerator wall;
	GeometryGenerator floor;
	GeometryGenerator mirror;
	GeometryGenerator cylinder;
	Box crate;
};
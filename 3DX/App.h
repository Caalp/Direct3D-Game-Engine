#pragma once

#include "WindowsIncludes.h"
//#include "Server.h"
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
#include "Model.h"
#include "TextureLoader.h"
#include "GeometryGenerator.h"
#include "Tree.h"
#include "Timer.h"
#include "Water.h"
#include "Sky.h"
#include "Bezier.h"
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
	Camera dynamicCubeMapCamera[6];
	DirectionalLight dirLight;
	PointLight pointLight;
	SpotLight spotLight;
	float x, y, z, dt;
	float last_x;
	float last_y;
	float mPhi, mTheta, mRadius;
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
	//Server* server;
	Tree tree;
	GeometryGenerator icosahedron;
	GeometryGenerator sphere;
	Sky sky;
	Timer timer;
	Bezier bezierPatch;
};
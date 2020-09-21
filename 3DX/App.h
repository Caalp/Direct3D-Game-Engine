#pragma once
#include "Window.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TerrainClass.h"
#include "Model.h"
#include "CommandBucket.h"
#include "TestRenderGraph.h"
#include "Plane.h"
#include "MirrorRenderGraph.h"
#include "SceneRenderer.h"
#include "TestCube.h"
#include "Sky.h"


class App
{
public:

	App();
	~App();
	int Go();
private:
	void Update(float dt);
private:
	
	Scene testScene;
	Window wnd;
	Camera cam;
	SceneRenderer sceneRenderer;
	DirectionalLight dirLight;
	PointLight pointLight;
	SpotLight spotLight;
	float x, y, z,dt;
	float last_x;
	float last_y;
	float mPhi, mTheta,mRadius;
	TestRenderGraph rg{ wnd.gfx() };
	MirrorRenderGraph rgMirror{ wnd.gfx() };
	TestCube testCube{ wnd.gfx(),0.0f,0.0f,10.0f };
	Plane mirror { wnd.gfx(),"mirror",10.0f, 10.0f, 1.0f, 0.03f, 0.0f, 1.0f };
	Plane floor{ wnd.gfx(),"floor", 30.0f, 30.0f, 1.0f, 0.03f, 0, 4.0f };
	Box box0{ wnd.gfx(),0.0f,0.0f,0.0f };
	Sky sky{ wnd.gfx(),"skySphere",5000.0f,30,30 };

	
};
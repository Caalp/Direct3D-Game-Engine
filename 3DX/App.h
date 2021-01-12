#pragma once
#include "Window.h"
#include "ImguiHandler.h"
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
#include "AnimatedCharacter.h"


class App
{
public:

	App();
	~App();
	int Go();
private:
	void Update(float dt);
private:
	float animTimer = 0.0288f;
	//Scene testScene;
	ImguiHandler imguiHandler;
	Window wnd;
	Camera cam;
	
	SceneRenderer sceneRenderer;
	DirectionalLight dirLight;
	float animTime = 0.0f;
	SpotLight spotLight{wnd.gfx()};
	PointLight pointLight;
	float dt;
	float last_x;
	float last_y;
	float mPhi, mTheta,mRadius;
	TestRenderGraph rg{ wnd.gfx() };
	MirrorRenderGraph rgMirror{ wnd.gfx() };
	TestCube testCube{ wnd.gfx(),0.0f,0.0f,10.0f };
	Plane mirror { wnd.gfx(),"mirror",10u, 10u, 1.0f, 0.03f, 0.0f, 1.0f };
	Plane floor{ wnd.gfx(),"floor", 30u, 30u, 1.0f, 0.03f, 0, 4.0f };
	Box box0{ wnd.gfx(),0.0f,0.0f,0.0f };
	Sky sky{ wnd.gfx(),"skySphere",5000.0f,30,30 };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/mouse.fbx","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/nanosuit.obj","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/box/box.obj","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/silly_dancing/silly_dancing.fbx","boblamp" };
	
	
	AnimatedCharacter chr{ wnd.gfx(),"../Models/boblamp/boblampclean.md5mesh","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/drone/drone.X","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/soldier/soldier.X","boblamp" };
	//AnimatedCharacter chr{ wnd.gfx(),"../Models/TestModel.fbx","boblamp" };
	bool updated = false;
	
};
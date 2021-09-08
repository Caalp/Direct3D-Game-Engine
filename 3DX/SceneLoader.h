#pragma once
#include "Scene.h"

class Scene;

class SceneLoader
{

public:
	/* Get singleton scene loader scene*/
	static SceneLoader* GetSingleton();

	~SceneLoader()
	{
		//delete p_RootScene;
	}

	/*Get root scene if one is not exist create and return it*/
	Scene* CreateRootScene();
	
	/* Get Root Scene, will return nullptr if root is not initialized*/
	static Scene* GetRootScene();




private:

	Scene* p_RootScene = nullptr;
	Scene* p_CurrentScene; // Current selected scene

	

};
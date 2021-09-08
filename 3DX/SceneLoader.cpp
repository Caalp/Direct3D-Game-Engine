#include "SceneLoader.h"
#include <iostream>

SceneLoader* SceneLoader::GetSingleton()
{
	static SceneLoader sceneLoader;
	return &sceneLoader;
}
Scene* SceneLoader::CreateRootScene()
{
	// Check if root scene is already exist refuse to create another one
	if (p_RootScene != nullptr)
	{
		std::cout << "Attempt to create second Root Scene blocked!" << std::endl;
		return nullptr;
	}

	// Create a root scene 
	p_RootScene = Scene::CreateRootScene();

	return p_RootScene;
}

Scene* SceneLoader::GetRootScene()
{
    
    return SceneLoader::GetSingleton()->p_RootScene;
    
}

#pragma once
#include <memory>
#include "Scene.h"

class SceneRenderer
{
public:
	void UpdateScene(float dt);
	


public:
	static Scene scene;
};

//std::unique_ptr<Scene> SceneRenderer::scene = std::unique_ptr<Scene>(new Scene());
Scene SceneRenderer::scene;
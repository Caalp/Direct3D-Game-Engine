#pragma once
#include <memory>
class Scene;

class SceneRenderer
{
	friend class Drawable;
public:
	void UpdateScene(float dt);
	


private:
	static Scene scene;
};

//std::unique_ptr<Scene> SceneRenderer::scene = std::unique_ptr<Scene>(new Scene());

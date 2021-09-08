#pragma once

#include <vector>
#include <memory>
#include <string>
#include "DrawCallDispatch.h"
#include "Types.h"
#include "IndexBuff.h"
#include "VertexBuffer.h"


class PixelShader;
class VertexShader;
class RenderGraph;
class RenderQueuePass;
class Bindable;
class Drawable;
class Graphics;
class RenderableComponent;
class Renderable;

class Step
{

public:
	Step(std::string targetName);
	Step(const Step&) = default;
	//void AddPacket(CommandPacket* cmdPkt);
	void AddBind(std::shared_ptr<Bindable> bindable);
	void AddBind(const std::shared_ptr<IBackendDispatch>& drawFunc);
	void Submit(Renderable& d);

	void Link(RenderGraph& fg);
	void Bind(Graphics& gfx) const;
	void Bind() const;
	
	
	void Draw(Graphics& gfx) const;
	void Draw() const;

	const std::string& GetTargetPassName() const;
	bool isLinked() const;

	//void Submit(RenderGraph& rg);
private:
	bool linked = false;
	std::string targetPassName;
	std::vector<std::shared_ptr<Bindable>> bindables;
	RenderQueuePass* targetPass;
	std::vector<std::shared_ptr<IBackendDispatch>> mDrawFunc;

};

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "DrawCallDispatch.h"


class PixelShader;
class VertexShader;
class RenderGraph;
class RenderQueuePass;
class Bindable;
class Drawable;
class Graphics;



class Step
{

public:
	Step(std::string targetName);
	Step(const Step&) = default;
	//void AddPacket(CommandPacket* cmdPkt);
	void AddBind(std::shared_ptr<Bindable> bindable);
	void AddBind(const std::shared_ptr<IBackendDispatch>& drawFunc);
	void Submit(Drawable& d);
	void Link(RenderGraph& rg);
	void Bind(Graphics& gfx) const ;
	
	
	void Draw(Graphics& gfx) const;

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

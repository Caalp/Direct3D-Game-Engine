#pragma once

#include <vector>
#include <memory>
#include <string>




class RenderGraph;
class RenderQueuePass;
class Bindable;
class Drawable;
class Graphics;

class Step
{
	
public:
	Step( std::string targetName);
	void AddBind(std::shared_ptr<Bindable> bindable);
	void Submit(Drawable& d);
	void Link(RenderGraph& rg);
	void Bind(Graphics& gfx) const ;
	const std::string& GetTargetPassName() const;
	bool isLinked() const;

	//void Submit(RenderGraph& rg);
private:
	bool linked = false;
	std::string targetPassName;
	std::vector<std::shared_ptr<Bindable>> bindables;
	RenderQueuePass* targetPass;
	//static const BackendDispatchFunction dispatchFunction;
};

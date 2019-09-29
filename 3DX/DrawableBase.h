#pragma once
#include <memory>
#include <vector>
#include "Bindables.h"
class DrawableBase
{
public:
	DrawableBase() = default;
	DrawableBase(const DrawableBase&) = delete;
	void Draw(Graphics& gfx);
	virtual void Update(float ft) = 0;
	void AddBind(std::unique_ptr<Bindables> binds);
	
	
protected:
	std::vector<std::unique_ptr<Bindables>> bindables;
		
};
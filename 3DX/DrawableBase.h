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
	virtual DirectX::XMMATRIX GetViewXM() const = 0;
	virtual DirectX::XMMATRIX GetWorldXM() const = 0;
	virtual DirectX::XMMATRIX GetProjXM() const = 0;
protected:
	void AddBind(std::unique_ptr<Bindables> binds);
	virtual const std::vector<std::unique_ptr<Bindables>>& GetStaticBindables() = 0;
	
	
protected:
	std::vector<std::unique_ptr<Bindables>> bindables;
	
};
#pragma once

#include "additional_headers.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void Draw(Graphics& gfx);
	void AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer);
	void SetIndexBufferFromStatic();
	bool isStaticallyBinded() const;
	virtual void Update(float ft) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const = 0;


protected:
	void AddBind(std::unique_ptr<Bindables> binds);
	void AddStaticBind(std::unique_ptr<Bindables> sbinds);

private:
	//virtual const std::vector<std::unique_ptr<Bindables>>& GetStaticBinds() const noexcept = 0;
protected:
	const IndexBuff*  pIndexBuffer;
	std::vector<std::unique_ptr<Bindables>> bindables;
	std::vector<std::unique_ptr<Bindables>> staticBindables;
};



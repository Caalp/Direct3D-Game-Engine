#pragma once

#include "additional_headers.h"

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void SetBlendState(bool state);
	void Draw(Graphics& gfx);
	void AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer);
	void SetIndexBufferFromStatic();
	bool isStaticallyBinded() const;
	virtual void Update(float ft) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const = 0;
	virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }
	template<typename T> 
	void UpdateVertexBuffer(Graphics& gfx, const T& v)
	{
		for (auto& b : bindables)
		{
			if (typeid(*b) == typeid(VertexBuffer))
			{
				auto buff = dynamic_cast<VertexBuffer*>(b.get());
				buff->Update(gfx, v);
			}

		}
	}


protected:
	void AddBind(std::unique_ptr<Bindables> binds);
	void AddStaticBind(std::unique_ptr<Bindables> sbinds);

private:
	//virtual const std::vector<std::unique_ptr<Bindables>>& GetStaticBinds() const noexcept = 0;
protected:
	bool blendOn = false;
	const IndexBuff*  pIndexBuffer;
	BlendState* pBlendState;
	std::vector<std::unique_ptr<Bindables>> bindables;
	std::vector<std::unique_ptr<Bindables>> staticBindables;
};



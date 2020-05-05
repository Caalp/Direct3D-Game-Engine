#pragma once

#include "additional_headers.h"
#include <stack>

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
	void SetRS(Graphics& gfx, RasterizerState::RasterizerType rType);
	void SetBS(Graphics& gfx, BlendState::BlendType bType);
	void SetDSS(Graphics& gfx, DSS::DSSType dType);
	virtual void Update(float ft) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTransformation(Graphics& gfx) const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }
	template<typename T> 
	void UpdateVertexBuffer(Graphics& gfx, const T& v)
	{
		for (auto& b : Bindables)
		{
			if (typeid(*b) == typeid(VertexBuffer))
			{
				auto buff = dynamic_cast<VertexBuffer*>(b.get());
				buff->Update(gfx, v);
			}

		}
	}


protected:
	void AddBind(std::unique_ptr<Bindable> binds);
	void AddStaticBind(std::unique_ptr<Bindable> sbinds);

private:
	//virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
protected:
	bool blendOn = false;
	const IndexBuff*  pIndexBuffer = nullptr;
	BlendState* pBlendState;
	
	std::vector<std::unique_ptr<Bindable>> Bindables;
	std::vector<std::unique_ptr<Bindable>> staticBindable;
	std::stack< std::unique_ptr<Bindable>> renderStates;
};



#pragma once
#include "additional_headers.h"

template<typename T>
class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable<T>&) = delete;
	void Draw(Graphics& gfx);
	void AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer);
	void SetIndexBufferFromStatic();
	bool isStaticallyBinded() const;
	virtual void Update(float ft) = 0;
	virtual DirectX::XMMATRIX GetTransformation() const = 0;


protected:
	void AddBind(std::shared_ptr<Bindables> binds);
	void AddStaticBind(std::shared_ptr<Bindables> sbinds);

private:
	//virtual const std::vector<std::unique_ptr<Bindables>>& GetStaticBinds() const noexcept = 0;
protected:
	const IndexBuff*  pIndexBuffer;
	std::vector<std::shared_ptr<Bindables>> bindables;
	static std::vector<std::unique_ptr<Bindables>> staticBindables;
};

template<typename T>
inline void Drawable<T>::Draw(Graphics & gfx)
{
	for (auto& b : bindables)
	{
		b->Bind(gfx);
	}
	for (auto& b : staticBindables)
	{
		if (typeid(*b) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
		}
		b->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetIndexCount());
}

template<typename T>
inline void Drawable<T>::AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer)
{
	pIndexBuffer = indexBuffer.get();
}

template<typename T>
inline void Drawable<T>::SetIndexBufferFromStatic()
{
	for (auto& elem : GetStaticBinds())
	{
		if (typeid(*elem) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(elem.get());
			return;
		}
	}
}

template<typename T>
inline bool Drawable<T>::isStaticallyBinded() const
{
	if (staticBindables.empty())
	{
		return false;
	}
	return true;
}

template<typename T>
inline void Drawable<T>::AddBind(std::shared_ptr<Bindables> binds)
{
	bindables.push_back(std::move(binds));
}

template<typename T>
inline void Drawable<T>::AddStaticBind(std::shared_ptr<Bindables> sbinds)
{
	staticBindables.push_back(std::move(sBinds));
}
template<typename T>
std::vector<std::unique_ptr<Bindables>> Drawable<T>::staticBindables;
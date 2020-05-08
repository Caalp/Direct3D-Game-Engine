//#pragma once
//#include <memory>
//#include <vector>
//#include "Bindables.h"
//#include "Camera.h"
//class DrawableBase
//{	
//public:
//	DrawableBase() = default;
//	DrawableBase(const DrawableBase&) = delete;
//	void Draw(Graphics& gfx);
//	void AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer);
//	void SetIndexBufferFromStatic();
//	virtual void Update(float ft) = 0;
//	virtual DirectX::XMMATRIX GetTransformation() const = 0;
//	
//		
//protected:
//	void AddBind(std::shared_ptr<Bindables> binds);
//	void AddStaticBind(std::shared_ptr<Bindables> sbinds);
//	
//private:
//	 virtual const std::vector<std::unique_ptr<Bindables>>& GetStaticBinds() const noexcept = 0;
//protected:
//	const IndexBuff*  pIndexBuffer;
//	std::vector<std::shared_ptr<Bindables>> bindables;
//	
//	
//};
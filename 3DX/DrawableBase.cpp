//#include "DrawableBase.h"
//#include "IndexBuff.h"
//
//void DrawableBase::Draw(Graphics & gfx)
//{
//	for (auto& b : Bindable)
//	{
//		b->Bind(gfx);
//	}
//	for (auto& b : GetStaticBinds())
//	{
//		if (typeid(*b) == typeid(IndexBuff))
//		{
//			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
//		}
//		b->Bind(gfx);
//	}
//	
//	gfx.DrawIndexed(pIndexBuffer->GetIndexCount());
//}
//
//void DrawableBase::AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer)
//{
//	pIndexBuffer = indexBuffer.get();
//	//staticBindable.push_back(std::move(indexBuffer));
//}
//
//void DrawableBase::SetIndexBufferFromStatic()
//{
//
//	for (auto& elem : GetStaticBinds())
//	{
//		if (typeid(*elem) == typeid(IndexBuff))
//		{
//			pIndexBuffer = dynamic_cast<IndexBuff*>(elem.get());
//			return;
//		}
//	}
//}
//
//
//void DrawableBase::AddBind(std::shared_ptr<Bindable> binds)
//{
//	Bindable.push_back(std::move(binds));
//}


 
 
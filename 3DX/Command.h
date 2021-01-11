//#pragma once
//#include "Graphics.h"
//function pointer typedef
//typedef void(*BackendDispatchFunction)(const void*);
//class IBackendDispatch
//{
//
//public:
//	IBackendDispatch() = default;
//	virtual void Draw(Graphics& gfx) = 0;
//};
//namespace command
//{
//
//	struct Draw
//	{
//		static const BackendDispatchFunction BackendDispatch;
//		UINT startIndex;
//		UINT indexCount;
//		
//		
//
//	};
//	struct DrawIndexed
//	{
//		static const BackendDispatchFunction BackendDispatch;
//		UINT startIndex;
//		UINT indexCount;
//
//
//	};
//	const BackendDispatchFunction DrawIndexed::BackendDispatch = &(backendDispatch::DrawIndexed);
//}
//
//class DrawIndexedFunc: public IBackendDispatch
//{
//public:
//	DrawIndexedFunc() = default;
//	DrawIndexedFunc(unsigned int startIndex, unsigned int indexCount) : mStartIndex(startIndex),mIndexCount(indexCount)
//	{
//
//	}
//	virtual void Draw(Graphics& gfx) override
//	{
//		gfx.DrawIndexed(mIndexCount);
//	}
//private:
//	unsigned int mStartIndex;
//	unsigned int mIndexCount;
//};
//
//namespace backendDispatch 
//{
//	void Draw(const void* data)
//	{
//		const command::Draw* realData = reinterpret_cast<const command::Draw*>(data);
//		
//	}
//	void DrawIndexed(const void* data)
//	{
//		const command::DrawIndexed* realData = reinterpret_cast<const command::DrawIndexed*>(data);
//		Graphics::pImmediateContext->DrawIndexed(realData->indexCount, realData->startIndex, 0);
//		
//	}
//}

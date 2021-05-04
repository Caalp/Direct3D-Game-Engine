//#pragma once
//#include "Graphics.h"
//#include <iostream>
//
//typedef void(*BackendDispatchFunction)(const void*);
//
//class IBackendDispatch2
//{
//
//public:
//
//	IBackendDispatch2() = default;
//	virtual void Draw(Graphics& gfx) const = 0;
//	virtual ~IBackendDispatch2() = default;
//};
//
//
////class DrawIndexed : public IBackendDispatch
////{
////public:
////	DrawIndexed() = default;
////	DrawIndexed(unsigned int startIndex, unsigned int indexCount) : m_StartIndex(startIndex), m_IndexCount(indexCount)
////	{
////		m_VertexBaseIndex = 0;
////	}
////	DrawIndexed(uint32_t indexCount, uint32_t startIndex, int vertexBaseIndex) : m_StartIndex(startIndex), m_IndexCount(indexCount), m_VertexBaseIndex(vertexBaseIndex)
////	{
////
////	}
////
////	virtual void Draw(Graphics& gfx)const  override
////	{
////		//gfx.DrawIndexed(mIndexCount, mStartIndex, m_vertexBaseIndex);
////
////		std::cout << "DrawIndexed..." << std::endl;
////	}
////
////private:
////	unsigned int m_StartIndex;
////	unsigned int m_IndexCount;
////	int m_VertexBaseIndex;
////};
//
//class DrawVertex : public IBackendDispatch2
//{
//public:
//	DrawVertex() = default;
//
//	DrawVertex(uint32_t vertexCount, uint32_t vertexStartIndex) :m_VertexCount(vertexCount), m_VertexStartIndex(vertexStartIndex)
//	{
//
//	}
//	virtual void Draw(Graphics& gfx) const  override
//	{
//		std::cout << "DrawVertex..." << std::endl;
//	}
//
//private:
//	unsigned int m_VertexCount;
//	unsigned int m_VertexStartIndex;
//
//
//};
//
//
//
////class IBackendDispatch
////{
////
////public:
////	IBackendDispatch() = default;
////	virtual void Draw(Graphics& gfx) = 0;
////};
////namespace command
////{
////
////	struct Draw
////	{
////		static const BackendDispatchFunction BackendDispatch;
////		UINT startIndex;
////		UINT indexCount;
////		
////		
////
////	};
////	struct DrawIndexed
////	{
////		static const BackendDispatchFunction BackendDispatch;
////		UINT startIndex;
////		UINT indexCount;
////
////
////	};
////	const BackendDispatchFunction DrawIndexed::BackendDispatch = &(backendDispatch::DrawIndexed);
////}
////
////class DrawIndexedFunc: public IBackendDispatch
////{
////public:
////	DrawIndexedFunc() = default;
////	DrawIndexedFunc(unsigned int startIndex, unsigned int indexCount) : mStartIndex(startIndex),mIndexCount(indexCount)
////	{
////
////	}
////	virtual void Draw(Graphics& gfx) override
////	{
////		gfx.DrawIndexed(mIndexCount);
////	}
////private:
////	unsigned int mStartIndex;
////	unsigned int mIndexCount;
////};
////
////namespace backendDispatch 
////{
////	void Draw(const void* data)
////	{
////		const command::Draw* realData = reinterpret_cast<const command::Draw*>(data);
////		
////	}
////	void DrawIndexed(const void* data)
////	{
////		const command::DrawIndexed* realData = reinterpret_cast<const command::DrawIndexed*>(data);
////		Graphics::pImmediateContext->DrawIndexed(realData->indexCount, realData->startIndex, 0);
////		
////	}
////}

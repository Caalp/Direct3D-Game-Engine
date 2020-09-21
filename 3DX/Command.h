//#pragma once
//
//
////function pointer typedef
//typedef void(*BackendDispatchFunction)(const void*);
////
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
////		IndexBuff* indexBuffer;
////		VertexBuffer* vertexBuffer;
////		PrimitiveTopology* primitiveTopology;
////
////	};
////	const BackendDispatchFunction DrawIndexed::BackendDispatch = &(backendDispatch::DrawIndexed);
////}
//
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

#pragma once


//function pointer typedef
typedef void(*BackendDispatchFunction)(const void*,void*);

namespace command
{
	struct Draw
	{
		static const BackendDispatchFunction BackendDispatch;
		UINT startIndex;
		UINT indexCount;
		//vertexbuffer
		//primitiveTopology
		//vertexlayout

	};
	struct DrawIndexed
	{
		static const BackendDispatchFunction BackendDispatch;
		UINT startIndex;
		UINT indexCount;
		//std::unique_ptr<Bindable> vertexBuffer;
		//std::unique_ptr<Bindable> indexBuff;
		//std::unique_ptr<PrimitiveTopology> topology;
		
		//vertexlayout

	};
	const BackendDispatchFunction DrawIndexed::BackendDispatch = &backendDispatch::DrawIndexed;
}


namespace backendDispatch 
{
	void Draw(const void* data,void* gfx)
	{
		const command::Draw* realData = reinterpret_cast<const command::Draw*>(data);
		
	}
	void DrawIndexed(const void* data,void* gfx)
	{
		const command::DrawIndexed* realData = reinterpret_cast<const command::DrawIndexed*>(data);
		Graphics* const pGfx = reinterpret_cast<Graphics* const>(gfx);
		pGfx->DrawIndexed(realData->indexCount);
		//Graphics::DrawIndexed(realData->indexCount);
	}
}

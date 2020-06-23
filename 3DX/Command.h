#pragma once


//function pointer typedef
typedef void(*BackendDispatchFunction)(const void*);

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
}


namespace backendDispatch 
{
	void Draw(const void* data)
	{
		const command::Draw* realData = reinterpret_cast<const command::Draw*>(data);
		// TO DO : backend draw call
	}
	void DrawIndexed(const void* data)
	{
		const command::DrawIndexed* realData = reinterpret_cast<const command::DrawIndexed*>(data);
		
		//Graphics::DrawIndexed(realData->indexCount);
	}
}

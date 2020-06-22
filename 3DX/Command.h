#pragma once


typedef const void* BackendDispatchFunction;


namespace command
{
	struct Draw
	{

		//backendDispatch function
		//vertexCount
		//startindex
		//vertexbuffer
		//primitiveTopology
		//vertexlayout

	};
	struct DrawIndexed
	{

		BackendDispatchFunction bdf;
		UINT startIndex;
		UINT indexCount;
		std::unique_ptr<Bindable> vertexBuffer;
		std::unique_ptr<Bindable> indexBuff;
		std::unique_ptr<PrimitiveTopology> topology;
		
		//vertexlayout

	};
}


namespace BackendDispatch 
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

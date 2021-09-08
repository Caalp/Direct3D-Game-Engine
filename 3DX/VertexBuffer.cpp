#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics & gfx)
{
	GraphicsResources::GetSingleton().pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}

void VertexBuffer::Bind()
{
	GraphicsResources::GetSingleton().pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
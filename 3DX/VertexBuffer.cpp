#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics & gfx)
{
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
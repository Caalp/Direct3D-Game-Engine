#include "Drawable.h"

void Drawable::Bind(Graphics & gfx) const
{
	indexBuffer->Bind(gfx);
	vertexBuffer->Bind(gfx);
	primitiveTopology->Bind(gfx);
}

void Drawable::LinkBucket(CommandBucket * cmdBucket)
{
	cmdBucket->Submit(std::move(cmdPacket));
}




void Drawable::PushPacket(std::shared_ptr<CommandPacket> cmd)
{
	cmdPacket = std::move(cmd);
}

UINT Drawable::GetIndexCount() const
{
	return indexBuffer->GetIndexCount();
}


#include "CommandBucket.h"


//CommandBucket::CommandBucket(const Drawable * db, std::string bucketID)
//{
//}

void CommandBucket::Submit(std::shared_ptr<CommandPacket> cmd)
{
	cmdPacket.push_back(std::move(cmd));
}

void CommandBucket::ProcessBucket(Graphics& gfx)
{
	for (auto& elem : cmdPacket)
	{
		elem->Bind(gfx);
	}
}

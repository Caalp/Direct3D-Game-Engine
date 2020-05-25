#pragma once
#include "CommandPacket.h"



class CommandBucket
{
public:
	//CommandBucket(const Drawable* db,std::string bucketID);
	void Submit(std::shared_ptr<CommandPacket> cmdPacket);
	void ProcessBucket(Graphics& gfx);
	


private:
	std::vector <std::shared_ptr<CommandPacket>> cmdPacket;
};
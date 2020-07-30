#include "Sink.h"


Sink::Sink(std::string sinkName) : sinkName(sinkName)
{
}

void Sink::SetPassName(std::string passName)
{
	sinkPassName = passName;
}

void Sink::SetTargetName(std::string targetName)
{
	sinkTargetName = targetName;
}

const std::string& Sink::GetRegisteredName() const
{
	return std::move(sinkName);
}

const std::string& Sink::GetPassName() const
{
	return sinkPassName;
}

const std::string& Sink::GetTargetName() const
{
	return sinkTargetName;
}


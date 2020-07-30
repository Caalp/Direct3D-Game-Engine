#include "Source.h"

Source::Source(std::string sourceName) : sourceName(sourceName)
{
}

const std::string& Source::GetName() const
{
	return sourceName;
}

std::shared_ptr<BufferResource> Source::GetSource()
{
	return std::shared_ptr<BufferResource>();
}

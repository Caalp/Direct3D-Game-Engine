#include "CustomException.h"
#include <sstream>

CustomException::CustomException(int line, const char * file) noexcept
	:
	line(line),
	file(file)
{
}

const char * CustomException::what() const noexcept
{
	std::ostringstream os;
	os << GetType() << std::endl << GetOriginString();
	wBuffer = os.str();
	return wBuffer.c_str();

}

const char * CustomException::GetType() const noexcept
{
	return "Custom Exception Handling";
}

int CustomException::GetLine() const noexcept
{
	return line;
}

const std::string & CustomException::GetFile() const noexcept
{
	return file;
}

std::string CustomException::GetOriginString() const noexcept
{
	std::ostringstream os;
	os << "File = " << file << std::endl << " Line = " << line;
	return os.str();

}

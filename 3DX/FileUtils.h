#pragma once
#include <string>
//#include <fstream>

namespace FileUtils
{
	std::wstring OpenFileDialog();
	FILE* OpenFile(const char* filepath);
}
#include "FilesHelper.h"

std::string FilesHelper::getTextFromFile(const char* filePath)
{
	std::fstream file(filePath);
	std::stringstream ss;
	std::string line;
	while (getline(file, line))
	{
		ss << line;
	}
	file.close();
	return ss.str();
}
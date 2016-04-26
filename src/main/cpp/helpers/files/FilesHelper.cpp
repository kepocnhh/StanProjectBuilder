#include "FilesHelper.h"

const std::string FilesHelper::error_open_file = "{\"error\":{\"message\":\"Can't open file\",\"type\":\"Open file\"}}";

std::string FilesHelper::getTextFromFile(const char* filePath)
{
	std::fstream file(filePath);
    if (!file.is_open())
    {
		return FilesHelper::error_open_file;
	}
	std::stringstream ss;
	std::string line;
	while (getline(file, line))
	{
		ss << line;
	}
	file.close();
	return ss.str();
}
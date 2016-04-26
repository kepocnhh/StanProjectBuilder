#include <sstream>
#include <string>
#include <fstream>

class FilesHelper
{
private:
public:
    static std::string getTextFromFile(const char* filePath);
	//
    static const std::string error_open_file;

protected:
};
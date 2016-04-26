#include <string>
#include "Build.h"

class Project
{
private:
public:
    Project();
	struct settings
	{
		std::string name;
		std::string rootDir;
		std::string type;
	}
	projectSettings;
	Build* build;
	//
    static const std::string error_incorrect_file;

protected:
};
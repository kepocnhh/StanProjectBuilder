#include <string>
#include "Build.h"
#include "Run.h"

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
	Run* run;
	//
    static const std::string error_incorrect_file;

protected:
};
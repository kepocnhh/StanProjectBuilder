#include <string>
#include "command/Command.h"

class Project
{
private:
public:
    Project();
	struct settings
	{
		std::string name;
		std::string rootDir;
		int type;
	}
	projectSettings;
	Command* runCommands;
	//
    static const std::string error_incorrect_file;
    static const std::string error_deserialize_file;

protected:
};
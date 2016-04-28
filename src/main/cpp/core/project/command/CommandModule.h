#include <string>
#include "Command.h"
#include "../Module.h"

class CommandModule : public Command
{
private:
public:
	int modulesSize;
	Module* modules;
	//
	CommandModule(std::string commandName, int commandType);

protected:
};
#include "Command.h"

Command::Command(std::string commandName, int commandType)
{
	name = commandName;
	type = commandType;
}
Command::Command()
{
}
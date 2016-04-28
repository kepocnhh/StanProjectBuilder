#include "Command.h"

class CommandGroup : public Command
{
private:
public:
	int commandsSize;
	Command* commands;
	//
	CommandGroup(std::string commandName, int commandType);

protected:
};
#ifndef _Command_H
#define _Command_H

#include <string>

class Command
{
private:
public:
	std::string name;
	int type;
	int preSize;
	std::string* pre;
	int postSize;
	std::string* post;
	//
	Command(std::string commandName, int commandType);
	Command();

protected:
};

#endif // _Command_H
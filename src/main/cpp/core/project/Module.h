#ifndef _Module_H
#define _Module_H

#include <string>

class Module
{
private:
public:
	std::string name;
	bool active;
	bool absolute;
	int linesSize;
	std::string* lines;

protected:
};

#endif // _Module_H
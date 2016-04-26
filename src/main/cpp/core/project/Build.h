#include <string>
#include "Module.h"

class Build
{
private:
public:
	int preSize;
	std::string* pre;
	struct lines
	{
		std::string compile;
		int modulesSize;
		Module* modules;
		int flagsSize;
		std::string* flags;
		int libsSize;
		std::string* libs;
	}
	mainline;
	int postSize;
	std::string* post;

protected:
};
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
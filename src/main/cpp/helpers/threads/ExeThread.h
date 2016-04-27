#include "fox-1.6/fx.h"
#include <iostream>
#include <fstream>

class ExeThread: public FXThread
{
  public:
	std::ofstream myfile;
	FILE *fp;
	std::string engage;
    bool done;
    ExeThread();
	void closeStreams();
    virtual FXint run();
};
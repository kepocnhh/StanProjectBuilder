#include "fox-1.6/fx.h"
#include <iostream>
#include <fstream>

class ExeThread: public FXThread
{
  public:
	std::string engage;
    bool done;
    ExeThread();
    virtual FXint run();
};
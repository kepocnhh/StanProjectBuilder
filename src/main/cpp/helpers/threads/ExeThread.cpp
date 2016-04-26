#include "ExeThread.h"

ExeThread::ExeThread():FXThread()
{

}

FXint ExeThread::run()
{
	std::ofstream myfile;
	myfile.open ("test.txt");
	FILE *fp;
	char var[1024];
	fp = popen(engage.c_str(), "r");
	while (fgets(var, sizeof(var), fp) != NULL) 
	{
		myfile << var;
	}
	pclose(fp);
	myfile.close();
  done=true;
  return 1;
}
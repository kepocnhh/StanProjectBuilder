#include "ExeThread.h"

ExeThread::ExeThread():FXThread()
{
	done = false;
}

FXint ExeThread::run()
{
	myfile.open("log");
	char var[1024];
	fp = popen(engage.c_str(), "r");
	while (fgets(var, sizeof(var), fp) != NULL) 
	{
		myfile << var;
	}
	closeStreams();
	done=true;
	return 1;
}
void ExeThread::closeStreams()
{
	pclose(fp);
	myfile.close();
	done = true;
}
#include "fox-1.6/fx.h"
#include <windows.h>
#include "json/json.h"
#include "Const.h"
#include "ui/windows/MainWindow.h"

void test()
{
	//ShellExecute(NULL, "open", "C:\\WINDOWS\\system32\\cmd.exe","/c \"start C:\\Users\\toha\\Downloads\\StanProjectBuilder\\test.txt\"", NULL, SW_SHOW );
    //ShellExecute(0, "open", "cmd.exe", "start C:/Users/toha/Downloads/StanProjectBuilder/test.txt", 0, SW_HIDE);
	//WinExec("C:/Users/toha/Downloads/StanProjectBuilder/test.txt",SW_SHOW);
	//testJson();
	//testExecuteCommand();
}

int main(int argc, char *argv[])
{
    FXApp application(Const::app_name, Const::company_name);
    application.init(argc, argv);
    MainWindow *main = new MainWindow(&application);
    application.create();
    SetWindowPos((HWND)main->id(), HWND_TOPMOST,
                 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE);
	test();
	return application.run();
}
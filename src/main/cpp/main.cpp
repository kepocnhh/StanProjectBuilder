#include "fox-1.6/fx.h"
#include <windows.h>
#include "json/json.h"
#include "Const.h"
#include "helpers/files/FilesHelper.h"
#include "ui/windows/MainWindow.h"

void testExecuteCommand()
{
  int i;
  i=system ("del blabla.txt");
}
void testJson()
{
	std::string line = FilesHelper::getTextFromFile("E:/Downloads/settings.spb");
	json::Object jsonData = json::Deserialize(line);
	//json::Object jsonData = json::Deserialize(FilesHelper::getTextFromFile("C:/Users/toha/develop/cpp/StanProjectBuilder/StanProjectBuilder/settings.spb"));
	if (jsonData.HasKey("project") && jsonData["project"].GetType() == json::ObjectVal)
	{
		json::Object project = jsonData["project"].ToObject();
		std::string rootDir = project["rootDir"].ToString();
	}
	else
	{
		exit(0);
	}
}

void test()
{
	testJson();
	//testExecuteCommand();
}

int main(int argc, char *argv[])
{
    FXApp application(Const::app_name, Const::company_name);
    application.init(argc, argv);
    MainWindow *main = new MainWindow(&application);
    application.create();
    // main->show(PLACEMENT_SCREEN);
    SetWindowPos((HWND)main->id(), HWND_TOPMOST,
                 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE);
	test();
    return application.run();
}
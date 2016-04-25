#include <sstream>
#include <string>
#include <fstream>
#include "fox-1.6/fx.h"
#include <windows.h>
#include "json/json.h"
#include "Const.h"
#include "ui/windows/MainWindow.h"

void testJson()
{
    std::fstream file("C:/Users/toha/Downloads/test.json");
	std::stringstream ss;
	std::string line;
	while (getline(file, line))
	{
		ss << line;
	}
	file.close();
	json::Object jsonData = json::Deserialize(ss.str());
	if (jsonData.HasKey("bool") && jsonData["bool"].GetType() == json::BoolVal)
	{
		bool boolObject = jsonData["bool"].ToBool();
		if(boolObject)
		{
			
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		exit(0);
	}
}

void test()
{
	testJson();
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
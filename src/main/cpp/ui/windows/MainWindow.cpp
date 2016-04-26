#include "MainWindow.h"
//#include <windows.h>
#include "../../Const.h"
#include "../../helpers/files/FilesHelper.h"
//#include <iostream>
//#include <fstream>

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_OPEN_FILE, MainWindow::openFileButtonClick),
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_BUILD, MainWindow::buildButtonClick)
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *a) : FXMainWindow(a, a->getAppName(), NULL, NULL,
            DECOR_NONE | DECOR_TITLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
{
	engage = "";
	mainSwitcher = new FXSwitcher(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame* openFileFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(openFileFrame, Const::open_file_button_name, NULL, this, MainWindow::ID_BUTTON_OPEN_FILE);

    FXHorizontalFrame* buildFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(buildFrame, Const::build_button_name, NULL, this, MainWindow::ID_BUTTON_BUILD);
}

void MainWindow::create()
{
	FXMainWindow::create();
	show(PLACEMENT_SCREEN);
}

void showErrorMessageDialog(FXMainWindow* mainWindow, json::Object error)
{
	std::string message = error["message"].ToString();
	std::string type = error["type"].ToString();
	FXMessageBox::error(mainWindow, MBOX_OK, type.c_str(), message.c_str());
}

void MainWindow::switchToBuild(json::Object projectJson, json::Object buildJson)
{
	try
	{
		project = ProjectBuilder::getProjectFromJson(projectJson, buildJson);
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return;
	}
	//
	FXSelector updatemessage=FXSEL(SEL_COMMAND,FXSwitcher::ID_OPEN_SECOND);
	mainSwitcher->handle(this,updatemessage,NULL);
}
void MainWindow::openFileChooseDialog()
{
    FXString filename = FXFileDialog::getOpenFilename(this, "Open", "settings.spb", "All Files(*.*)");
    if(filename.empty())
    {
		json::Object jsonDataErrorOpenfile = json::Deserialize(FilesHelper::error_open_file);
		showErrorMessageDialog(this, jsonDataErrorOpenfile["error"].ToObject());
		return;
    }
	std::string line = FilesHelper::getTextFromFile(filename.text());
	json::Object jsonData;
	try
	{
		jsonData = json::Deserialize(line);
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return;
	}
	if(jsonData.HasKey("error"))
	{
		showErrorMessageDialog(this, jsonData["error"].ToObject());
		return;
	}
	else if(!jsonData.HasKey("project") || jsonData["project"].GetType() != json::ObjectVal)
	{
		json::Object jsonDataErrorIncorrectFile = json::Deserialize(Project::error_incorrect_file);
		showErrorMessageDialog(this, jsonDataErrorIncorrectFile["error"].ToObject());
		return;
	}
	switchToBuild(jsonData["project"].ToObject(), jsonData["build"].ToObject());
}

long MainWindow::openFileButtonClick(FXObject* sender, FXSelector, void*)
{
	openFileChooseDialog();
    return 1;
}
long MainWindow::buildButtonClick(FXObject *, FXSelector, void *)
{
	if(engage.size() == 0)
	{
		engage = ProjectBuilder::buildProject(project);
		//engage = "/c \"" + engage + "\"";
	}
	//ShellExecute(NULL, "open", "C:\\WINDOWS\\system32\\cmd.exe", engage.c_str(), NULL, SW_SHOW);
	int i;
	i=system(engage.c_str());
	/*
	std::ofstream myfile;
	myfile.open ("test.txt");
	myfile << engage;
	myfile.close();
	*/
	//FXMessageBox::error(this, MBOX_OK, "Build", engage.c_str());
    return 1;
}
#include "MainWindow.h"
#include <windows.h>
#include "../../Const.h"
#include "../../helpers/files/FilesHelper.h"
#include "../../res/drawable/Drawable.h"
#include <iostream>
#include <fstream>

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
	mainSwitcher = new FXSwitcher(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame* openFileFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(openFileFrame, Const::open_file_button_name, NULL, this, MainWindow::ID_BUTTON_OPEN_FILE);

    FXHorizontalFrame* buildFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(buildFrame, Const::build_button_name, NULL, this, MainWindow::ID_BUTTON_BUILD);

    FXBitmap* circle = new FXBitmap(a, NULL);
    circle->setData(Drawable::circle_progress_bar);
	FXBitmapFrame* circleProgress = new FXBitmapFrame(mainSwitcher,circle,FRAME_THICK);
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
    settingsFileName = filename.text();
	std::string line = FilesHelper::getTextFromFile(settingsFileName.c_str());
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
	if(checkJsonData(jsonData))
	{
		switchToBuild(jsonData["project"].ToObject(), jsonData["build"].ToObject());
	}
}
bool MainWindow::checkJsonData(json::Object jsonData)
{
	if(jsonData.HasKey("error"))
	{
		showErrorMessageDialog(this, jsonData["error"].ToObject());
		return false;
	}
	else if(!jsonData.HasKey("project") || jsonData["project"].GetType() != json::ObjectVal)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return false;
	}
	else if(!jsonData.HasKey("build") || jsonData["build"].GetType() != json::ObjectVal)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return false;
	}
	return true;
}

long MainWindow::openFileButtonClick(FXObject* sender, FXSelector, void*)
{
	openFileChooseDialog();
    return 1;
}
long MainWindow::buildButtonClick(FXObject *, FXSelector, void *)
{
	std::string line = FilesHelper::getTextFromFile(settingsFileName.c_str());
	json::Object jsonData;
	try
	{
		jsonData = json::Deserialize(line);
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return 1;
	}
	if(!checkJsonData(jsonData))
	{
		return 1;
	}
	try
	{
		project = ProjectBuilder::getProjectFromJson(jsonData["project"].ToObject(), jsonData["build"].ToObject());
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return 1;
	}
	std::string engage;
	engage = ProjectBuilder::buildProject(project);
	//if(engage.size() == 0)
	//{
		//engage = ProjectBuilder::buildProject(project);
		//engage = "/c \"" + engage + "\"";
	//}
	//engage += " >> test.txt";

	engage += " 2>&1";
	std::ofstream myfile;
	myfile.open ("test.txt");
  FILE *fp;
  //FILE *outputfile;
  char var[1024];

	fp = popen(engage.c_str(), "r");
	while (fgets(var, sizeof(var), fp) != NULL) 
	{
		//printf("%s", var);
		myfile << var;
	}
	pclose(fp);

  //outputfile = fopen("test.txt", "a");
  //fprintf(outputfile,"%s\n",var);
  //fclose(outputfile);
	myfile.close();

	/*
	FILE *fp = popen(engage.c_str(), "r");
	char buf[1024];
	std::string inputLine = "";
	while (fgets(buf, 1024, fp))
	{
		inputLine += buf;
	}
	fclose(fp);
	*/

	//FXMessageBox::error(this, MBOX_OK, "caption", inputLine.c_str());
	//engage = "/c \"" + engage + "\"";
	//ShellExecute(NULL, "open", "cmd.exe", engage.c_str(), NULL, SW_HIDE);
	
	//system(engage.c_str());
	
	/*
	std::ofstream myfile;
	myfile.open ("test.txt");
	myfile << inputLine;
	myfile.close();
	*/

	//FXMessageBox::error(this, MBOX_OK, "Build", engage.c_str());
    return 1;
}
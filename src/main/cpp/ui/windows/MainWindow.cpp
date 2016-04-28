#include "MainWindow.h"

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_OPEN_FILE, MainWindow::openFileButtonClick),
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_BUILD, MainWindow::buildButtonClick),
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_RUN, MainWindow::runButtonClick),
	FXMAPFUNC(SEL_TIMEOUT, MainWindow::ID_EXECUTE_COMAND, MainWindow::executeCommand)
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *a) : FXMainWindow(a, a->getAppName(), NULL, NULL,
            DECOR_NONE | DECOR_TITLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
{
	mainSwitcher = new FXSwitcher(this,LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame* openFileFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(openFileFrame, Const::open_file_button_name, NULL, this, MainWindow::ID_BUTTON_OPEN_FILE);

    FXHorizontalFrame* commandsFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(commandsFrame, Const::build_button_name, NULL, this, MainWindow::ID_BUTTON_BUILD);
    //new FXButton(commandsFrame, Const::run_button_name, NULL, this, MainWindow::ID_BUTTON_RUN);

    /*
    FXBitmap* circle = new FXBitmap(a, NULL);
	circle->create();
    circle->setData(Drawable::test);
    circle->render();
	FXBitmapFrame* circleProgress = new FXBitmapFrame(mainSwitcher,circle);
	*/
	new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
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

void MainWindow::switchToBuild(json::Object projectJson, json::Array runCommands)
{
	try
	{
		project = ProjectBuilder::getProjectFromJson(projectJson, runCommands);
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
std::string getModulesString(CommandModule* command, Project::settings projectSettings)
{
	std::string engage = "";
	if(command->modulesSize == 8)
	{
		engage += "8";
	}
	else if(command->modulesSize > 8)
	{
		engage += ">8";
	}
	else if(command->modulesSize < 8)
	{
		engage += "<8";
	}
		engage += command->name;
	if(command->modules[0].active)
	{
		engage += "active";
	}
	else
	{
		engage += "!!!active";
	}
	//MODULES
	for(int i=0; i < command->modulesSize; i++)
	{
		/*
		if(!command->modules[i].active)
		{
			continue;
		}
		std::string prefix = "";
		if(!command->modules[i].absolute)
		{
			prefix = projectSettings.rootDir + "/";
		}
		for(int j=0; j < command->modules[i].linesSize; j++)
		{
			engage += " " + prefix + command->modules[i].lines[j];
		}
		*/
	}
	//EXECUTE_FILE_NAME
	if(projectSettings.type == TypesHelper::PROJECT_TYPE_CPP)
	{
		engage += " -o " + projectSettings.rootDir + "/" + projectSettings.name;
	}
	return engage;
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
		showErrorMessageDialog(this, json::Deserialize(Project::error_deserialize_file)["error"].ToObject());
		return;
	}
	if(checkJsonData(jsonData))
	{
		switchToBuild(
			jsonData["project"].ToObject(),
			jsonData["runCommands"].ToArray());
	}
	//
	FXMessageBox::error(this, MBOX_OK, "modules", getModulesString(((CommandModule *)&project->runCommands[0]), project->projectSettings).c_str());
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
	else if(!jsonData.HasKey("runCommands") || jsonData["runCommands"].GetType() != json::ArrayVal)
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
long MainWindow::executeCommand(FXObject *, FXSelector, void *)
{
	if(!exeThread->done)
	{
		getApp()->addTimeout(this,ID_EXECUTE_COMAND,100);
	}
	else
	{
		mainSwitcher->handle(this,FXSEL(SEL_COMMAND,FXSwitcher::ID_OPEN_SECOND),NULL);
	}
	return 1;
}
long MainWindow::runButtonClick(FXObject *, FXSelector, void *)
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
		project = ProjectBuilder::getProjectFromJson(
			jsonData["project"].ToObject(),
			jsonData["runCommands"].ToArray());
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return 1;
	}
	/*
	TerminateProcess(pi.hProcess, 0);
	std::string engage;
	engage = ProjectBuilder::runProject(project);
	STARTUPINFO si;
	memset((void *)&si,0,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	memset((void *)&pi,0,sizeof(PROCESS_INFORMATION));
	CreateProcess(NULL, const_cast<LPSTR>(engage.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	*/
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
		showErrorMessageDialog(this, json::Deserialize(Project::error_deserialize_file)["error"].ToObject());
		return 1;
	}
	if(!checkJsonData(jsonData))
	{
		return 1;
	}
	try
	{
		project = ProjectBuilder::getProjectFromJson(
			jsonData["project"].ToObject(),
			jsonData["runCommands"].ToArray());
	}
	catch (const std::runtime_error& e)
	{
		showErrorMessageDialog(this, json::Deserialize(Project::error_incorrect_file)["error"].ToObject());
		return 1;
	}
	mainSwitcher->handle(this,FXSEL(SEL_COMMAND,FXSwitcher::ID_OPEN_THIRD),NULL);
    exeThread = new ExeThread();
	std::string engage = "";
	engage = ProjectBuilder::buildCommand(&project->runCommands[0], project->projectSettings);
	engage += " 2>&1";
    exeThread->engage = engage;
    exeThread->start();
    getApp()->addTimeout(this,ID_EXECUTE_COMAND,100);
    return 1;
}
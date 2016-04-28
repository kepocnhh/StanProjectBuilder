#include <windows.h>
#include <iostream>
#include <fstream>
#include "fox-1.6/fx.h"
#include "json/json.h"
#include "../../helpers/files/FilesHelper.h"
#include "../../helpers/project/ProjectBuilder.h"
#include "../../helpers/threads/ExeThread.h"
#include "../../Const.h"

class MainWindow : public FXMainWindow
{
FXDECLARE(MainWindow)

private:
	//
	FXSwitcher* mainSwitcher;
	FXHorizontalFrame *commandsFrame;
	//
	ExeThread *exeThread;
	Project* project;
	std::string settingsFileName;
	PROCESS_INFORMATION pi;
	//
	void openFileChooseDialog();
	bool checkJsonData(json::Object);
	void switchToBuild(json::Object projectJson, json::Array runCommands);

public:
	enum
	{
		ID_BUTTON_OPEN_FILE = FXMainWindow::ID_LAST,
		ID_BUTTON_BUILD,
		ID_BUTTON_RUN,
		ID_EXECUTE_COMAND
	};
	long openFileButtonClick(FXObject *, FXSelector, void *);
	long buildButtonClick(FXObject *, FXSelector, void *);
	long runButtonClick(FXObject *, FXSelector, void *);
	long executeCommand(FXObject *, FXSelector, void *);
    MainWindow(FXApp *a);
    virtual void create();

protected:
    MainWindow() { }
};
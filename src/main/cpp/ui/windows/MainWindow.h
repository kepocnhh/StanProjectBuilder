#include "fox-1.6/fx.h"
#include "json/json.h"
#include "../../helpers/project/ProjectBuilder.h"

class MainWindow : public FXMainWindow
{
FXDECLARE(MainWindow)

private:
	FXSwitcher* mainSwitcher;
	//FXHorizontalFrame *openFileFrame;
	//FXHorizontalFrame *buildFrame;
	Project* project;
	std::string settingsFileName;
	void openFileChooseDialog();
	bool checkJsonData(json::Object);
	void switchToBuild(json::Object, json::Object);

public:
	enum
	{
		ID_BUTTON_OPEN_FILE = FXMainWindow::ID_LAST,
		ID_BUTTON_BUILD
	};
	long openFileButtonClick(FXObject *, FXSelector, void *);
	long buildButtonClick(FXObject *, FXSelector, void *);
    MainWindow(FXApp *a);
    virtual void create();

protected:
    MainWindow() { }
};
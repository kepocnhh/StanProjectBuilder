#include "MainWindow.h"
#include "../../Const.h"

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

	openFileFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(openFileFrame, Const::open_file_button_name, NULL, this, MainWindow::ID_BUTTON_OPEN_FILE);

    buildFrame = new FXHorizontalFrame(mainSwitcher,DECOR_NONE);
    new FXButton(buildFrame, Const::build_button_name, NULL, this, MainWindow::ID_BUTTON_BUILD);
}

void MainWindow::create()
{
	FXMainWindow::create();
	show(PLACEMENT_SCREEN);
}

void MainWindow::openFileChooseDialog()
{
    FXString filename = FXFileDialog::getOpenFilename(this, "Open", "settings.spb", "All Files(*.*)");
    if(!filename.empty())
    {
		FXSelector updatemessage=FXSEL(SEL_COMMAND,FXSwitcher::ID_OPEN_SECOND);
		mainSwitcher->handle(this,updatemessage,NULL);
    }
}

long MainWindow::openFileButtonClick(FXObject* sender, FXSelector, void*)
{
	openFileChooseDialog();
    return 1;
}
long MainWindow::buildButtonClick(FXObject *, FXSelector, void *)
{
    return 1;
}
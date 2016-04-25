#include "MainWindow.h"
#include "../../Const.h"

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

FXDEFMAP(MainWindow) MainWindowMap[] = {
	FXMAPFUNC(SEL_COMMAND, MainWindow::ID_BUTTON_BUILD, MainWindow::buildButtonClick)
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *a) : FXMainWindow(a, a->getAppName(), NULL, NULL,
            DECOR_NONE | DECOR_TITLE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
{
    new FXButton(this, Const::build_button_name, NULL, this, MainWindow::ID_BUTTON_BUILD);
}

void MainWindow::create()
{
	FXMainWindow::create();
	show(PLACEMENT_SCREEN);
}

void openFileChooseDialog(FXWindow* owner)
{
	//new FXFileDialog(owner, "FXFileDialog");
    FXString filename = FXFileDialog::getOpenFilename(owner, "Open", "suggestedname.ext", "All Files(*.*)");
    if(!filename.empty())
    {
		FXMessageBox::error(owner, MBOX_OK, "caption", filename.text());
    }
}

long MainWindow::buildButtonClick(FXObject *, FXSelector, void *)
{
	//exit(0);
	openFileChooseDialog(this);
    return 1;
}
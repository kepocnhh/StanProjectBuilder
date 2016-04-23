#include "fox-1.6/fx.h"

class MainWindow : public FXMainWindow
{
FXDECLARE(MainWindow)

private:

public:
	enum
	{
		ID_BUTTON_BUILD = FXMainWindow::ID_LAST
	};
	long buildButtonClick(FXObject *, FXSelector, void *);
    MainWindow(FXApp *a);
    virtual void create();

protected:
    MainWindow() { }
};
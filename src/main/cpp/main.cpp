#include "fox-1.6/fx.h"
#include <windows.h>
#include "Const.h"
#include "ui/windows/MainWindow.h"

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
    return application.run();
}
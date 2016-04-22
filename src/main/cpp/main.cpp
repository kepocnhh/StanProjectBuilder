#include "fox-1.6/fx.h"
#include "Const.h"
#include "ui/windows/MainWindow.h"

int main(int argc, char *argv[])
{
  FXApp application("Hello", "FoxTest");
  application.init(argc, argv);
  MainWindow *main=new MainWindow(&application);
  new FXButton(main, Const::app_name, NULL, &application, FXApp::ID_QUIT);
  application.create();
  main->show(PLACEMENT_SCREEN);
  return application.run();
}
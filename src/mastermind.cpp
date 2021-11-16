#include <iostream>

#include <gtkmm/application.h>

#include "MainWindow.h"

int main(int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.mastermind");

  MainWindow mastermind;

  //Shows the window and returns when it is closed.
  return app->run(mastermind);
}

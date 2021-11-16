/*
 * MainWindow.h
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
	public:
		MainWindow();
		virtual ~MainWindow();

	private:
		Gtk::Box m_mainBox;
		Gtk::Toolbar m_toolbar;
		Gtk::Box m_bordBox;
		Gtk::Statusbar m_statusbar;

};

#endif /* SRC_MAINWINDOW_H_ */

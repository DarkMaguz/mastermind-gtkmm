/*
 * MainWindow.h
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <gtkmm.h>

#include <map>

#include "PlayerBoard.h"
#include "Computer.h"
#include "Human.h"
#include "MasterMind.h"

class MainWindow : public Gtk::Window
{
	public:
		MainWindow();
		virtual ~MainWindow();

	protected:
		void buildToolbar(void);
		void onToolbarNewGame(void);
		void onToolbarQuit(void);

		void onGameStateChanged(const uint8_t& newState);

	private:
		Gtk::Box m_mainBox;
		Gtk::Toolbar *m_toolbar;
		Gtk::Box m_boardBox;
		Gtk::Statusbar m_statusbar;
		Glib::RefPtr<Gtk::Builder> m_refBuilder;

		typedef std::pair<const Glib::ustring, Human*> t_player;

		std::map<const Glib::ustring, Human*> m_players;

		MasterMind m_masterMind;

		Computer* m_computer;

};

#endif /* SRC_MAINWINDOW_H_ */

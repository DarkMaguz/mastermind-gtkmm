/*
 * MainWindow.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "MainWindow.h"
#include "MasterMind.h"

MainWindow::MainWindow() :
	m_mainBox(Gtk::ORIENTATION_VERTICAL),
	m_bordBox(Gtk::ORIENTATION_HORIZONTAL)
{
	set_title("Mastermind");
	set_default_size(800, 600);

	m_mainBox.pack_start(m_toolbar, Gtk::PACK_SHRINK);
	m_mainBox.pack_start(m_bordBox, Gtk::PACK_EXPAND_WIDGET);
	m_mainBox.pack_start(m_statusbar, Gtk::PACK_SHRINK);

	t_player computerPlayer = t_player("Computer", Gtk::make_managed<PlayerBoard>("Computer", &m_masterMind));
	t_player humanPlayer = t_player("human", Gtk::make_managed<PlayerBoard>("human", &m_masterMind));

	m_players.insert(computerPlayer);
	m_players.insert(humanPlayer);

	m_bordBox.pack_start(*computerPlayer.second, Gtk::PACK_EXPAND_WIDGET);
	m_bordBox.pack_start(*humanPlayer.second, Gtk::PACK_EXPAND_WIDGET);

	add(m_mainBox);
	show_all_children();
	//computerPlayer.second->begin();
}

MainWindow::~MainWindow()
{
}


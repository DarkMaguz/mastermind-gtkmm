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
	m_boardBox(Gtk::ORIENTATION_HORIZONTAL)
{
	set_title("Mastermind");
	set_default_size(800, 600);

	m_mainBox.pack_start(m_toolbar, Gtk::PACK_SHRINK);
	m_mainBox.pack_start(m_boardBox, Gtk::PACK_EXPAND_WIDGET);
	m_mainBox.pack_start(m_statusbar, Gtk::PACK_SHRINK);

	m_computer = Gtk::make_managed<Computer>("Computer", &m_masterMind);
	t_player humanPlayer = t_player("human", Gtk::make_managed<Human>("human", &m_masterMind));

	m_players.insert(humanPlayer);

	m_boardBox.pack_start(*m_computer, Gtk::PACK_EXPAND_WIDGET);
	m_boardBox.pack_start(*humanPlayer.second, Gtk::PACK_EXPAND_WIDGET);

	m_masterMind.restart();

	add(m_mainBox);
	show_all_children();
}

MainWindow::~MainWindow()
{
}


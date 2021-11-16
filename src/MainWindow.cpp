/*
 * MainWindow.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "MainWindow.h"
#include "PlayerBoard.h"

MainWindow::MainWindow() :
	m_mainBox(Gtk::ORIENTATION_VERTICAL),
	m_bordBox(Gtk::ORIENTATION_HORIZONTAL)
{
	set_title("Mastermind");
	set_default_size(800, 600);

	m_mainBox.pack_start(m_toolbar, Gtk::PACK_SHRINK);
	m_mainBox.pack_start(m_bordBox, Gtk::PACK_EXPAND_WIDGET);
	m_mainBox.pack_start(m_statusbar, Gtk::PACK_SHRINK);

	m_bordBox.pack_start(*Gtk::make_managed<PlayerBoard>("Computer"), Gtk::PACK_EXPAND_WIDGET);
	m_bordBox.pack_start(*Gtk::make_managed<PlayerBoard>("Human"), Gtk::PACK_EXPAND_WIDGET);

	add(m_mainBox);
	show_all_children();
}

MainWindow::~MainWindow()
{
}


/*
 * MainWindow.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "MainWindow.h"
#include "MasterMind.h"

#include <iostream>

MainWindow::MainWindow() :
	m_mainBox(Gtk::ORIENTATION_VERTICAL),
	m_toolbar(nullptr),
	m_boardBox(Gtk::ORIENTATION_HORIZONTAL),
	m_refBuilder(Gtk::Builder::create())
{
	set_title("Mastermind");
	set_default_size(800, 600);

	buildToolbar();
	m_mainBox.pack_start(*m_toolbar, Gtk::PACK_SHRINK);
	m_mainBox.pack_start(m_boardBox, Gtk::PACK_EXPAND_WIDGET);
	m_mainBox.pack_start(m_statusbar, Gtk::PACK_SHRINK);

	m_computer = Gtk::make_managed<Computer>("Computer", &m_masterMind);
	t_player humanPlayer = t_player("human", Gtk::make_managed<Human>("human", &m_masterMind));

	m_players.insert(humanPlayer);

	m_boardBox.pack_start(*m_computer, Gtk::PACK_EXPAND_WIDGET);
	m_boardBox.pack_start(*humanPlayer.second, Gtk::PACK_EXPAND_WIDGET);

	// Connect to MasterMind game state changed signal.
	m_masterMind.signalGameStateChanged().connect(sigc::mem_fun(*this, &MainWindow::onGameStateChanged));
	//m_masterMind.restart();

	add(m_mainBox);
	show_all_children();
	m_boardBox.set_visible(false);
}

MainWindow::~MainWindow()
{
	if (m_toolbar)
		delete m_toolbar;
}

void MainWindow::buildToolbar(void)
{

	// Connect toolbar button action signals.
	auto refActionGroup = Gio::SimpleActionGroup::create();
	refActionGroup->add_action("newgame", sigc::mem_fun(*this, &MainWindow::onToolbarNewGame));
	refActionGroup->add_action("quit", sigc::mem_fun(*this, &MainWindow::onToolbarQuit));
	insert_action_group("toolbar", refActionGroup);

	// Load toolbar buttons from xml file.
	Glib::ustring uiToolbarButtons;
	auto ioc = Glib::IOChannel::create_from_file("gui.xml", "r");
	ioc->read_to_end(uiToolbarButtons);
	ioc->close();

	// Remove unused template variables.
	Glib::ustring templateName = "$menuItems$";
	auto templatePos = uiToolbarButtons.find(templateName);
	uiToolbarButtons.replace(templatePos, templateName.size(), "");

  try
  {
    m_refBuilder->add_from_string(uiToolbarButtons);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building toolbar failed: " <<  ex.what();
  }

  m_refBuilder->get_widget("toolbar", m_toolbar);
  if (!m_toolbar)
  	std::cerr << "GtkToolbar not found!";
  else
  	m_toolbar->set_toolbar_style(Gtk::TOOLBAR_BOTH);

}

void MainWindow::onToolbarNewGame(void)
{
	if (m_masterMind.gameState() == MasterMind::INPROGRESS)
	{
		// Ask user if they really would like to start a new game and thus terminate the existing one.
		Gtk::MessageDialog dialog(*this,
				"Are you sure about starting a new game and thus loosing the progress of the current game?",
				false,
				Gtk::MESSAGE_QUESTION,
				Gtk::BUTTONS_OK_CANCEL);
		if (dialog.run() == Gtk::RESPONSE_OK)
			m_masterMind.restart();
	}
	else
	{
		m_masterMind.restart();
	}
}

void MainWindow::onToolbarQuit(void)
{
	if (m_masterMind.gameState() == MasterMind::INPROGRESS)
	{
		// Ask user if they really would like to quit the game.
		Gtk::MessageDialog dialog(*this,
				"Are you sure about quitting the game?",
				false,
				Gtk::MESSAGE_QUESTION,
				Gtk::BUTTONS_OK_CANCEL);
		if (dialog.run() == Gtk::RESPONSE_OK)
			hide();
	}
	else
	{
		hide();
	}
}

void MainWindow::onGameStateChanged(const uint8_t& newState)
{
	switch (newState) {
		case MasterMind::STOPED:
			m_boardBox.set_visible(false);
			break;
		case MasterMind::INPROGRESS:
			m_boardBox.set_visible(true);
			break;
		case MasterMind::ENDED:
		{
			// Display the score/stats and ask if the user would like a new game?
			Gtk::MessageDialog dialog(*this,
					"Would you like to play again?",
					false,
					Gtk::MESSAGE_QUESTION,
					Gtk::BUTTONS_OK_CANCEL);
			if (dialog.run() == Gtk::RESPONSE_OK)
				m_masterMind.restart();
			else
				m_boardBox.set_visible(false);
			break;
		}
		default:
			std::cout << "MainWindow::onGameStateChanged --> default" << std::endl;
			break;
	}
}


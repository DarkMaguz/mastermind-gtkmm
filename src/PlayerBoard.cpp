/*
 * PlayerBoard.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "PlayerBoard.h"
#include "ScorePeg.h"

#include <gtkmm.h>

#include <iostream>
#include <exception>
#include <fstream>

PlayerBoard::PlayerBoard(const Glib::ustring& playerName, MasterMind *mm) :
	Gtk::Frame(playerName),
	m_playerVBox(Gtk::ORIENTATION_HORIZONTAL),
	m_guessButtonBox(Gtk::ORIENTATION_HORIZONTAL),
	m_scoreButtonBox(Gtk::ORIENTATION_HORIZONTAL),
	m_refBuilder(Gtk::Builder::create()),
	m_pMenuPopup(nullptr),
	m_playerName(playerName),
	m_masterMind(mm)
{
	set_label_align(0.25);

	m_playerVBox.set_valign(Gtk::ALIGN_CENTER); // Set the boxes in the center.
	m_playerVBox.pack_start(m_guessButtonBox, Gtk::PACK_START, 5);
	m_playerVBox.pack_start(m_scoreButtonBox, Gtk::PACK_START, 5);

	// Add score left to right.
	m_scoreButtonBox.set_halign(Gtk::ALIGN_START);

	mm->signalGameStateChanged().connect(sigc::mem_fun(*this, &PlayerBoard::onGameStateChanged));

	buildColorMenu();
	//if (m_playerName != "Computer")

	add(m_playerVBox);
	show_all_children();
}

PlayerBoard::~PlayerBoard()
{
	for (auto button : m_guessButtons)
		delete button;
}

void PlayerBoard::begin(void)
{
	if (m_playerName == "Computer")
	{
		//m_playerVBox.set_visible(false);
	}
}

void PlayerBoard::onGuessClicked(const uint8_t guessNumber)
{
	if (m_masterMind->gameState() != MasterMind::INPROGRESS)
		return;

	// Set the current guess needed by onSelectColor.
	m_currentGuessPeg = guessNumber;

	// Make sure the popup menu have something to attach to.
  if(!m_pMenuPopup->get_attach_widget())
    m_pMenuPopup->attach_to_widget(*this);

  // Make the menu pop up.
  if(m_pMenuPopup)
    m_pMenuPopup->popup_at_widget(m_guessButtons.at(guessNumber)->guessPeg,
    		Gdk::GRAVITY_SOUTH, Gdk::GRAVITY_NORTH, nullptr);
}

void PlayerBoard::onSelectColor(const MasterMind::color color)
{
	GuessButtonInfo *gButton = m_guessButtons.at(m_currentGuessPeg);

	gButton->guessPeg->setColor(MasterMind::cssColorMap[color]);

	MasterMind::score score = m_masterMind->guess(m_currentGuessPeg, color);
	//m_score.push_back(score);
	//m_scoreButtonBox.add(*Gtk::make_managed<ScorePeg>(score));
	//m_scoreButtonBox.set_visible(true);
	gButton->scorePeg->setScore(score);
	//m_scoreButtonBox.show_all_children();
}

void PlayerBoard::onGameStateChanged(const uint8_t& newState)
{
	std::cout << "PlayerBoard::onGameStateChanged: " << std::endl;
	std::cout << "\tplayerName: " << m_playerName << std::endl;
	std::cout << "\tnewState: " << std::to_string(newState) << std::endl;

	switch (newState) {
		case MasterMind::STOPED:

			break;
		case MasterMind::INPROGRESS:

			break;
		case MasterMind::ENDED:
			revealCode();
			// Disconnect signals so that guess buttons wont react to clicks anymore.
			/*if (!m_masterMind->guessesLeft())
				for (auto button : m_guessButtons)
					button->connection.disconnect();*/
			break;
		default:
			break;
	}
}

void PlayerBoard::buildColorMenu(void)
{
	// Connect popup menu action signals to onSelectColor parsing the chosen color.
	auto refActionGroup = Gio::SimpleActionGroup::create();

	for (uint8_t i = 0; i < MasterMind::cssColorMap.size(); i++)
		refActionGroup->add_action(MasterMind::cssColorMap[i],
				sigc::bind(sigc::mem_fun(*this, &PlayerBoard::onSelectColor), MasterMind::color(i)));
	insert_action_group("color-menu", refActionGroup);

	// Load popup menu template from xml file.
	Glib::ustring uiColorMenu;
	auto ioc = Glib::IOChannel::create_from_file("color-menu.xml", "r");
	ioc->read_to_end(uiColorMenu);
	ioc->close();

	// Add items to the menu.
	Glib::ustring uiColorMenuItems;
	for (uint8_t i = 0; i < MasterMind::cssColorMap.size(); i++)
	{
		auto color = MasterMind::cssColorMap[i];
		uiColorMenuItems.append(
				"<item>"
				"<attribute name='label'>"
						+ color +
					"</attribute>"
					"<attribute name='action'>"
						"color-menu." + color +
					"</attribute>"
				"</item>"
				);
	}
	Glib::ustring templateName = "$menuItems$";
	auto templatePos = uiColorMenu.find(templateName);
	uiColorMenu.replace(templatePos, templateName.size(), uiColorMenuItems);

	// Add color menu to builder.
	try
	{
		m_refBuilder->add_from_string(uiColorMenu);
	}
	catch (const Glib::Error& e)
	{
		std::cerr << "Building color menu failed: " <<  e.what();
	}

	// Build the menu.
  auto object = m_refBuilder->get_object("color-menu");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  m_pMenuPopup = std::make_unique<Gtk::Menu>(gmenu);
  if(!gmenu)
  	std::cout << "GMenu not found!" << std::endl;
}

void PlayerBoard::createPegs(void)
{
//	// Create guess pegs and score pegs.
//	for (uint8_t i = 0; i < 5; i++)
//	{
//		GuessButtonInfo* gButton = new GuessButtonInfo;
//		m_guessButtons.push_back(gButton);
//
//		gButton->guessPeg = Gtk::make_managed<Peg>();
//		gButton->guessPeg->set_name(m_playerName + "-guessButton" + std::to_string(i));
//		gButton->connection = gButton->guessPeg->signal_clicked()
//				.connect(sigc::bind(sigc::mem_fun(*this, &PlayerBoard::onGuessClicked), i));
//
//		m_guessButtonBox.add(*gButton->guessPeg);
//
//		gButton->scorePeg = Gtk::make_managed<ScorePeg>();
//
//		m_scoreButtonBox.add(*gButton->scorePeg);
//		gButton->scorePeg->setScore(MasterMind::NONE);
//	}
}

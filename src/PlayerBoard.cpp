/*
 * PlayerBoard.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "PlayerBoard.h"

#include <iostream>
#include <exception>
#include <fstream>

PlayerBoard::PlayerBoard(const Glib::ustring& playerName, MasterMind *mm) :
	Gtk::Frame(playerName),
	m_playerVBox(Gtk::ORIENTATION_VERTICAL),
	m_playerHBox(Gtk::ORIENTATION_HORIZONTAL),
	m_guessButtonBox(Gtk::ORIENTATION_HORIZONTAL),
	m_scoreButtonBox(Gtk::ORIENTATION_HORIZONTAL),
	m_refBuilder(Gtk::Builder::create()),
	m_pMenuPopup(nullptr),
	m_playerName(playerName),
	m_masterMind(mm)
{
	set_label_align(0.25);

	m_playerVBox.pack_start(m_playerHBox, Gtk::PACK_EXPAND_WIDGET, 5);
	m_playerHBox.pack_start(m_guessButtonBox, Gtk::PACK_EXPAND_WIDGET, 5);
	m_playerHBox.pack_start(m_scoreButtonBox, Gtk::PACK_EXPAND_WIDGET, 5);

	buildColorMenu();

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
		m_playerVBox.set_visible(false);
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

	// Create guess buttons.
	for (uint8_t i = 0; i < 5; i++)
	{
		GuessButtonInfo* gButton = new GuessButtonInfo;

		gButton->button = Gtk::make_managed<Gtk::Button>();
		gButton->button->set_name(m_playerName + "-guessButton" + std::to_string(i));
		gButton->styleContext = gButton->button->get_style_context();
		gButton->connection = gButton->button->signal_button_press_event()
				.connect(sigc::bind(sigc::mem_fun(*this, &PlayerBoard::onGuessClicked), i));

		m_guessButtons.push_back(gButton);

		m_guessButtonBox.add(*gButton->button);
	}
}

bool PlayerBoard::onGuessClicked(GdkEventButton* buttonEvent, const uint8_t guessNumber)
{
  if( (buttonEvent->type == GDK_DOUBLE_BUTTON_PRESS) && (buttonEvent->button == 1) )
  {
  	// Set the current guess needed by onSelectColor.
  	m_currentGuess = guessNumber;

  	// Make sure the popup menu have something to attach to.
    if(!m_pMenuPopup->get_attach_widget())
      m_pMenuPopup->attach_to_widget(*this);

    // Make the menu pop up.
    if(m_pMenuPopup)
      m_pMenuPopup->popup_at_pointer((GdkEvent*)buttonEvent);

    return true;
  }
  else
    return false;
}

void PlayerBoard::onSelectColor(const MasterMind::color color)
{
	std::cout << "m_currentGuess: " << std::to_string(m_currentGuess) << std::endl;
	std::cout << "onSelectColor: " << std::to_string(color) << std::endl;

	GuessButtonInfo *gButton = m_guessButtons.at(m_currentGuess);

  // Create CSS prvider.
	auto css = Gtk::CssProvider::create();
	css->load_from_data("#" + m_playerName + "-guessButton" + std::to_string(m_currentGuess) +
			"{background-image: none; background-color: " + MasterMind::cssColorMap[color] + ";}");

	// Set the chosen color.
	gButton->styleContext->add_provider_for_screen(Gdk::Screen::get_default(),
			css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// Disconnect signal so that the button wont react to clicks anymore.
	gButton->connection.disconnect();

	m_masterMind->guess(m_currentGuess, color);
}

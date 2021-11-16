/*
 * PlayerBoard.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#include "PlayerBoard.h"

#include <stdlib.h>

PlayerBoard::PlayerBoard(const Glib::ustring& playerName) :
	Gtk::Frame(playerName),
	m_playerVBox(Gtk::ORIENTATION_VERTICAL),
	m_playerHBox(Gtk::ORIENTATION_HORIZONTAL),
	m_guessButtonBox(Gtk::ORIENTATION_HORIZONTAL),
	m_scoreButtonBox(Gtk::ORIENTATION_HORIZONTAL)
{
	set_label_align(0.25);

	m_playerVBox.pack_start(m_playerHBox, Gtk::PACK_EXPAND_WIDGET, 5);

	m_playerHBox.pack_start(m_guessButtonBox, Gtk::PACK_EXPAND_WIDGET, 5);
	m_playerHBox.pack_start(m_scoreButtonBox, Gtk::PACK_EXPAND_WIDGET, 5);

	auto css = Gtk::CssProvider::create();
	css->load_from_data("#guessButton {background-image: none;}");

	for (uint8_t i = 0; i < 5; i++) {
		Gtk::Button* button = Gtk::make_managed<Gtk::Button>();
		button->set_name("guessButton");
		button->override_background_color(Gdk::RGBA("red"));
		button->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(),
				css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

		m_scoreButtons.push_back(button);

		m_guessButtonBox.add(*button);
	}

	add(m_playerVBox);
}

PlayerBoard::~PlayerBoard()
{
}


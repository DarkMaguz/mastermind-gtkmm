/*
 * Computer.cpp
 *
 *  Created on: Nov 19, 2021
 *      Author: magnus
 */

#include <gtkmm.h>
#include "Computer.h"

Computer::Computer(const Glib::ustring& playerName, MasterMind *mm) :
	PlayerBoard(playerName, mm)
{
	createPegs();
}

Computer::~Computer()
{
}

void Computer::createPegs(void)
{
	// Create guess pegs and score pegs.
	for (uint8_t i = 0; i < 5; i++)
	{
		GuessButtonInfo* gButton = new GuessButtonInfo;
		m_guessButtons.push_back(gButton);

		gButton->guessPeg = Gtk::make_managed<Peg>();
		gButton->guessPeg->set_name(m_playerName + "-guessButton" + std::to_string(i));

		m_guessButtonBox.add(*gButton->guessPeg);
	}
}

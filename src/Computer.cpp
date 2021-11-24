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
		PegInfo* gButton = new PegInfo;
		m_guessButtons.push_back(gButton);

		gButton->scorePeg = nullptr;
		gButton->colorPeg = Gtk::make_managed<Peg>();
		gButton->colorPeg->set_name(m_playerName + "-guessButton" + std::to_string(i));

		m_guessButtonBox.add(*gButton->colorPeg);
	}
}

void Computer::revealCode(void)
{
	// Loop through the guess buttons and assign the secret color code to each peg.
	auto colorIt = m_masterMind->getMasterSequence().begin();
	for (auto pegIt : m_guessButtons)
	{
		pegIt->colorPeg->setColor(MasterMind::cssColorMap[*colorIt]);
		colorIt++;
	}
}

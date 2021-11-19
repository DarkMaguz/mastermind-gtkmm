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
	// TODO Auto-generated constructor stub
	
}

Computer::~Computer()
{
	// TODO Auto-generated destructor stub
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
		gButton->connection = gButton->guessPeg->signal_clicked()
				.connect(sigc::bind(sigc::mem_fun(*this, &PlayerBoard::onGuessClicked), i));

		m_guessButtonBox.add(*gButton->guessPeg);

		gButton->scorePeg = Gtk::make_managed<ScorePeg>();

		m_scoreButtonBox.add(*gButton->scorePeg);
		gButton->scorePeg->setScore(MasterMind::NONE);
	}
}

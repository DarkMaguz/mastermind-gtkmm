/*
 * Human.cpp
 *
 *  Created on: Nov 20, 2021
 *      Author: magnus
 */

#include <gtkmm.h>

#include "Human.h"

Human::Human(const Glib::ustring& playerName, MasterMind *mm) :
	PlayerBoard(playerName, mm)
{
	m_submitGuessButton.signal_clicked().connect(sigc::mem_fun(*this, &Human::onSubmitGuess));
	createPegs();
}

Human::~Human()
{
}

void Human::createPegs(void)
{
	// Create guess pegs and score pegs.
	for (uint8_t i = 0; i < 5; i++)
	{
		PegInfo* gButton = new PegInfo;
		m_guessButtons.push_back(gButton);

		gButton->colorPeg = Gtk::make_managed<Peg>();
		// Make the colorPeg identifiable.
		gButton->colorPeg->set_name(m_playerName + "-guessButton" + std::to_string(i));
		gButton->connection = gButton->colorPeg->signal_clicked()
				.connect(sigc::bind(sigc::mem_fun(*this, &PlayerBoard::onGuessClicked), i));

		m_guessButtonBox.add(*gButton->colorPeg);

		gButton->scorePeg = Gtk::make_managed<ScorePeg>();

		m_scorePegBox.add(*gButton->scorePeg);
		gButton->scorePeg->setScore(MasterMind::NONE);
	}
}

void Human::onSubmitGuess(void)
{
	MasterMind::t_colorSequnence seq;
	for (auto guess : m_guessButtons)
		seq.push_back(guess->colorPeg->getColor());
	MasterMind::t_score score = m_masterMind->guess(seq);

	uint8_t it = 0;
	for (auto guess : m_guessButtons)
		guess->scorePeg->setScore(score[it++]);

	m_score.push_back(score);
}

/*
 * MasterMind.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "MasterMind.h"

#include <algorithm>
#include <iostream>

std::array<const std::string, 6> const MasterMind::cssColorMap = {
			"red", "green", "blue", "yellow", "black", "white"
		};

MasterMind::MasterMind() :
	m_gameState(STOPED),
	m_guessCouter(0)
{
}

MasterMind::MasterMind(t_colorSequnence& masterSequence) :
	m_gameState(STOPED),
	m_masterSequence(masterSequence),
	m_guessCouter(0)
{
	if (masterSequence.size() != 5)
		throw "Wrong sized sequence!\n\tGot " + std::to_string(masterSequence.size()) + " expected 5";
}

MasterMind::~MasterMind()
{
}

void MasterMind::restart(void)
{
	m_guessCouter = 0;
	genNewMasterSequence();
	changeState(INPROGRESS);
}

const MasterMind::score MasterMind::guess(const uint8_t& position, const color guess)
{
	std::cout << "MasterMind::guess: guessesLeft():" << std::to_string(guessesLeft()) << std::endl;
	if (guessesLeft() < 0)
		throw "The maximum number of guesses has been exceeded!";

	if (position > 4)
		throw "Invalid position!\n\tGot " + std::to_string(position) + " expected position to be in range 0-4";

	const bool hasColor = std::any_of(m_masterSequence.begin(),
			m_masterSequence.end(),
			[&](color c){return c == guess;});

	if (guessesLeft() <= 0)
	{
		std::cout << "MasterMind::guess: changeState(ENDED);" << std::endl;
		changeState(ENDED);
	}

	m_guessCouter++;

	if (hasColor) {
		if (m_masterSequence.at(position) == guess)
			return score::HIT;
		else
			return score::MISS;
	} else {
		return score::NONE;
	}
}

const int8_t MasterMind::guessesLeft(void) const
{
	return 2 - m_guessCouter;
}

const MasterMind::state MasterMind::gameState(void) const
{
	return m_gameState;
}

sigc::signal<void, MasterMind::state> MasterMind::signalGameStateChanged(void)
{
	return m_signalGameStateChanged;
}

void MasterMind::changeState(const state& newState)
{
	m_gameState = newState;
	m_signalGameStateChanged.emit(newState);
}

void MasterMind::genNewMasterSequence(void)
{
	m_masterSequence.clear();

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 4);

	for (int i = 0; i < 5; i++)
		m_masterSequence.push_back(color(distribution(generator)));
}

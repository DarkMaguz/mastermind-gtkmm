/*
 * MasterMind.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "MasterMind.h"
#include <algorithm>

MasterMind::MasterMind()
{
	genMasterSequence();
}

MasterMind::MasterMind(t_colorSequnence& masterSequence) :
	m_masterSequence(masterSequence)
{
	if (masterSequence.size() != 5)
		throw "Wrong sized sequence!\n\tGot " + std::to_string(masterSequence.size()) + " expected 5";
}

MasterMind::~MasterMind()
{
}

void MasterMind::genMasterSequence(void)
{
	m_masterSequence.clear();

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 4);

	for (int i = 0; i < 5; i++)
		m_masterSequence.push_back(color(distribution(generator)));
}

const score MasterMind::guess(const uint8_t& position, const color guess) const
{
	if (position > 4)
		throw "Invalid position!\n\tGot " + std::to_string(position) + " expected position to be in range 0-4";

	const bool hasColor = std::any_of(m_masterSequence.begin(),
			m_masterSequence.end(),
			[&](color c){return c == guess;});

	if (hasColor) {
		if (m_masterSequence.at(position) == guess)
			return score::HIT;
		else
			return score::MISS;
	} else {
		return score::NONE;
	}
}

/*
 * MasterMind.h
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#ifndef SRC_MASTERMIND_H_
#define SRC_MASTERMIND_H_

#include <vector>
#include <string>
#include <random>

enum color {
	RED = 1,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	YELLOW
};

enum score {
	HIT = 1,
	MISS,
	NONE
};

typedef std::vector<color> t_colorSequnence;

class MasterMind
{
	public:
		MasterMind();
		MasterMind(t_colorSequnence& masterSequence);
		virtual ~MasterMind();

		const score guess(const uint8_t& position, const color guess) const;

	private:
		t_colorSequnence m_masterSequence;
};

#endif /* SRC_MASTERMIND_H_ */

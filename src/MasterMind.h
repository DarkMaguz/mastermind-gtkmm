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
#include <array>

class MasterMind
{
	public:
		enum color {
			RED = 0,
			GREEN,
			BLUE,
			YELLOW,
			BLACK,
			WHITE
		};

		enum score {
			HIT = 1,
			MISS,
			NONE
		};

		typedef std::vector<color> t_colorSequnence;

		static std::array<const std::string, 6> const cssColorMap;

	public:
		MasterMind();
		MasterMind(t_colorSequnence& masterSequence);
		virtual ~MasterMind();

		void genNewMasterSequence(void);
		const score guess(const uint8_t& position, const color guess) const;

	private:
		t_colorSequnence m_masterSequence;
};

#endif /* SRC_MASTERMIND_H_ */

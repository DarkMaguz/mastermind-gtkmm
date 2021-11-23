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

#include <sigc++/sigc++.h>

class Computer;

class MasterMind
{
		friend Computer;
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

		enum state {
			STOPED = 0,
			INPROGRESS,
			ENDED
		};

		typedef std::vector<color> t_colorSequnence;
		static std::array<const std::string, 6> const cssColorMap;

	public:
		MasterMind();
		MasterMind(t_colorSequnence& masterSequence);
		virtual ~MasterMind();

		void restart(void);
		const score guess(const uint8_t& position, const color guess);

		const int8_t guessesLeft(void) const;
		const state gameState(void) const;

		sigc::signal<void, state> signalGameStateChanged(void);

	protected:
		const t_colorSequnence& getMasterSequence(void) const;

	private:
		void changeState(const state& newState);
		void genNewMasterSequence(void);

		state m_gameState;
		t_colorSequnence m_masterSequence;
		int8_t m_guessCouter;

		sigc::signal<void, state> m_signalGameStateChanged;
};

#endif /* SRC_MASTERMIND_H_ */

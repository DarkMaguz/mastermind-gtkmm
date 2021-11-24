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
			VOID = 0,
			RED,
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
		typedef std::vector<MasterMind::score> t_score;
		static std::array<const std::string, 7> const cssColorMap;

	public:
		MasterMind();
		MasterMind(t_colorSequnence& masterSequence);
		virtual ~MasterMind();

		void restart(void);
		const t_score guess(const t_colorSequnence& guess);

		const int8_t guessesLeft(void) const;
		const state gameState(void) const;

		sigc::signal<void, state> signalGameStateChanged(void);

	protected:
		const t_colorSequnence& getMasterSequence(void) const;

	private:
		void changeState(const state& newState);
		void genNewMasterSequence(void);
		const score evaluateGuess(const uint8_t& position, const color& guess) const;

		state m_gameState;
		t_colorSequnence m_masterSequence;
		int8_t m_guessCouter;

		sigc::signal<void, state> m_signalGameStateChanged;
};

#endif /* SRC_MASTERMIND_H_ */

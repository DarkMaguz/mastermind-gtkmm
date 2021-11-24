/*
 * Human.h
 *
 *  Created on: Nov 20, 2021
 *      Author: magnus
 */

#ifndef SRC_HUMAN_H_
#define SRC_HUMAN_H_

#include <gtkmm.h>

#include "PlayerBoard.h"

class Human: public PlayerBoard
{
	public:
		Human(const Glib::ustring& playerName, MasterMind *mm);
		virtual ~Human();

	private:
		void createPegs(void);

		void onSubmitGuess(void);
};

#endif /* SRC_HUMAN_H_ */

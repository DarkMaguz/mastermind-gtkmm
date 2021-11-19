/*
 * Computer.h
 *
 *  Created on: Nov 19, 2021
 *      Author: magnus
 */

#ifndef SRC_COMPUTER_H_
#define SRC_COMPUTER_H_

#include "PlayerBoard.h"
#include <gtkmm.h>

class Computer: public PlayerBoard
{
	public:
		Computer(const Glib::ustring& playerName, MasterMind *mm);
		virtual ~Computer();

	private:

		virtual void createPegs(void);
};

#endif /* SRC_COMPUTER_H_ */

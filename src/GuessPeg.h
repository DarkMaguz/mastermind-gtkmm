/*
 * GuessPeg.h
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#ifndef SRC_GUESSPEG_H_
#define SRC_GUESSPEG_H_

#include "Peg.h"

class GuessPeg: public Peg
{
	public:
		GuessPeg();
		virtual ~GuessPeg();

	protected:
		virtual void setColor(const Glib::ustring& color);
};

#endif /* SRC_GUESSPEG_H_ */

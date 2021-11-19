/*
 * ScorePeg.h
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#ifndef SRC_SCOREPEG_H_
#define SRC_SCOREPEG_H_

#include "Peg.h"
#include "MasterMind.h"

class ScorePeg: public Peg
{
	public:
		ScorePeg(const MasterMind::score& score);
		virtual ~ScorePeg();

	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

	private:
		const MasterMind::score m_score;
};

#endif /* SRC_SCOREPEG_H_ */

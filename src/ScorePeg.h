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

#include <gtkmm.h>

struct rgbColor
{
	double red;
	double green;
	double blue;
};

class ScorePeg: public Gtk::DrawingArea
{
	public:
		ScorePeg();
		virtual ~ScorePeg();

		void setScore(const MasterMind::score& score);

	protected:
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

	private:
		MasterMind::score m_score;
};

#endif /* SRC_SCOREPEG_H_ */

/*
 * Peg.h
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#ifndef SRC_PEG_H_
#define SRC_PEG_H_

#include <gtkmm.h>

#include "MasterMind.h"

class Peg : public Gtk::Button
{
	public:
		Peg();
		virtual ~Peg();

		void setColor(const MasterMind::color& color);
		const MasterMind::color& getColor(void) const;

	protected:
		//virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

		MasterMind::color m_color;

};

#endif /* SRC_PEG_H_ */

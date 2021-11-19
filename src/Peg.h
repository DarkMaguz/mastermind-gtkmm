/*
 * Peg.h
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#ifndef SRC_PEG_H_
#define SRC_PEG_H_

#include <gtkmm.h>

class Peg : public Gtk::Button
{
	public:
		Peg();
		virtual ~Peg();

		void setColor(const Glib::ustring& color);

	protected:
		//virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

};

#endif /* SRC_PEG_H_ */

/*
 * PlayerBoard.h
 *
 *  Created on: Nov 16, 2021
 *      Author: magnus
 */

#ifndef SRC_PLAYERBOARD_H_
#define SRC_PLAYERBOARD_H_

#include <gtkmm.h>

#include <vector>

class PlayerBoard : public Gtk::Frame
{
	public:
		PlayerBoard(const Glib::ustring& playerName);
		virtual ~PlayerBoard();

	private:
		Gtk::Box m_playerVBox;
		Gtk::Box m_playerHBox;

		Gtk::ButtonBox m_guessButtonBox;
		Gtk::ButtonBox m_scoreButtonBox;

		std::vector<Gtk::Button*> m_scoreButtons;


};

#endif /* SRC_PLAYERBOARD_H_ */

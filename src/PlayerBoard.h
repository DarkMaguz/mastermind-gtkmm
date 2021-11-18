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
#include "MasterMind.h"

struct GuessButtonInfo
{
		Gtk::Button* button;
		sigc::connection connection;
		Glib::RefPtr<Gtk::StyleContext> styleContext;
};

class PlayerBoard : public Gtk::Frame
{
	public:
		PlayerBoard(const Glib::ustring& playerName, MasterMind *mm);
		virtual ~PlayerBoard();

		void begin(void);

	private:
		bool onGuessClicked(GdkEventButton* button_event, const uint8_t guessNumber);
		void onSelectColor(const Glib::ustring color);

		void buildColorMenu(void);

		Gtk::Box m_playerVBox;
		Gtk::Box m_playerHBox;

		Gtk::ButtonBox m_guessButtonBox;
		Gtk::ButtonBox m_scoreButtonBox;

		std::vector<GuessButtonInfo *> m_guessButtons;

		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		std::unique_ptr<Gtk::Menu> m_pMenuPopup;

		uint8_t m_currentGuess;
		Glib::ustring m_playerName;

		MasterMind* m_masterMind;
};

#endif /* SRC_PLAYERBOARD_H_ */

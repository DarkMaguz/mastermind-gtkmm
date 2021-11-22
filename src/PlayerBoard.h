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
#include "Peg.h"
#include "ScorePeg.h"

struct GuessButtonInfo
{
		Peg* guessPeg;
		ScorePeg* scorePeg;
		sigc::connection connection;
};

class Computer;
class Human;
class PlayerBoard : public Gtk::Frame
{
		friend Computer;
		friend Human;
	public:
		PlayerBoard(const Glib::ustring& playerName, MasterMind *mm);
		virtual ~PlayerBoard();

		void begin(void);

	protected:
		void onGuessClicked(const uint8_t guessNumber);
		void onSelectColor(const MasterMind::color color);

		void onGameStateChanged(const uint8_t& newState);

		void buildColorMenu(void);
		virtual void createPegs(void);

		Gtk::Box m_playerVBox;

		Gtk::ButtonBox m_guessButtonBox;
		Gtk::Box m_scoreButtonBox;

		std::vector<GuessButtonInfo*> m_guessButtons;

		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		std::unique_ptr<Gtk::Menu> m_pMenuPopup;

		uint8_t m_currentGuessPeg;
		Glib::ustring m_playerName;

		MasterMind* m_masterMind;

		std::vector<MasterMind::score> m_score;
};

#endif /* SRC_PLAYERBOARD_H_ */

/*
 * ScorePeg.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "ScorePeg.h"

ScorePeg::ScorePeg(const MasterMind::score& score) :
	m_score(score)
{
	show_all_children();
}

ScorePeg::~ScorePeg()
{
}

bool ScorePeg::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	struct rgb {
		double red;
		double green;
		double blue;
	} color;

	if (m_score == MasterMind::HIT)
		color = {255, 255, 255};
	else if (m_score == MasterMind::MISS)
		color = {0, 0, 0};
	else
		set_visible(false);

  // This is where we draw on the window
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  const int lesser = MIN(width, height);

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  // outline thickness changes with window size
  cr->set_line_width(lesser * 0.02);
  // now draw a circle
  cr->save();
  cr->arc(xc, yc, lesser / 4.0, 0.0, 2.0 * M_PI); // full circle
  //cr->set_source_rgba(0.0, 0.0, 0.8, 0.6);    // partially translucent
  cr->set_source_rgb(color.red, color.green, color.blue);
  cr->fill_preserve();
  cr->restore();  // back to opaque black
  cr->stroke();

	return false;
}

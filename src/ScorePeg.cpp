/*
 * ScorePeg.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "ScorePeg.h"

ScorePeg::ScorePeg() :
	m_score(MasterMind::NONE)
{
	show_all_children();
}

ScorePeg::~ScorePeg()
{
}

void ScorePeg::setScore(const MasterMind::score& score)
{
	m_score = score;
	// Request redrawing of widget.
	queue_draw();
}

bool ScorePeg::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	rgbColor color;

	if (m_score == MasterMind::HIT)
		color = {1., 1., 1.};
	else if (m_score == MasterMind::MISS)
		color = {0., 0., 0.};
	else
	{
		reset_style();
		return false;
	}

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

  cr->set_source_rgb(color.red, color.green, color.blue);
  cr->fill_preserve();
  cr->restore();  // back to opaque black
  cr->stroke();

	return false;
}

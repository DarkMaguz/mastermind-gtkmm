/*
 * Peg.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "Peg.h"

#include <iostream>

Peg::Peg() :
	m_color(MasterMind::color::VOID)
{
	show_all_children();
}

Peg::~Peg()
{
}

//bool Peg::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
//{
//	/*
//  // This is where we draw on the window
//  Gtk::Allocation allocation = get_allocation();
//  const int width = allocation.get_width();
//  const int height = allocation.get_height();
//  const int lesser = MIN(width, height);
//
//  // coordinates for the center of the window
//  int xc, yc;
//  xc = width / 2;
//  yc = height / 2;
//
//  // outline thickness changes with window size
//  cr->set_line_width(lesser * 0.02);
//  // now draw a circle
//  cr->save();
//  cr->arc(xc, yc, lesser / 4.0, 0.0, 2.0 * M_PI); // full circle
//  cr->set_source_rgba(0.0, 0.0, 0.8, 0.6);    // partially translucent
//  cr->fill_preserve();
//  cr->restore();  // back to opaque black
//  cr->stroke();*/
//
//	return false;
//}

const MasterMind::color& Peg::getColor(void) const
{
	return m_color;
}

void Peg::setColor(const MasterMind::color& color)
{
	bool hasColor = color != MasterMind::color::VOID;
	m_color = color;
	// Create CSS string.
	Glib::ustring bgColor = hasColor ? " background-color: " + MasterMind::cssColorMap[color] +";" : "";
	Glib::ustring css = Glib::ustring::compose(
			"#%1.mmClass {background-image: none;%2}",
			get_name(), bgColor);

  // Create CSS prvider.
	auto cssProvider = Gtk::CssProvider::create();
	cssProvider->load_from_data(css);

	// Set the chosen color.
	auto styleContext = get_style_context();
	styleContext->add_provider_for_screen(Gdk::Screen::get_default(),
			cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// Add or remove the style depending on whether or not a color was set.
	if (hasColor)
		styleContext->add_class("mmClass");
	else
		styleContext->remove_class("mmClass");
}

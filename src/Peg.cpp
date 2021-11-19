/*
 * Peg.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include "Peg.h"

#include <iostream>

Peg::Peg()
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

void Peg::setColor(const Glib::ustring& color)
{
	auto styleContext = get_style_context();

	std::cout << "get_name: " << get_name() << std::endl;

  // Create CSS prvider.
	auto css = Gtk::CssProvider::create();
	css->load_from_data("#" + get_name() +
			"{background-image: none; background-color: " + color + ";}");

	// Set the chosen color.
	styleContext->add_provider_for_screen(Gdk::Screen::get_default(),
			css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

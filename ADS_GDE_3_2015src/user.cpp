// User.cpp : header file
//solitär
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "user.h"
#include "graphics\graphicfunctions.h"
#include <iostream>
#include <fstream>
#include <string>

#include "graphic.h"

#ifndef Spielfunktionen.h
#include "Spielfunktionen.h"
#endif

#ifndef __Klassen__
#include "Klassen.h"
#endif

#ifndef __k7scan2__
#include "k7scan2.h"
#endif 

#ifndef __data_file__
#include "data_file.h"
#endif

#ifndef Eingabe_Ausgabe.h
#include	"Eingabe_Ausgabe.h"
#endif // !Eingabe_Ausgabe.h

#ifndef __window__
#include "window.h"
#endif

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif



void user_main()
{
	//fenster anlegen
	window win;
	win.wide = 700;
	win.height = 600;

	set_windowpos(0, 0, win.wide, win.height);	//windowsfenster öffnen
	set_drawarea(win.wide, win.height);		// Setzen des Zeichenbereiches arbeitsfeld

	win.x_mouse = 0;
	win.y_mouse = 0;

	//karten anlegen
	const	size_t	length = 52;
	vector<Card>	cards(length);

	vector<field_stack> field_stack(12);

	for (size_t i = 4; i < 11; i++)
	{
		field_stack[i].set_stack_count(i - 3);
		cout << "the number of cards which are allowed to stay at stack:" << i << " is:" << field_stack[i].get_stack_count() << "\n";
	}

	field_stack[11].set_stack_count(24);

	initialize_cards(cards);
	get_arr(cards);
	//read_data(field_stack);

	for (size_t yy = 0; yy < 4; yy++)
	{
		for (size_t ii = 0; ii < 13; ii++)
		{
			field_stack[yy].field.push_back(&cards[13 * yy + ii]);
		}
	}

	austeilen(field_stack);

	newwindow(win);

	win.first_click_card = 100;
	win.first_click_stack = 13;
	win.second_click_card = 100;
	win.second_click_stack = 13;

	while (1)
	{
		win.second_click_card = 100;
		win.second_click_stack = 13;

		button(win, field_stack, cards);

		click_window(field_stack, win, cards);
		playing_rules(field_stack, win);
		click_window(field_stack, win, cards);

		//cout <<"click on stack" << win.click_stack << "\n" << "card" << win.click_card <<"\n";
		updatescr();

		while (!mouseclick(&win.x_mouse, &win.y_mouse) == 1){}

		if (StopProcess())break;

	}



}
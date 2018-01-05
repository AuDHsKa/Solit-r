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

void	gewonnen()
{
	cout << "*************************************************************\n";
	cout << "*************************************************************\n";
	cout << "				\n Herzlichen Glueckwunsch!\n";
	cout << "				\n Sie haben das Spiel gewonnen!\n";
	cout << "*************************************************************\n";
	cout << "*************************************************************\n";
}


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
	vector<Card*>	copycards(length);

	vector<field_stack> field_stack(12);

	//for (size_t i = 4; i < 11; i++)
	//{
	//	field_stack[i].set_stack_count(i - 3);
	//}

	//field_stack[11].set_stack_count(24);

	initialize_field(field_stack);
	initialize_cards(cards);
	initialize_target(field_stack, cards);

	get_arr(cards);

	//read_data(field_stack);

	//copy_cards(cards, copycards);
	mein_austeilen(field_stack);

	//austeilen(field_stack);

	newwindow(win);

	win.first_click_card = 100;
	win.first_click_stack = 13;
	win.second_click_card = 100;
	win.second_click_stack = 13;

#ifdef Auswerten
	//size_t	n = 10;
	//size_t	gewonnen = 0;

	//while (n)
	//{
	//	gewonnen += solvealgo(field_stack, win);
	//	//delete_data(field_stack);
	//	//clear_field(field_stack);
	//	//copy_cards(cards, copycards);
	//	//mein_austeilen(field_stack, copycards);
	//	austeilen(field_stack, cards);
	//	n--;
	//}

	//cout << "Es wurden:" << gewonnen << "Spiele gewonnen!";
	statistik(field_stack, win, cards);
#endif // !Auswerten



	while (1)
	{
		win.second_click_card = 100;
		win.second_click_stack = 13;

		button(win, field_stack, cards);

		click_window(field_stack, win, cards);
		window_move(field_stack, win);
		click_window(field_stack, win, cards);

		//win.test++;

		updatescr();

		if ((field_stack[0].field.size() == 13) &&
			(field_stack[1].field.size() == 13) &&
			(field_stack[2].field.size() == 13) &&
			(field_stack[3].field.size() == 13))
		{
			gewonnen();
		}


		while (!mouseclick(&win.x_mouse, &win.y_mouse) == 1){}

		if (StopProcess())break;
		

		
	}



}
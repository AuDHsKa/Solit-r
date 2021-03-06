﻿// User.cpp : header file
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

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

void user_main()
{
	//fenster anlegen
	window win;
	win.wide = 700;
	win.height = 600;
	win.statistik = 0;

	// GDE funktionen
	set_windowpos(0, 0, win.wide, win.height);	//windowsfenster öffnen
	set_drawarea(win.wide, win.height);		// Setzen des Zeichenbereiches arbeitsfeld

	// Mausklicks initialisieren
	win.x_mouse = 0;
	win.y_mouse = 0;

	// karten anlegen
	const	size_t	length = 52;
	vector<Card>	cards(length);
	
	// Kartenstapel anlegen (4 Zielfelder + 7 Spielfelder + Kartendeck = 12)
	vector<field_stack> field_stack(12);

	// Initialisierungsroutinen
	initialize_field(field_stack);
	initialize_cards(cards);
	initialize_target(field_stack, cards);

	austeilen(field_stack);

	// neues Spielfeld wird gezeichnen; Grafische Ausgabe
	newwindow(win);

	// Ausgabe für das Logfile
	output("\n\n#################################\n\nDas Programm wurde gestartet\n\n#################################\n\n", "logfile.txt");

	// Hauptroutine
	while (1)
	{
		//win.second_click_card = 100; //reset second mouseclick
		//win.second_click_stack = 13; //reset second mouseclick

		button(win, field_stack, cards); // sourch for a click on buttons
		click_window(field_stack, win); // sourch for a click on stacks
		window_move(field_stack, win); // look for a turn (spielzug)
		click_window(field_stack, win); // draw the window after a move

		// GDE funktion
		updatescr();

		// Überprüfe, ob das Spiel gewonnen wurde
		if (look_for_game_won(field_stack))
		{
			gewonnen();
		}

		// Warten auf ein Mausklick'Event
		while (!mouseclick(&win.x_mouse, &win.y_mouse) == 1){}
		if (StopProcess())break;				
	}
}
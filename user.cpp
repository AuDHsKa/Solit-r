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

//#ifndef __k7scan2__
//#include "k7scan2.h"
//#endif 

#ifndef __data_file__
#include "data_file.h"
#endif


#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif



void user_main()
{
	//fenster anlegen
	int windowswide = 700, windowsheight = 600;
	int x = windowswide;	//mauszeiger startposition
	int y = windowsheight;	//mauszeiger startposition
	set_windowpos(0, 0, windowswide, windowsheight);	//windowsfenster öffnen
	set_drawarea(windowswide, windowsheight);		// Setzen des Zeichenbereiches arbeitsfeld


	//karten anlegen
	const	size_t	length = 52;
	vector<Card>	cards(length);

	stack<Card*>	target_stack[4];
	vector<field_stack> field_stack(8);

	for (size_t i = 0; i < 7; i++)
	{
		field_stack[i].set_stack_count(i + 1);
		field_stack[i].set_stack_NOF(0);
		cout << "the number of cards which are allowed to stay at stack:" << i << " is:" << field_stack[i].get_stack_count() << "\n";
	}

	// set the playing stacks values
	field_stack[7].set_stack_count(24);
	field_stack[7].set_stack_NOF(0);

	initialize_cards(cards);

	for (size_t yy = 0; yy < 4; yy++)
	{
		for (size_t ii = 0; ii < 13; ii++)
		{
			target_stack[yy].push(&cards[13 * yy + ii]);
		}
	}

	cout << "the size of target stack 1 is:" << target_stack[0].size() << "\n";
	cout << "the size of target stack 2 is:" << target_stack[1].size() << "\n";
	cout << "the size of target stack 3 is:" << target_stack[2].size() << "\n";
	cout << "the size of target stack 4 is:" << target_stack[3].size() << "\n";

	austeilen(target_stack, field_stack);

	for (size_t i = 0; i < 7; i++)
	{
		for (size_t ii = 0; ii < field_stack[i].field.size(); ii++)
		{
				cout << "the card number: " << (ii + 1) << "of field number:" << (i + 1) << " colour is " << field_stack[i].field.at(ii)->get_card_colour() << "\n";
				cout << "the card number: " << (ii + 1) << "of field number:" << (i + 1) << " value is " << field_stack[i].field.at(ii)->get_card_value() << "\n";
		}
	}

	
	for (size_t yy = 0; yy < field_stack[7].field.size(); yy++)
	{
		cout << "the card number: " << (yy + 1) << "of field number:" << 8 << " colour is " << field_stack[7].field.at(yy)->get_card_colour() << "\n";
		cout << "the card number: " << (yy + 1) << "of field number:" << 8 << " value is " << field_stack[7].field.at(yy)->get_card_value() << "\n";
	}

		cout << "the size of target stack 1 is:" << target_stack[0].size() << "\n";
		cout << "the size of target stack 2 is:" << target_stack[1].size() << "\n";
		cout << "the size of target stack 3 is:" << target_stack[2].size() << "\n";
		cout << "the size of target stack 4 is:" << target_stack[3].size() << "\n";

		cout << "the size of field stack 1 is:" << field_stack[0].field.size() << "\n";
		cout << "the size of field stack 2 is:" << field_stack[1].field.size() << "\n";
		cout << "the size of field stack 3 is:" << field_stack[2].field.size() << "\n";
		cout << "the size of field stack 4 is:" << field_stack[3].field.size() << "\n";
		cout << "the size of field stack 5 is:" << field_stack[4].field.size() << "\n";
		cout << "the size of field stack 6 is:" << field_stack[5].field.size() << "\n";
		cout << "the size of field stack 7 is:" << field_stack[6].field.size() << "\n";
		cout << "the size of field stack 8 is:" << field_stack[7].field.size() << "\n";
		cout << "the size of field stack 8 is:" << field_stack[7].get_stack_NOF() << "\n";


	while (1)
	{
		newwindow(windowswide, windowsheight);

		for (int i = 0; i < 4; i++)
		{
			w_target_field(x, y, &target_stack[i],i);
		}


		for (int i = 0; i < 7; i++)
		{
			w_field(x, y, field_stack, i);
		}

		w_deck(x, y, field_stack);


		button(x, y, windowswide, windowsheight);
		
		//read_file(cards);


		updatescr();
		while (!mouseclick(&x, &y) == 1) {}

		if (StopProcess())break;

	}



}
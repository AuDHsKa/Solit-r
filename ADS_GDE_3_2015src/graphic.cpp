#include "graphic.h"
#include "stdafx.h"
#include "user.h"
#include "graphics\graphicfunctions.h"
#include <iostream>
#include <fstream>
#include "math.h"

#ifndef Spielfunktionen.h
#include "Spielfunktionen.h"
#endif

#ifndef __Klassen__
#include "Klassen.h"
#endif

#ifndef stack
#include <stack>
#endif

#ifndef __window__
#include "window.h"
#endif

#ifndef __einaus__
#include "Eingabe_Ausgabe.h"
#endif

#ifndef __data_file__
#include "data_file.h"
#endif

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

#define kart RGB(250,240,220)
COLORREF Colref[] = { BLACK, RED, GREEN, BLUE, YELLOW, BROWN };
#define white RGB(250,240,220)



char w_suit[4] = { 'D', 'S', 'H', 'C' }; // Card suit of Diamonds, Spades, Hearts, Clubs

char w_card[14] = { '0','A','2', '3', '4' , '5', '6', '7', '8', '9', 'Z', 'J', 'Q', 'K' }; // Cards value, Z=10, J= Jack, Q=Queen, K=King

  // Card=Karte function: print a card to the window : 
 // bx, by, hx, hy =card position, aktiv= click on this card, karte= number of w_card, w_colour= number of w_suit
void KARTE(int bx, int by, int hx, int hy, bool aktiv, bool hidden, char karte, char w_colour)
{
	int col = GREEN;	//colour for the card_suit (green = emty field)
	int akt = GREEN;	//colour for aktiv (green = emty field)

						//is card activ
	if (aktiv == true)
	{
		akt = YELLOW;
	}
	else
	{
		akt = BLUE;
	}

	//which colour is selected
	if ((w_colour == w_suit[1]) || (w_colour == w_suit[3]))
	{
		col = BLACK;
	}
	else if ((w_colour == w_suit[0]) || (w_colour == w_suit[2]))
	{
		col = RED;
	}
	else
	{
		col = GREEN;
	}

	// if card is not hide(hidden = 1) ___draw card____
	if (hidden == 0)
	{
		if (karte != w_card[0]) //field is not empty
		{
			textbox(bx, by, hx, hy, 22, white, akt, col, LEFT_ALIGN,
				" %c    %c    %c\n %c          %c\n %c    %c    %c\n %c          %c\n %c    %c    %c\n", w_colour, karte, w_colour, karte, karte, w_colour, karte, w_colour, karte, karte, w_colour, karte, w_colour);
		}
		else		//field is empty
		{
			rectangle(bx, by, hx, hy, akt, GREEN);
		}
	}
	else //card is hidden (hidden = 1)
	{
		rectangle(bx, by, hx, hy, BLUE, BLUE);
		ellipse(bx + 10, by + 10, hx - 10, hy - 10, BROWN, BROWN);
	}
}

//draw a single field of target or field, sourch for a mouseclick
int w_field(int x, int y, vector<field_stack>& f1, int feld)
{
	int posnumber = f1[feld].field.size();//number of card on a field
	int abstand;//distanz to the next card
	bool aktiv = false;
	bool hidden = false;
	int mclickcard = 100;//unmögliches ergebnis zum erkenn keine karte ausgewählt
						 //zahlt von 0 ab

	int hx, hy, bx, by;
	//position of field_stack 0-10
	if (feld < 4) // target
	{
		bx = 310 + feld * 100;
		hx = 380 + feld * 100;
		by = 10;
		hy = 120;
		abstand = 0;
	}
	else // field
	{
		bx = 10 + (feld - 4) * 100;
		hx = 80 + (feld - 4) * 100;
		by = 160;
		hy = 270;
		abstand = 20;

	}

	//draw cards on field_stack
	if (posnumber)
	{
		for (int i = 0; i < posnumber; i++)
		{
			if (feld > 3)
			{
				by = 160 + i*abstand;
				hy = 270 + i*abstand;
			}

			hidden = f1[feld].field[i]->is_card_hidden();

			//mausklick auf deck und karte??
			if ((i + 1) < posnumber)
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < (by + abstand))) // auswahl der karte in mitten eines stapels
				{
					cout << "######################################\n";
					cout << "Mausklick auf F" << feld << "\n" << "Karte " << (i + 1) << " ausgewaehlt\n";
					cout << "######################################\n\n";
					mclickcard = i;
					aktiv = true;
				}
			}
			else
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < hy)) // auswahl der letzten karte eines stapels
				{
					cout << "######################################\n";
					cout << "Mausklick auf F" << feld << "\n" << "Karte " << (i + 1) << " ausgewaehlt\n";
					cout << "######################################\n\n";
					mclickcard = i;
					aktiv = true;
				}
			}

			KARTE(bx, by, hx, hy, aktiv, hidden, w_card[f1[feld].field[i]->get_card_value()], w_suit[f1[feld].field[i]->get_card_colour()]);
		}
	}
	else
	{
		if ((bx < x) && (x < hx) && (by < y) && (y < hy))
		{
			cout << "######################################\n";
			cout << "Mausklick auf F" << feld << "\n" << "Karte " << "0 ausgewaehlt\n";
			cout << "######################################\n\n";
			mclickcard = 53;
			aktiv = true;
		}

		KARTE(bx, by, hx, hy, aktiv, 0, w_card[0], w_suit[0]);
	}
	// wenn karte verdeckt dann nehme die nächste umdeckte karte auf dem stapel
	if ((mclickcard != 100) && (mclickcard != 53))
	{
		while (f1[feld].field[mclickcard]->is_card_hidden())
		{
			hidden = f1[feld].field[mclickcard]->is_card_hidden();
			mclickcard++;
			cout << mclickcard;
		}
	}
	return mclickcard;
};

//draw cards on deck
int w_deck(int x, int y, vector<field_stack>& deck)
{
	int posnumber = deck[11].field.size(); //number of card on the deck
	int bx = 10;
	int by = 10;
	int hx = 80;
	int hy = 120;
	bool hidden = false;
	bool deckleer = true; //true no card on deck is hidden
	bool aktiv = false; //aktiv false f+r spätere abfrage
	int mclickcard = 100; //unmögliches ergebnis zum erkenn keine karte ausgewählt
						  //zahlt von 0 ab

						  //draw cards on deck
	if (posnumber) //are cards on deck
	{
		int number_of_unhidden_cards = 0;
		//draw first the card that unhidden, last card is unhidden is on top
		for (int i = (posnumber - 1); i >= 0; i--)
		{
			hidden = deck[11].field[i]->is_card_hidden();

			if (hidden == 0)
			{
				bx = 110;
				hx = 180;
				//draw aktive = mouseclick on closed deck
				if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
				{
					aktiv = true;
				}

				KARTE(bx, by, hx, hy, aktiv, deck[11].field[i]->is_card_hidden(), w_card[deck[11].field[i]->get_card_value()], w_suit[deck[11].field[i]->get_card_colour()]);

			}
			else
			{
				bx = 10;
				hx = 80;
				//draw aktive =mouseclick on open deck
				if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
				{
					aktiv = true;
				}

				KARTE(bx, by, hx, hy, aktiv, deck[11].field[i]->is_card_hidden(), w_card[deck[11].field[i]->get_card_value()], w_suit[deck[11].field[i]->get_card_colour()]);
				deckleer = false;
				number_of_unhidden_cards++;
			}
		}

		//mouseclick on closed deck
		bx = 10;
		hx = 80;
		if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
		{
			cout << "######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = 53;

		}
		//draw if closed deck is empty
		if (deckleer)
		{
			KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
		}

		//mouseclick on open deck
		bx = 110;
		hx = 180;
		if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
		{
			cout << "######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = number_of_unhidden_cards;

		}
	}
	else //no cards on deck
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}

	return mclickcard;
};

//draw botten save, load, restart and solve 
void save(window& win, vector<field_stack>&  field_stack)
{

	int apx = win.wide - 120;//anfangspunkt x
	int apy = win.height - 40; //anfangpunkt y
	int epx = win.wide - 5;//anfangspunkt x
	int epy = win.height - 5; //anfangpunkt y

	if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
		(win.y_mouse > apy) && (win.y_mouse < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Save"));
		cout << "######################################\n";
		cout << "Datei gespeichert\n";
		cout << "######################################\n\n";
		output("Datei gespeichert\n", "logfile.txt");
		write_data(field_stack);
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Save"));
	}
}
void load(window& win, vector<field_stack>&  field_stack)
{

	int apx = win.wide - 245;//anfangspunkt x
	int apy = win.height - 40; //anfangpunkt y
	int epx = win.wide - 130;//anfangspunkt x
	int epy = win.height - 5; //anfangpunkt y

	if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
		(win.y_mouse > apy) && (win.y_mouse < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
		cout << "######################################\n";
		cout << "Datei geladen\n";
		cout << "######################################\n\n";
		delete_data(field_stack);
		read_data(field_stack);
		output("Datei geladen und augefürt\n", "logfile.txt");
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
	}

}
void restart(window& win, vector<field_stack>&  field_stack, vector<Card>& cards)
{
	int apx = 125;//anfangspunkt x
	int apy = win.height - 40; //anfangpunkt y
	int epx = 250;//anfangspunkt x
	int epy = win.height - 5; //anfangpunkt y


	if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
		(win.y_mouse> apy) && (win.y_mouse < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
		cout << "######################################\n";
		cout << "Neustart\n";
		cout << "######################################\n\n";

		delete_data(field_stack);
		initialize_cards(cards);
		for (size_t i = 4; i < 11; i++)
		{
			field_stack[i].set_stack_count(i - 3);
		}
		field_stack[11].set_stack_count(24);
		for (size_t yy = 0; yy < 4; yy++)
		{
			for (size_t ii = 0; ii < 13; ii++)
			{
				field_stack[yy].field.push_back(&cards[13 * yy + ii]);
			}
		}
		austeilen(field_stack);
		output("Restart augefürt\n", "logfile.txt");
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
	}
}
void solve(window& win, vector<field_stack>&  field_stack)
{

	int apx = 5;//anfangspunkt x
	int apy = win.height - 40; //anfangpunkt y
	int epx = 120;//anfangspunkt x
	int epy = win.height - 5; //anfangpunkt y



	if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
		(win.y_mouse > apy) && (win.y_mouse < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Lösen"));

		cout << "######################################\n";
		cout << "Loese Spiel\n";
		cout << "######################################\n\n";
		output("Lösen augefürt\n", "logfile.txt");
		solvealgo(field_stack, win);
		output("Lösen augefürt\n", "logfile.txt");
		//take_card_from_field_to_field(field_stack);

		//take_card_from_deck_to_field(field_stack);
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Lösen"));
	}
}

//new green window
void newwindow(window& win)
{
	rectangle(0, 0, win.wide, win.height, GREEN, GREEN);
}
//neues grünes feld für karten
void newwindow_cards(window& win)
{
	rectangle(0, 0, win.wide-5, win.height-40, GREEN, GREEN);
}
//load button
int button(window& win, vector<field_stack>&  field_stack, vector<Card>& cards)  // maus x, maus y, windowsweite, windowshöhe
{
	load(win, field_stack);
	save(win, field_stack);
	restart(win, field_stack, cards);
	solve(win,  field_stack);

	return 0;
}

//search for a click on a card
void click_window(vector<field_stack>& field_stack, window& win , vector<Card>& cards)
{
	win.second_click_card = 100;	//mouseclick on card_number (100= no card is seleced,)
	win.second_click_stack = 13;	//mouseclick on field_number (0= no stack is seleced)
	int click = 100;			//save mclickcard (so mclick will not be overwritten)

	newwindow_cards(win);

	for (int i = 0; i < 11; i++)
	{
		click = 100;
		click = w_field(win.x_mouse, win.y_mouse, field_stack, i);

		if (click < 100)
		{
			//cout << "mausklick auf feld" << i << "      karte" << click << "\n";
			win.second_click_stack = i;
			win.second_click_card = click;
		}
	}

	click = 100;
	click = w_deck(win.x_mouse, win.y_mouse, field_stack);
	if (click < 100)
	{
		//cout << "mausklick auf deck" << "      karte" << win.click_card << "\n";
		win.second_click_stack = 11; //click on top of deck
		win.second_click_card = click;
	}

}
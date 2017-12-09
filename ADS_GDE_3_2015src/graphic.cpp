﻿#include "graphic.h"
#include "stdafx.h"
#include "user.h"
#include "graphics\graphicfunctions.h"
#include <iostream>
#include <fstream>
#include "math.h"

#ifndef __Klassen__
#include "Klassen.h"
#endif

#ifndef stack
#include <stack>
#endif


#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

#define kart RGB(250,240,220)
COLORREF Colref[] = { BLACK, RED, GREEN, BLUE, YELLOW, BROWN };
#define white RGB(250,240,220)

char w_suit[4] = { 'D', 'S', 'H', 'C' }; // Card suit of Diamonds, Spades, Hearts, Clubs

char w_card[14] = { '0','A','2', '3', '4' , '5', '6', '7', '8', '9', 'Z', 'J', 'Q', 'K' }; // Cards value, Z=10, J= Jack, Q=Queen, K=King

// Card=Karte function is to print a card to the window : 
// bx, by, hx, hy =card position, aktiv= click on this card, karte= number of w_card, w_colour= number of w_suit
void KARTE(int bx, int by, int hx, int hy, bool aktiv, bool hidden, char karte, char w_colour)
{
	int col = GREEN;	//colour for the card_suit (green = emty field)
	int akt = GREEN;	//colour for aktiv (green = emty field)
	int abstand = 20;	//distance to the next card on the field

	if (aktiv == true)//is card activ
	{
		akt = YELLOW;
	}
	else
	{
		akt = BLUE;
	}

	if ((w_colour == w_suit[1]) || (w_colour == w_suit[3]))	//which colour is selected
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

	if (hidden == 0)	//if card is not hide (hidden=1) draw card
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
	else //card is hidden (hidden=1)
	{
		rectangle(bx, by, hx, hy, BLUE, BLUE);
		ellipse(bx + 10, by + 10, hx - 10, hy - 10, BROWN, BROWN);
	}
}  


//draw cards on target_field
int w_target_field(int x, int y, vector<field_stack>& tsp, int feld)
{
	int bx = 310 + feld * 100;
	int hx = 380 + feld * 100;
	int by = 10;
	int hy = 120;

	bool hidden = false;
	bool aktiv = false;
	int mclickcard = 100;//ungültig 

	if ((bx < x) && (x < hx) && (by < y) && (y < hy))
	{
		aktiv = true;
		cout << "######################################\n";
		cout << "Mausklick auf target_stack\n";
		cout << "######################################\n\n";

		mclickcard = 53;
		if (tsp[feld].field.size())
		{
			mclickcard = 1;
		}
	}
	else
	{
		aktiv = false;
	}

	if (tsp[feld].field.size())
	{

		hidden = tsp[feld].field.back()->is_card_hidden();

		KARTE(bx, by, hx, hy, aktiv, hidden, w_card[tsp[feld].field.back()->get_card_value()], w_suit[tsp[feld].field.back()->get_card_colour()]);
	}
	else
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}

	return mclickcard;
};
//draw cards on field
int w_field(int x, int y, vector<field_stack>& f1, int feld)
{
	int	bx = 10 + (feld-4) * 100;
	int	hx = 80 + (feld-4) * 100;
	int	by = 160;
	int	hy = 270;

	int posnumber = f1[feld].field.size();
	int abstand = 20;
	bool aktiv = false;
	bool hidden = false;

	int mclickcard = 100;//unmögliches ergebnis zum erkenn keine karte ausgewählt
					//zahlt von 0 ab


	if (posnumber)
	{
		for (int i = 0; i < posnumber; i++)
		{
			by = 160 + i*abstand;
			hy = 270 + i*abstand;

			hidden = f1[feld].field[i]->is_card_hidden();

			if ((i + 1) < posnumber)
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < (by + abstand)))
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
				if ((bx < x) && (x < hx) && (by < y) && (y < hy))
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

	return mclickcard;
};
//draw cards on deck
int w_deck(int x, int y, vector<field_stack>& deck)
{
	int posnumber = 0;
	int abstand = 20;
	int bx = 10;
	int by = 10;
	int hx = 80;
	int hy = 120;
	bool hidden = false;
	bool deckleer = true; //true für stätere abfrage
	bool aktiv = false; //aktiv false f+r spätere abfrage
	int mclickcard = 100; //ungültige karte

	posnumber = deck[11].field.size();

	if (posnumber) //für nicht inizialisrung
	{
		int c = 0;
		for (int i = (posnumber-1); i >= 0; i--)
		{
			hidden = deck[11].field[i]->is_card_hidden();

			if (hidden == 0)
			{
				bx = 110;
				hx = 180;
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
				if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
				{
					aktiv = true;
				}

				KARTE(bx, by, hx, hy, aktiv, deck[11].field[i]->is_card_hidden(), w_card[deck[11].field[i]->get_card_value()], w_suit[deck[11].field[i]->get_card_colour()]);
				deckleer = false;
				c++;
			}
		}
		 
		bx = 10;
		hx = 80;
		if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
		{
			cout << "######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = 0;

		}

		bx = 110;
		hx = 180;
		if (((bx < x) && (x < hx) && (by < y) && (y < hy)))
		{
			cout << "######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = c;

		}

		bx = 10;
		hx = 80;
		if (deckleer)
		{
			KARTE(bx, by, hx, hy, aktiv, 0, w_card[0], w_suit[0]);
		}

	}
	else
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}


	return mclickcard;
};

//draw botten save, load, restart and solve 
void save(int x, int y, int b, int h)
{

	int apx = b - 120;//anfangspunkt x
	int apy = h - 40; //anfangpunkt y
	int epx = b - 5;//anfangspunkt x
	int epy = h - 5; //anfangpunkt y

	if ((x > apx) && (x < epx) &&
		(y > apy) && (y < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Save"));
		cout << "######################################\n";
		cout << "Datei gespeichert\n";
		cout << "######################################\n\n";
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Save"));
	}
}
void load(int x, int y, int b, int h)
{

	int apx = b - 245;//anfangspunkt x
	int apy = h - 40; //anfangpunkt y
	int epx = b - 130;//anfangspunkt x
	int epy = h - 5; //anfangpunkt y

	if ((x > apx) && (x < epx) &&
		(y > apy) && (y < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
		cout << "######################################\n";
		cout << "Datei geladen\n";
		cout << "######################################\n\n";
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
	}

}
void restart(int x, int y, int b, int h)
{
	int apx = 125;//anfangspunkt x
	int apy = h - 40; //anfangpunkt y
	int epx = 250;//anfangspunkt x
	int epy = h - 5; //anfangpunkt y


	if ((x > apx) && (x < epx) &&
		(y > apy) && (y < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
		cout << "######################################\n";
		cout << "Neustart\n";
		cout << "######################################\n\n";
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
	}
}
void solve(int x, int y, int b, int h)
{

	int apx = 5;//anfangspunkt x
	int apy = h - 40; //anfangpunkt y
	int epx = 120;//anfangspunkt x
	int epy = h - 5; //anfangpunkt y



	if ((x > apx) && (x < epx) &&
		(y > apy) && (y < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Lösen"));

		cout << "######################################\n";
		cout << "Loese Spiel\n";
		cout << "######################################\n\n";
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Lösen"));
	}
}

//new green window
void newwindow(int b, int h)
{
	rectangle(0, 0, b, h, GREEN, GREEN);
}
//load button
int button(int x, int y, int b, int h)  // maus x, maus y, windowsweite, windowshöhe
{
	load(x, y, b, h);
	save(x, y, b, h);
	restart(x, y, b, h);
	solve(x, y, b, h);

	return 0;
}

//search for a click on a card
void fieldclick(int x, int y, int mclick[2], vector<field_stack>& field_stack, int windowswide, int windowsheight)
{
	int mclickcard = 100;	//mouseclick on card_number (100= no card is seleced,)
	int mclickstack = 13;	//mouseclick on field_number (0= no stack is seleced)
	int click = 0;			//save mclickcard (so mclick will not be overwritten)

	newwindow(windowswide, windowsheight);
	button(x, y, windowswide, windowsheight);

	for (int i = 0; i < 4; i++) //window target_field
	{
		click = 100;
		click = w_target_field(x, y, field_stack, i);

		if (click < 100)
		{
			cout << "mausklick auf target_field" << i+1 << "\n";

			mclickstack = i;
			mclickcard = click;
		}

	}


	for (int i = 4; i < 11; i++)
	{
		click = 100;
		click = w_field(x, y, field_stack, i);

		if (click < 100)
		{
			cout << "mausklick auf stack_feld" << i << "      karte" << click << "\n";
			mclickstack = i;
			mclickcard = click;
		}
	}

	click = 100;
	click = w_deck(x, y, field_stack);
	if (click < 100)
	{
		cout << "mausklick auf deck" << "      karte" << mclickcard << "\n";
		mclickstack = 11; //click on top of deck
		mclickcard = click;
	}

	mclick[0] = mclickstack; //handover mclick first stack
	mclick[1] = mclickcard; //handover mclick second card
}
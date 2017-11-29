#include "graphic.h"
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
COLORREF Colref[] = { BLACK,RED,GREEN,BLUE,YELLOW,BROWN };
#define white RGB(250,240,220)

char w_suit[4] = { 'S', 'H', 'D', 'C'};
char* w_colour;

char w_card[14] = {'0','A','2', '3', '4' , '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};


void KARTE(int bx, int by, int hx, int hy, bool aktiv, bool hidden, char karte, char w_colour)
{
	int col = GREEN;
	int akt = GREEN;
	int abstand = 20;

	if (aktiv == true)
	{
		akt = YELLOW;
	}
	else
	{
		akt = BLUE;
	}

	if ((w_colour == w_suit[0]) || (w_colour == w_suit[3]) )
	{
		col = BLACK;
	}
	else if ((w_colour == w_suit[1]) || (w_colour == w_suit[2]))
	{
		col = RED;
	}
	else
	{
		col = GREEN;
	}

	if (hidden == 0) //karte zeichenen an position
	{
		if (karte != w_card[0])
		{
			textbox(bx, by, hx, hy, 22, white, akt, col, LEFT_ALIGN,
				" %c    %c    %c\n %c          %c\n %c    %c    %c\n %c          %c\n %c    %c    %c\n", w_colour, karte, w_colour, karte, karte, w_colour, karte, w_colour, karte, karte, w_colour, karte, w_colour);
		}
		else
		{
			rectangle(bx, by, hx, hy, akt, GREEN);
		}
	}
	else
	{
		rectangle(bx, by, hx, hy, BLUE, BLUE);
		ellipse(bx+10, by+10, hx-10, hy-10, BROWN, BROWN);
	}
}


void w_target_field(int x, int y, stack<Card*>* tsp, int feld)
{
	int bx = 310 + feld * 100;
	int hx = 380 + feld * 100;
	int by = 10;
	int hy = 120;

	if (tsp->size())
	{
		bool hidden = false;
		hidden = tsp->top()->is_card_hidden();

		bool aktiv = false;
		if ((bx < x) && (x < hx) && (by < y) && (y < hy))
		{
			aktiv = true;
			cout << "######################################\n";
			cout << "Mausklick auf target_stack_Pik\n";
			cout << "######################################\n\n";

		}
		else
		{
			aktiv = false;
		}

		KARTE(bx, by, hx, hy, aktiv, hidden, w_card[tsp->top()->get_card_value()], w_suit[tsp->top()->get_card_colour()]);
	}
	else
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}
};
void w_field(int x, int y, vector<field_stack>& f1, int feld)
{
	int	bx = 10 +feld*100;
	int	hx = 80 +feld*100;
	int	by = 160;
	int	hy = 270;

	int posnumber = f1[feld].field.size();
	int abstand = 20;
	bool aktiv = false;
	bool hidden = false;
	

	if (posnumber)
	{
		for (int i = 0; i < posnumber; i++)
		{
			by = 160 + i*abstand;
			hy = 270 + i*abstand;

			hidden = f1[feld].field[i]->is_card_hidden();
				
			if ((i+1) < posnumber)
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < (by + abstand)))
				{
					cout << "######################################\n";
					cout << "Mausklick auf F" << feld << "\n" << "Karte " << (i + 1) << " ausgewaehlt\n";
					cout << "######################################\n\n";

					aktiv = true;
				}
			}
			else
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < hy))
				{
					cout << "######################################\n";
					cout << "Mausklick auf F" << feld << "\n" << "Karte " << (i+1) << " ausgewaehlt\n";
					cout << "######################################\n\n";

					aktiv = true;
				}
			}

			KARTE(bx, by, hx, hy, aktiv, hidden, w_card[f1[feld].field[i]->get_card_value()], w_suit[f1[feld].field[i]->get_card_colour()]);
		}
	}
	else
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}
};
void w_deck(int x, int y, vector<field_stack>& deck)
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
	bool aktiv2 = true; //aktiv2 true f+r spätere abfrage

	posnumber = deck[7].field.size();


	if (deck[7].field.size()) //für nicht inizialisrung
	{
		for (int i = 0; i < posnumber; i++)
		{
			hidden = deck[7].field[i]->is_card_hidden();

			if (hidden == 0)
			{
				bx = 110;
				hx = 180;
			}
			else
			{
				deckleer = false;
			}

			if ( ((bx < x) && (x < hx) && (by < y) && (y < hy)) && (aktiv2  == true) )
			{
				aktiv2 = true;
				aktiv = true;
				cout << "######################################\n";
				cout << "Mausklick auf DECK\n";
				cout << "######################################\n\n";

			}


			KARTE(bx, by, hx, hy, aktiv, hidden, w_card[deck[7].field[i]->get_card_value()], w_suit[deck[7].field[i]->get_card_colour()]);

			aktiv2 = false;
		}

		if (deckleer)
		{
			
			bx = 10;
			hx = 80;
			if ((bx < x) && (x < hx) && (by < y) && (y < hy))
			{
				aktiv = true;
			}
			else
			{
				aktiv = false;
			}
			KARTE(bx, by, hx, hy, aktiv, 0, w_card[0], w_suit[0]);
		}

	}
	else
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}

};


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


void newwindow(int b, int h)
{
	rectangle(0, 0, b, h, GREEN, GREEN);
}

int button(int x, int y, int b, int h)  // maus x, maus y, windowsweite, windowshöhe
{
	load(x, y, b, h);
	save(x, y, b, h);
	restart(x, y, b, h);
	solve(x, y, b, h);

	return 0;
}
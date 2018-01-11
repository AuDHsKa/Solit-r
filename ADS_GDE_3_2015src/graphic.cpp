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


// Card suit of Diamonds, Spades, Hearts, Clubs
char w_suit[4] = { 'D', 'S', 'H', 'C' }; 

// Cards value, Z=10, J= Jack, Q=Queen, K=King A=Ass
char w_card[14] = { '0','A','2', '3', '4' , '5', '6', '7', '8', '9', 'Z', 'J', 'Q', 'K' }; 

/***KARTE***/
/* Card=Karte function: print one card to the window:																*/
/* bx, by, hx, hy =card position, aktiv= click on this card, karte= number of w_card, w_colour= number of w_suit	*/
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
		col = BLACK; //Spades or Clubs
	}
	else if ((w_colour == w_suit[0]) || (w_colour == w_suit[2]))
	{
		col = RED; //Hearts or Diamonds
	}
	else
	{
		col = GREEN; //no card
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


//***w_field***//
/* draw all cards that are on a field/target, (feld)			  */
/* and															  */
/* sourch for a mouseclick on this field	(x and y)			  */
int w_field(int x, int y, vector<field_stack>& f1, int feld)
{
	int posnumber = f1[feld].field.size();	//number of card on a field
	int abstand;	//distanz to the next card
	bool aktiv = false; //click on card
	bool hidden = false; // how many cards are hidden
	int mclickcard = 100; //number of card that is choose, counts from 0. (100 no card is choose)

	int hx, hy, bx, by; // feld_stack_position
	//position of field_stack 0-10
	if (feld < 4) // target_stack
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

	//draw cards on field_stack and look for a mouseclick
	if (posnumber) //are cards on deck
	{
		for (int i = 0; i < posnumber; i++)//for ewvery card on the stack
		{
			if (feld > 3) // distance for cards on a field_stack
			{
				by = 160 + i*abstand;
				hy = 270 + i*abstand;
			}

			hidden = f1[feld].field[i]->is_card_hidden(); // is card hidden

			//maouseclick on card at feld 
			if ((i + 1) < posnumber)
			{
				if ((bx < x) && (x < hx) && (by < y) && (y < (by + abstand))) // auswahl der karte in mitten eines stapels
				{
					cout << "\n######################################\n";
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
					cout << "\n######################################\n";
					cout << "Mausklick auf F" << feld << "\n" << "Karte " << (i + 1) << " ausgewaehlt\n";
					cout << "######################################\n\n";
					mclickcard = i;
					aktiv = true;
				}
			}

			KARTE(bx, by, hx, hy, aktiv, hidden, w_card[f1[feld].field[i]->get_card_value()], w_suit[f1[feld].field[i]->get_card_colour()]); // draw card
		}
	}
	else // no cards on feld
	{
		if ((bx < x) && (x < hx) && (by < y) && (y < hy))
		{
			cout << "\n######################################\n";
			cout << "Mausklick auf F" << feld << "\n" << "Karte " << "0 ausgewaehlt\n";
			cout << "######################################\n\n";
			mclickcard = 53; // click at an empty feld
			aktiv = true;
		}

		KARTE(bx, by, hx, hy, aktiv, 0, w_card[0], w_suit[0]); // draw a empty field
	}

	
	//if the aktiv card is hidden, choose the next unhidden card 
	//wenn karte verdeckt dann nehme die nächste umdeckte karte auf dem stapel
	if ((mclickcard != 100) && (mclickcard != 53)) // 100 = no card choose, 53 empty feld
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

//***w_deck***//
/* draw all cards that are on the deck							  */
/* and															  */
/* sourch for a mouseclick (x and y)							  */
int w_deck(int x, int y, vector<field_stack>& deck)
{
	int posnumber = deck[11].field.size(); //number of card on the deck
	
	//Position of deck
	int bx = 10;
	int by = 10;
	int hx = 80;
	int hy = 120;

	bool hidden = false;  //is cards are hidden
	bool deckleer = true; //true no card on deck is hidden
	bool aktiv = false;   //aktiv false f+r spätere abfrage
	int mclickcard = 100; //number of card that is choose, counts from 0. (100 no card is choose)
						  

	//draw cards on deck_stack and look for a mouseclick
	if (posnumber) //are cards on deck
	{
		int number_of_unhidden_cards = 0; // how many cards are hidden

		//draw first the card that unhidden, last card is unhidden is on top
		for (int i = (posnumber - 1); i >= 0; i--)
		{
			hidden = deck[11].field[i]->is_card_hidden();

			if (hidden == 0) //card is unhidden
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
			else // card is hidden
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
			cout << "\n######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = 53; // mouseclick on closed deck = 53

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
			cout << "\n######################################\n";
			cout << "Mausklick auf DECK\n";
			cout << "######################################\n\n";
			mclickcard = number_of_unhidden_cards; // mouseclick on the last open card

		}
	}
	else //no cards on deck
	{
		KARTE(bx, by, hx, hy, 0, 0, w_card[0], w_suit[0]);
	}

	return mclickcard;
};


//***button_save***//
/* draw button_save					*/
/* and							    */
/* sourch for a mouseclick (win)    */
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
		cout << "\n######################################\n";
		cout << "Datei gespeichert\n";
		cout << "######################################\n\n";
		updatescr();
		output("Datei gespeichert\n", "logfile.txt");
		write_data(field_stack); // save game
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Save"));
	}
}


//***button_load***//
/* draw button_load					*/
/* and							    */
/* sourch for a mouseclick (win)    */
void load(window& win, vector<field_stack>&  field_stack, vector<Card>& arrl)
{

	int apx = win.wide - 245;//anfangspunkt x
	int apy = win.height - 40; //anfangpunkt y
	int epx = win.wide - 130;//anfangspunkt x
	int epy = win.height - 5; //anfangpunkt y

	if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
		(win.y_mouse > apy) && (win.y_mouse < epy))
	{
		textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
		cout << "\n######################################\n";
		cout << "Datei geladen\n";
		cout << "######################################\n\n";
		updatescr();
		delete_data(field_stack); // delete last game
		read_data(field_stack, arrl); //load a game
		output("Datei geladen und augefürt\n", "logfile.txt");
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Load"));
	}

}

//***button_restart***//
/* draw button_restart				*/
/* and							    */
/* sourch for a mouseclick (win)    */
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
		cout << "\n######################################\n";
		cout << "Neustart\n";
		cout << "######################################\n\n";
		updatescr();
		//restart game
		delete_data(field_stack);
		initialize_field(field_stack);
		initialize_target(field_stack, cards);
		austeilen(field_stack);
		output("Restart augefürt\n", "logfile.txt");
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Restart"));
	}
}


//***button_solve***//
/* draw button_solve				*/
/* and							    */
/* sourch for a mouseclick (win)    */
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
		updatescr();
		cout << "\n######################################\n";
		cout << "Loese Spiel\n";
		cout << "######################################\n\n";
		output("Lösen augefürt\n", "logfile.txt");
		solvealgo(field_stack, win); //solve the game
	}
	else
	{
		textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Lösen"));
	}
}


//***button_statistik***//
/* draw button_statistik			*/
/* and							    */
/* sourch for a mouseclick (win)    */
void statistik_button(window& win, vector<field_stack>&  field_stack, vector<Card>& cards)
	{

		int apx = 255;//anfangspunkt x
		int apy = win.height - 40; //anfangpunkt y
		int epx = 370;//anfangspunkt x
		int epy = win.height - 5; //anfangpunkt y



		if ((win.x_mouse > apx) && (win.x_mouse < epx) &&
			(win.y_mouse > apy) && (win.y_mouse < epy))
		{
			textbox(apx, apy, epx, epy, 18, BLUE, YELLOW, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Statistik"));

			cout << "\n######################################\n";
			cout << "Statistik auswerten\n";
			cout << "######################################\n\n";
			statistik(field_stack, win, cards);
		}
		else
		{
			textbox(apx, apy, epx, epy, 18, BLUE, GREY, GREY, SINGLE_LINE | VCENTER_ALIGN | CENTER_ALIGN, ("Statistik"));
		}
	}


//draw new green window (complet)
void newwindow(window& win)
{
	rectangle(0, 0, win.wide, win.height, GREEN, GREEN);
}

//draw new green window (without button)
void newwindow_cards(window& win)
{
	rectangle(0, 0, win.wide-5, win.height-40, GREEN, GREEN);
}


//***button***//
/* load all button that are allowed								  */
/* and															  */
/* sourch for a mouseclick on this field	(x and y)			  */
int button(window& win, vector<field_stack>&  field_stack, vector<Card>& cards)  // maus x, maus y, windowsweite, windowshöhe
{
	load(win, field_stack,cards);
	save(win, field_stack);
	restart(win, field_stack, cards);
	solve(win,  field_stack);

#ifndef Auswerten
	statistik_button(win, field_stack, cards);
#endif // Auswerten

	return 0;
}

//***click_window***//
/* a click was detected  										  */
/* and															  */
/* sourch for a mouseclick all stacks							  */
/* and															  */
/* save choosen card in window& win 							  */
void click_window(vector<field_stack>& field_stack, window& win )
{
	win.second_click_card = 100;	//mouseclick on card_number (100= no card is seleced)
	win.second_click_stack = 13;	//mouseclick on field_number (13= no stack is seleced)
	int click = 100;				//save mclickcard (so mclick will not be overwritten)

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
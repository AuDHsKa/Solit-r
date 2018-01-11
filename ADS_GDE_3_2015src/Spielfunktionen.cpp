#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <time.h>

#include "graphics\graphicfunctions.h"

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#include <stack>
#include <iostream>

#ifndef graphic.h
#include "graphic.h"
#endif // !graphic.h

#ifndef __window__
#include "window.h"
#endif

#ifndef Spielfunktionen.h
	#include "Spielfunktionen.h"
#endif // !Spielfunktionen.h

#ifndef __einaus__
#include "Eingabe_Ausgabe.h"
#endif

void	copy_cards(vector<Card>& origin, vector<Card*>& copy)
{
	for (size_t i = 0; i < 52; i++)
	{
		// schreibt in copy die Referenz der Karten
		copy.at(i) = &origin.at(i);
	}
}

void	mein_austeilen(vector<field_stack>& ziel)
{
	size_t	mini = 0;
	size_t	maxi = 13;
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	new_card = 0;
	size_t	size = 0;
	size_t	ii = 0;
	Card*	jojo;

	// time(NULL) und "time.h" eingef�gt, f�e immer andere Zufallszahl
	srand(time(NULL));

	//while (Karten.size())
	//{
	//	new_card = min + rand() % (maxi - mini + 1);
	//	hoch = min + rand() % (max - min + 1);

	//	size = Karten.size();

	//	// holt sich die ausgew�lte zuf�llige Referenz 
	//	jojo = Karten.at(new_card % size);

	//	// l�scht die ausgew�lte zuf�llige Referenz
	//	Karten.erase(Karten.begin() + (new_card % size));

	//	// ueberpr�ft ob der Feldstapel "voll" ist
	//	while (ziel[(hoch % 8) + 4].field.size() == ziel[(hoch % 8) + 4].get_stack_count())
	//	{
	//		hoch++;
	//	}

	//	// setzt die ausgew�hlte Karte auf den Feldstapel
	//	ziel[(hoch % 8) + 4].field.push_back(jojo);
	//}

	//// take every card of every stack on the target field 
	//for (size_t i = 0; i < 13; i++)
	//{
	//	// go for every stack on the target field
	//	for (size_t ii = 0; ii < 4; ii++)
	//	{
	while (ziel.at(0).field.size() || ziel.at(1).field.size() || ziel.at(2).field.size() || ziel.at(3).field.size())
	{
		if (ii < 4)
		{
			if (ziel.at(ii).field.size())
			{
				maxi = ziel.at(ii).field.size() - 1;
				new_card = min + rand() % (maxi - mini + 1);
				hoch = min + rand() % (max - min + 1);

				jojo = ziel.at(ii).field.at(new_card);
				ziel.at(ii).field.erase((ziel.at(ii).field.begin() + new_card));

				while (ziel.at((hoch % 8) + 4).field.size() == ziel.at((hoch % 8) + 4).get_stack_count())
				{
					hoch++;
				}

				// set the card from target stack on the (hoch) field stack
				ziel.at((hoch % 8) + 4).field.push_back(jojo);
				ii++;
			}
			else
			{
				ii++;
			}
		}
		else
		{
			ii = 0;
		}
	}


	//Versteckt die Karten beim austeilen

	for (size_t i = 4; i < 12; i++)
	{
		for (size_t ii = 0; ii < (ziel.at(i).field.size() - 1); ii++)
		{
			ziel.at(i).field.at(ii)->hide_card();
		}
	}
}

void	austeilen(vector<field_stack>& ziel)
{
	size_t	pp = 0;
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;

	// eingef�gt 
	srand(time(NULL));

	// take every card of every stack on the target field 
	for (size_t i = 0; i < 13; i++)
	{
		// go for every stack on the target field
		for (size_t ii = 0; ii < 4; ii++)
		{
			jojo = ziel.at(ii).field.back();
			ziel.at(ii).field.pop_back();

			if (pp == 53)
			{	
				pp = 0;
				hoch = 7; 
			}
			else
			{
				hoch = min + rand() % (max - min + 1);
			}

			while (ziel.at((hoch % 8) + 4).field.size() == ziel.at((hoch % 8) + 4).get_stack_count())
			{
				hoch++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel.at((hoch % 8) + 4).field.push_back(jojo);
			pp++;
		}

	}

	for (size_t i = 4; i < 12; i++)
	{
		for (size_t ii = 0; ii < (ziel.at(i).field.size() - 1); ii++)
		{
			ziel.at(i).field.at(ii)->hide_card();
		}
	}
}

/****************window_move*****************************************/
/*if the turn (Spielzug) possile, Yes = move card	no= no change	*/
void	window_move(vector<field_stack>& field_stack, window& win)
{
	//click on a field_stack or target_stack or open deck
	if ((win.second_click_stack == 13) || (win.first_click_card == 53)) // click on no stack
	{
		win.first_click_stack = 13; // clear click on first card 
		win.first_click_card = 100; // clear click on first card 
	}
	else
	{
		if ((win.first_click_stack == 13) || (win.first_click_stack == win.second_click_stack)) //click on the same stack
		{
			win.first_click_stack = win.second_click_stack; // choose the new stack at first stack
			win.first_click_card = win.second_click_card;   // choose the new card at first card
		}
		else
		{
			if (win.second_click_stack < 53) // mouseclick is not the hidden deck
			{
				playing_rules(field_stack, win); // look for possilble move
			}
		}
	}

	// mouseclick on  hidden deck_stack
	if (win.second_click_stack == 11 && win.second_click_card == 53) //mausklick auf verdecktes deck
	{
		int c = 0;

		for (size_t i = 0; i < field_stack[11].field.size(); i++) // count number of hidden cards
		{
			if ((field_stack[11].field[i]->is_card_hidden()) == 1)
			{
				c++;
			}
		}

		if (c == 0) // if no card is hidden, then hide all cards on deck.
		{
			for (size_t i = 0; i < (field_stack[11].field.size()); i++)
			{
				field_stack[11].field[i]->hide_card();
			}
		}
		else
		{
			field_stack[11].field[c - 1]->undiscover_card();
		}

		win.first_click_stack = 13; //reset of the first click
		win.first_click_card = 100; //reset of the first click
		win.x_mouse = 0; //reset of the aktuel mouseclick
		win.y_mouse = 0; //reset of the aktuel mouseclick
	}

}

/****************same_colour*****************************************/
/*have the cards the same colour									*/
bool	same_colour(vector<field_stack>& field_stack, window& win)
{
	bool same_col = false;

	return same_col;
}

/******************field_empty***************************************/
/*is there any card on the stack									*/
bool	field_empty(vector<field_stack>& field_stack, int empty_field) 
{
	bool empty = false;

	if (field_stack[empty_field].field.empty())
	{
		empty = true;
	}
	else
	{
		empty = false;
	}

	return empty;
}

/******************undiscover***************************************/
/*undiscover choosing card										   */
void	undiscover(vector<field_stack>& field_stack, window& win)
{
	if (win.first_click_stack < 11)
	{
		if (field_stack[win.first_click_stack].field.size())
		{
			field_stack[win.first_click_stack].field[field_stack[win.first_click_stack].field.size()-1]->undiscover_card();
		}
	}
}

/******************target_rules*************************************/
/*look for a possible move on target							   */
void	target_rules(vector<field_stack>& field_stack, window& win)
{
	bool first_stack_empty = field_empty(field_stack, win.first_click_stack);
	bool second_stack_empty = field_empty(field_stack, win.second_click_stack);

	if (first_stack_empty) // no card on field to move
	{
		return;
	}

	if (second_stack_empty) // only the Ass can be move at target when field is empty
	{
		if(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == 1) 
		{
		win.second_click_stack = field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour(); //sourch for the right target_field 
		move_cards(field_stack, win);
		undiscover(field_stack, win);

		win.first_click_stack = 13; //reset of the first click
		win.first_click_card = 100; //reset of the first click
		win.x_mouse = 0; //reset of the aktuel mouseclick
		win.y_mouse = 0; //reset of the aktuel mouseclick
		}
	}
	else
	{
		win.second_click_stack = field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour();//sourch for the right target_field

			if (((field_stack[win.first_click_stack].field.empty() == false) && (field_stack[win.second_click_stack].field.empty() == false)) &&
				(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == (field_stack[win.second_click_stack].field.back()->get_card_value() + 1)))
			{
				move_cards(field_stack, win);
				undiscover(field_stack, win);

				win.first_click_stack = 13; //reset of the first click
				win.first_click_card = 100; //reset of the first click
				win.x_mouse = 0; //reset of the aktuel mouseclick
				win.y_mouse = 0; //reset of the aktuel mouseclick
			}
	}
}

/******************field_rules*************************************/
/*look for a possible move on field_Stack						   */
void	field_rules(vector<field_stack>& field_stack, window& win)
{
	bool same_col = same_colour(field_stack, win);
	bool first_stack_empty = field_empty(field_stack, win.first_click_stack);
	bool second_stack_empty = field_empty(field_stack, win.second_click_stack);

	if (first_stack_empty)
	{
		return;
	}

	if (second_stack_empty)
	{
		if (field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == 13)//is the card a king
		{
			move_cards(field_stack, win);
			undiscover(field_stack, win);

			win.first_click_stack = 13; //reset of the first click
			win.first_click_card = 100; //reset of the first click
			win.x_mouse = 0; //reset of the aktuel mouseclick
			win.y_mouse = 0; //reset of the aktuel mouseclick
		}
	}
	else
	{	//is the move possible (colour, card number)
		if (((field_stack[win.first_click_stack].field.empty() == false) && (field_stack[win.second_click_stack].field.empty() == false)) &&
			(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == (field_stack[win.second_click_stack].field.back()->get_card_value() - 1)) &&
			(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() != field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) &&
			((field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() + field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) != 2) &&
			((field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() + field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) != 4))
		{
			move_cards(field_stack, win);
			undiscover(field_stack, win);

			win.first_click_stack = 13; //reset of the first click
			win.first_click_card = 100; //reset of the first click
			win.x_mouse = 0; //reset of the aktuel mouseclick
			win.y_mouse = 0; //reset of the aktuel mouseclick
		}
	}

}

/******************playing_rules*************************************/
/*call the right rules (target or field rules) 					    */
void	playing_rules(vector<field_stack>& field_stack, window& win)
{
	if (win.second_click_stack < 4)
	{
		target_rules(field_stack, win);
	}

	if (win.second_click_stack > 3)
	{
		field_rules(field_stack, win);
	}

}

void	move_cards(vector<field_stack>& field_stack, window&	select)
{
	Card*	jojo;

	if (select.first_click_stack == 11 || select.first_click_stack < 4 || select.second_click_stack < 4)
	{
#ifndef Auswerten
		write_log_data(field_stack, select);
#endif
		jojo = field_stack[select.first_click_stack].field.at(select.first_click_card);
		field_stack[select.first_click_stack].field.erase(field_stack[select.first_click_stack].field.begin() + select.first_click_card);

		field_stack[select.second_click_stack].field.push_back(jojo);
	}
	else
	{
		while (field_stack[select.first_click_stack].field.size()	>	select.first_click_card)
		{
#ifndef Auswerten
			write_log_data(field_stack, select);
#endif
			jojo = field_stack[select.first_click_stack].field.at(select.first_click_card);
			field_stack[select.first_click_stack].field.erase(field_stack[select.first_click_stack].field.begin() + select.first_click_card);

			field_stack[select.second_click_stack].field.push_back(jojo);
		}
	}
}


/******************ki_field_field*************************************/
/*KI Move: sourch for a move from field to field					 */
/*move only one card												 */
/*return: someting_game (0= no change, 1= one card has been change	 */
int ki_field_field(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;
	int hide = 0;

	win.old_card_one = NULL; //set old card1 0, is used to stop the same turn
	win.old_card_second = NULL; //set old card2 0, is used to stop the same turn

		for (int i = 4; i < 11; i++)
		{
			win.x_mouse = 1;// set to 1 to look for a moved card
			win.y_mouse = 1;// set to 1 to look for a moved card

			hide = 0; // search for unhidden cards
			if (field_stack[i].field.size() != 0)
			{
				while (field_stack[i].field[hide]->is_card_hidden())
				{
					hide++;
				}
			}

			for (hide; hide < field_stack[i].field.size(); hide++)
			{


				for (int y = 4; y < 11; y++)
				{
					if (i != y)
					{
						win.first_click_stack = i; // set cards
						win.first_click_card = hide;
						win.second_click_stack = y;
						if (field_stack[win.second_click_stack].field.size())
						{
							win.second_click_card = field_stack[y].field.size() - 1;
						}
						else
						{
							win.second_click_card = 53; //leeres feld f�r k�nig
						}

						if (win.second_click_card != 53)
						{ //if the card will be turn to the old place: break
							if ( (field_stack[win.first_click_stack].field.at(win.first_click_card) == win.old_card_one)
								&& (field_stack[win.second_click_stack].field.at(win.second_click_card) == win.old_card_second) )
							{
	
								something_game = 0;
								break;

							}
						}

						playing_rules(field_stack, win);

						

						if (win.x_mouse == 0 && win.y_mouse == 0)// a move was made
						{
							something_game = 1;
							if (win.second_click_card != 53)
							{
								win.old_card_one = field_stack[win.second_click_stack].field.at(win.second_click_card + 1); // i-te karte ausgew�hlt damit nicht selbe karte zwei mal verschoben
							}
							if (field_stack[i].field.size())
							{
								win.old_card_second = field_stack[i].field.back();
							}
							break;
						}
					}

				}

			}
		}
	return something_game;
}

/******************ki_deck_field*************************************/
/*KI Move: sourch for a move from deck  to field					 */
/*move only one card												 */
/*return: someting_game (0= no change, 1= one card has been change	 */
int ki_deck_field(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;
	int hide = 0;

	win.first_click_stack = 11;

		win.x_mouse = 1;// set to 1 to look for a moved card
		win.y_mouse = 1;// set to 1 to look for a moved card

			if (field_stack[11].field.size() == 0)
			{
				something_game = 0;
				return something_game;
			}

			for (int i = 0; i < field_stack[11].field.size(); i++)
			{
				win.first_click_card = i;

				for (int y = 4; y < 11; y++)
				{
					win.second_click_stack = y; // set cards
					win.second_click_card = field_stack[y].field.size() - 1;// set cards

					playing_rules(field_stack, win);

					if (win.x_mouse == 0 && win.y_mouse == 0)// a move was made
					{
						something_game = 1;
						break;
					}
				}

				if (win.x_mouse == 0 && win.y_mouse == 0)// a move was made
				{
					something_game = 1;
					break;
				}
			}
		return something_game;
}

/******************ki_field_target*************************************/
/*KI Move: sourch for a move from field  to target					 */
/*move only one card												 */
/*return: someting_game (0= no change, 1= one card has been change	 */
int ki_field_target(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;

	for (int i = 4; i < 11; i++)
	{
		win.x_mouse = 1;// set to 1 to look for a moved card
		win.y_mouse = 1;// set to 1 to look for a moved card

			win.first_click_stack = i; //set stack
			if (field_stack[i].field.size())
			{
				win.first_click_card = field_stack[i].field.size()-1;//set card
			}
			else
			{
				win.first_click_card = 53; //leeres feld f�r field
			}

			for (int y = 0; y < 4; y++)
			{
				win.second_click_stack = y;//set stack
				if (field_stack[y].field.size())
				{
					win.second_click_card = field_stack[y].field.size()-1;////set card
				}
				else
				{
					win.second_click_card = 53; //leeres feld f�r target
				}

				playing_rules(field_stack, win);

				if (win.x_mouse == 0 && win.y_mouse == 0)// a move was made
				{
					something_game = 1;
					return something_game;
				}
			}
	}
	return something_game;
}

/******************ki_deck_target*************************************/
/*KI Move: sourch for a move from deck  to target					 */
/*move only one card												 */
/*return: someting_game (0= no change, 1= one card has been change	 */
int ki_deck_target(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;

	win.first_click_stack = 11;

	win.x_mouse = 1;// set to 1 to look for a moved card
	win.y_mouse = 1;// set to 1 to look for a moved card

	if (field_stack[11].field.size() == 0)
	{
		something_game = 0;
		return something_game;
	}

	for (int i = 0; i < field_stack[11].field.size(); i++)
	{
		win.first_click_card = i;//set stack

		for (int y = 0; y < 4; y++)
		{
			win.second_click_stack = y;//set stack
			win.second_click_card = field_stack[y].field.size() - 1;//set card

			playing_rules(field_stack, win);

			if (win.x_mouse == 0 && win.y_mouse == 0)// a move was made
			{
				something_game = 1;
				return something_game;
			}
		}
	}
	return something_game;
}

/******************solvealgo******************************************/
/*KI: call the KI_function in loops									 */
/*move card till game is won or no change after a loop				 */
/*return:	size_t 0= no solution 1= game is solved					 */
size_t solvealgo(vector<field_stack>&	field_stack, window& win)
{
	int loop_field = 1;
	int loop_deck = 0;
	int loop_field_target = 0;
	int loop_deck_target = 0;
	int unterbrechung = 0; // for field to field, do the loop more often 
	int loop_deck_anz = 0;// for deck to field, do the loop more often

	if (field_stack[11].field.size() != 0)
	{
		for (size_t ii = 0; ii < (field_stack[11].field.size() - 1); ii++)
		{
			field_stack[11].field[ii]->undiscover_card();
		}
	}
		

	while (loop_field == 1 || loop_deck == 1 || loop_field_target == 1 || loop_deck_target == 1)
	{


		loop_field = 1;
		while (loop_field == 1)//loop field to field
		{
			loop_field = ki_field_field(field_stack, win);/// fehler wenn karte immer verschiebarist!!
			unterbrechung++;
			if (unterbrechung > 3)
			{
				loop_field = 0;
				break;
			}
		}

		loop_deck_anz = 0;
		loop_deck = 1;
		while (loop_deck == 1)//loop deck to field
		{
			loop_deck = ki_deck_field(field_stack, win);
			loop_deck_anz++;
		}
		if (loop_deck_anz > 2)
		{
			loop_field = 1;
		}
		
		loop_field_target = 1;
		loop_field_target = ki_field_target(field_stack, win);

		loop_deck_target = 1;
		loop_deck_target = ki_deck_target(field_stack, win);

		click_window(field_stack, win);//l�sungsweg anzeigen
		updatescr();//l�sungsweg anzeigen
	}

	//won the game
	if ((field_stack.at(0).field.size() == 13) &&
		(field_stack.at(1).field.size() == 13) &&
		(field_stack.at(2).field.size() == 13) &&
		(field_stack.at(3).field.size() == 13))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void	gewonnen()
{
	cout << "\n*************************************************************\n";
	cout << "*************************************************************\n";
	cout << "				\n Herzlichen Glueckwunsch!\n";
	cout << "				\n Sie haben das Spiel gewonnen!\n";
	cout << "\n*************************************************************\n";
	cout << "*************************************************************\n";
	output("Das Spiel wurde gewonnen\n", "logfile.txt");
}

void statistik(vector<field_stack>&	field_stack, window& win, vector<Card>& cards)
{
	size_t	n = 0;
	size_t	gewonnen = 0;

	cout << "Statistik. Wie viele Versuche moechten sie Durchlaufen?\n(Bitte die Anzahl eingeben)\n";
	cin >> n ;

	while (n)
	{
		set_win_clicks(win);
		gewonnen += solvealgo(field_stack, win);
		delete_data(field_stack);
		initialize_target(field_stack, cards);
#ifdef mydistri
		austeilen(field_stack);
#endif // mydistri
#ifdef zufall
		zuf_austeilen(field_stack);
#endif // !mydistri
		n--;
	}

	cout << "Es wurden: " << gewonnen << " Spiele gewonnen!\n";
}

size_t	look_for_game_won(vector<field_stack>&	field_stack)
{
	if ((field_stack[0].field.size() == 13) &&
		(field_stack[1].field.size() == 13) &&
		(field_stack[2].field.size() == 13) &&
		(field_stack[3].field.size() == 13))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void	clear_field(vector<field_stack>&	field_stack)
{
	for (size_t yy = 0; yy < 12; yy++)
	{
		if (!(field_stack.at(yy).field.empty()))
		{
			field_stack.at(yy).field.erase(field_stack.at(yy).field.begin(), (field_stack.at(yy).field.begin() + field_stack.at(yy).field.size()));
		}
	}
}

void	initialize_field(vector<field_stack>&	field_stack)
{
	for (size_t i = 4; i < 11; i++)
	{
		field_stack.at(i).set_stack_count(i - 3);
	}

	field_stack.at(11).set_stack_count(24);
}

void	initialize_target(vector<field_stack>& field_stack, vector<Card>& cards)
{
	for (size_t yy = 0; yy < 4; yy++)
	{
		for (size_t ii = 0; ii < 13; ii++)
		{
			field_stack.at(yy).field.push_back(&cards.at(13 * yy + ii));
			field_stack.at(yy).field.at(ii)->undiscover_card();
		}
	}
}

void	set_win_clicks(window& win)
{
	win.first_click_card = 100;
	win.first_click_stack = 13;
	win.second_click_card = 100;
	win.second_click_stack = 13;
}
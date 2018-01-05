#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "math.h"

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

void	mein_austeilen(vector<field_stack>& ziel, vector<Card*> Karten)
{
	size_t	mini = 0;
	size_t	maxi = 51;
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	new_card = 0;
	size_t	size = 0;
	size_t	iii = 0;
	Card*	jojo;

	// time(NULL) und "time.h" eingefügt, füe immer andere Zufallszahl
	srand(time(NULL));

	while (Karten.size())
	{
		new_card = min + rand() % (maxi - mini + 1);
		hoch = min + rand() % (max - min + 1);

		size = Karten.size();

		// holt sich die ausgewälte zufällige Referenz 
		jojo = Karten.at(new_card % size);

		// löscht die ausgewälte zufällige Referenz
		Karten.erase(Karten.begin() + (new_card % size));

		// ueberprüft ob der Feldstapel "voll" ist
		while (ziel[(hoch % 8) + 4].field.size() == ziel[(hoch % 8) + 4].get_stack_count())
		{
			hoch++;
		}

		// setzt die ausgewählte Karte auf den Feldstapel
		ziel[(hoch % 8) + 4].field.push_back(jojo);
	}

	//Versteckt die Karten beim austeilen

	for (size_t i = 4; i < 12; i++)
	{
		for (size_t ii = 0; ii < (ziel[i].field.size() - 1); ii++)
		{
			ziel[i].field[ii]->hide_card();
		}
	}
}

void	austeilen(vector<field_stack>& ziel)
{
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;

	// eingefügt 
	srand(time_t(NULL));

	// take every card of every stack on the target field 
	for (size_t i = 0; i < 13; i++)
	{
		// go for every stack on the target field
		for (size_t ii = 0; ii < 4; ii++)
		{
			hoch = min + rand() % (max - min + 1);

			jojo = ziel[ii].field.back();
			ziel[ii].field.pop_back();


			while (ziel[(hoch % 8) + 4].field.size() == ziel[(hoch % 8) + 4].get_stack_count())
			{
				hoch++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel[(hoch % 8) + 4].field.push_back(jojo);
		}

	}

	for (size_t i = 4; i < 12; i++)
	{
		for (size_t ii = 0; ii < (ziel[i].field.size() - 1); ii++)
		{
			ziel[i].field[ii]->hide_card();
		}
	}
}

void	window_move(vector<field_stack>& field_stack, window& win)
{
	if ((win.second_click_stack == 13) || (win.first_click_card == 53))
	{
		win.first_click_stack = 13;
		win.first_click_card = 100;
	}
	else
	{
		if ((win.first_click_stack == 13) || (win.first_click_stack == win.second_click_stack))
		{
			win.first_click_stack = win.second_click_stack;
			win.first_click_card = win.second_click_card;
		}
		else
		{
			if (win.second_click_stack < 53)
			{
				playing_rules(field_stack, win);
			}
		}
	}

	if (win.second_click_stack == 11 && win.second_click_card == 53) //mausklick auf verdecktes deck
	{
		int c = 0;

		for (size_t i = 0; i < field_stack[11].field.size(); i++)
		{
			if ((field_stack[11].field[i]->is_card_hidden()) == 1)
			{
				c++;
			}
		}

		if (c == 0)
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

		win.first_click_stack = 13; //rücksetzen des ersen clicks
		win.first_click_card = 100;
		win.x_mouse = 0;
		win.y_mouse = 0;
	}

}

bool	same_colour(vector<field_stack>& field_stack, window& win)
{
	bool same_col = false;

	return same_col;
}

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

void	target_rules(vector<field_stack>& field_stack, window& win)
{
	bool first_stack_empty = field_empty(field_stack, win.first_click_stack);
	bool second_stack_empty = field_empty(field_stack, win.second_click_stack);

	if (first_stack_empty)
	{
		return;
	}

	if (second_stack_empty)
	{
		if(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == 1)
		{
		win.second_click_stack = field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour();
		move_cards(field_stack, win);
		undiscover(field_stack, win);

		win.first_click_stack = 13; //rücksetzen des ersen clicks
		win.first_click_card = 100;

		win.x_mouse = 0;
		win.y_mouse = 0;
		}
	}
	else
	{
		win.second_click_stack = field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour();

			if (((field_stack[win.first_click_stack].field.empty() == false) && (field_stack[win.second_click_stack].field.empty() == false)) &&
				(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == (field_stack[win.second_click_stack].field.back()->get_card_value() + 1)))
			{
				move_cards(field_stack, win);
				undiscover(field_stack, win);

				win.first_click_stack = 13; //rücksetzen des ersen clicks
				win.first_click_card = 100;

				win.x_mouse = 0;
				win.y_mouse = 0;
			}
	}
}

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
		if (field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == 13)
		{
			move_cards(field_stack, win);
			undiscover(field_stack, win);

			win.first_click_stack = 13; //rücksetzen des ersen clicks
			win.first_click_card = 100;

			win.x_mouse = 0;
			win.y_mouse = 0;
		}
	}
	else
	{
		if (((field_stack[win.first_click_stack].field.empty() == false) && (field_stack[win.second_click_stack].field.empty() == false)) &&
			(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_value() == (field_stack[win.second_click_stack].field.back()->get_card_value() - 1)) &&
			(field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() != field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) &&
			((field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() + field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) != 2) &&
			((field_stack[win.first_click_stack].field[win.first_click_card]->get_card_colour() + field_stack[win.second_click_stack].field[win.second_click_card]->get_card_colour()) != 4))
		{
			move_cards(field_stack, win);
			undiscover(field_stack, win);

			win.first_click_stack = 13; //rücksetzen des ersen clicks
			win.first_click_card = 100;

			win.x_mouse = 0;
			win.y_mouse = 0;
		}
	}

}

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
		jojo = field_stack[select.first_click_stack].field.at(select.first_click_card);
		field_stack[select.first_click_stack].field.erase(field_stack[select.first_click_stack].field.begin() + select.first_click_card);

		field_stack[select.second_click_stack].field.push_back(jojo);
		
		cout << "von stack " << select.first_click_stack << "  Karte " << select.first_click_card << "\n";
		cout << "zu stack " << select.second_click_stack << "  Karte " << select.second_click_card << "\n\n";
		//write_log_data(field_stack, select.first_click_stack * 100 + select.first_click_card, select.second_click_stack * 100 + select.second_click_card);
	}
	else
	{
		while (field_stack[select.first_click_stack].field.size()	>	select.first_click_card)
		{
			jojo = field_stack[select.first_click_stack].field.at(select.first_click_card);
			field_stack[select.first_click_stack].field.erase(field_stack[select.first_click_stack].field.begin() + select.first_click_card);

			field_stack[select.second_click_stack].field.push_back(jojo);

			cout << "von stack " << select.first_click_stack << "  Karte " << select.first_click_card << "\n";
			cout << "zu stack " << select.second_click_stack << "  Karte " << select.second_click_card << "\n\n";
			//write_log_data(field_stack,select.first_click_stack*100+select.first_click_card, select.second_click_stack*100+select.second_click_card +1);
		}
	}
}


//sven big ki
int ki_field_field(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;
	int hide = 0;

	win.old_card_one = NULL;
	win.old_card_second = NULL;

		for (int i = 4; i < 11; i++)
		{
			win.x_mouse = 1;
			win.y_mouse = 1;

			hide = 0;
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
						win.first_click_stack = i;
						win.first_click_card = hide;
						win.second_click_stack = y;
						if (field_stack[win.second_click_stack].field.size())
						{
							win.second_click_card = field_stack[y].field.size() - 1;
						}
						else
						{
							win.second_click_card = 53; //leeres feld für könig
						}

						if (win.second_click_card != 53)
						{
							if ( (field_stack[win.first_click_stack].field.at(win.first_click_card) == win.old_card_one)
								&& (field_stack[win.second_click_stack].field.at(win.second_click_card) == win.old_card_second) )
							{
	
								something_game = 0;
								break;

							}
						}

						playing_rules(field_stack, win);

						

						if (win.x_mouse == 0 && win.y_mouse == 0)
						{
							something_game = 1;
							if (win.second_click_card != 53)
							{
								win.old_card_one = field_stack[win.second_click_stack].field.at(win.second_click_card + 1); // i-te karte ausgewählt damit nicht selbe karte zwei mal verschoben
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

int ki_deck_field(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;
	int no_change = 0;
	int hide = 0;

	win.first_click_stack = 11;

		win.x_mouse = 1;
		win.y_mouse = 1;

			if (field_stack[11].field.size() == 0)
			{
				something_game = 0;
				return something_game;
			}
			no_change = 1;

			for (int i = 0; i < field_stack[11].field.size(); i++)
			{
				win.first_click_card = i;

				for (int y = 4; y < 11; y++)
				{
					win.second_click_stack = y;
					win.second_click_card = field_stack[y].field.size() - 1;

					playing_rules(field_stack, win);

					if (win.x_mouse == 0 && win.y_mouse == 0)
					{
						no_change = 0;
						something_game = 1;
						break;
					}
				}
				if (win.x_mouse == 0 && win.y_mouse == 0)
				{
					no_change = 0;
					something_game = 1;
					break;
				}
			}
		return something_game;
}

int ki_field_target(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;

	for (int i = 4; i < 11; i++)
	{
		win.x_mouse = 1;
		win.y_mouse = 1;

			win.first_click_stack = i;
			if (field_stack[i].field.size())
			{
				win.first_click_card = field_stack[i].field.size()-1;
			}
			else
			{
				win.first_click_card = 53; //leeres feld für field
			}

			for (int y = 0; y < 4; y++)
			{
				win.second_click_stack = y;
				if (field_stack[y].field.size())
				{
					win.second_click_card = field_stack[y].field.size()-1;
				}
				else
				{
					win.second_click_card = 53; //leeres feld für target
				}

				playing_rules(field_stack, win);

				if (win.x_mouse == 0 && win.y_mouse == 0)
				{
					something_game = 1;
					return something_game;
				}
			}
	}
	return something_game;
}

int ki_deck_target(vector<field_stack>&	field_stack, window& win)
{
	int something_game = 0;

	win.first_click_stack = 11;

	win.x_mouse = 1;
	win.y_mouse = 1;

	if (field_stack[11].field.size() == 0)
	{
		something_game = 0;
		return something_game;
	}

	for (int i = 0; i < field_stack[11].field.size(); i++)
	{
		win.first_click_card = i;

		for (int y = 0; y < 4; y++)
		{
			win.second_click_stack = y;
			win.second_click_card = field_stack[y].field.size() - 1;

			playing_rules(field_stack, win);

			if (win.x_mouse == 0 && win.y_mouse == 0)
			{
				something_game = 1;
				return something_game;
			}
		}
	}
	return something_game;
}


size_t solvealgo(vector<field_stack>&	field_stack, window& win)
{
	int loop_field = 1;
	int loop_deck = 0;
	int loop_field_target = 0;
	int loop_deck_target = 0;
	int unterbrechung = 0;
	int loop_deck_anz = 0;

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
		while (loop_field == 1)
		{
			loop_field = ki_field_field(field_stack, win);/// fehler wenn karte immer verschiebarist!!S
			unterbrechung++;
			if (unterbrechung > 3)
			{
				loop_field = 0;
				break;
			}
		}

		loop_deck_anz = 0;
		loop_deck = 1;
		while (loop_deck == 1)
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
	}

	cout << "\n Herzlichen Glueckwunsch!\n";

	if (field_stack[0].field.empty() || field_stack[1].field.empty() || field_stack[2].field.empty() || field_stack[3].field.empty())
	{
		return 0;
	}
	else
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

}


void	gewonnen()
{
	cout << "***********************************************************\n";
	cout << "				\n Herzlichen Glückwunsch!\n";
	cout << "				\n Sie haben das Spiel gewonnen!\n";
	cout << "*************************************************************";
}

void statistik(vector<field_stack>&	field_stack, window& win)
{
	size_t	n = 10;
	size_t	gewonnen = 0;

	while (n)
	{

		gewonnen += solvealgo(field_stack, win);
		austeilen(field_stack);
		n--;
	}

	cout << "Es wurden:" << gewonnen << "Spiele gewonnen!";
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

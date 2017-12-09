#include "stdafx.h"

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


			while (ziel[(hoch % 8) + 4].get_stack_NOF() == ziel[(hoch % 8) + 4].get_stack_count())
			{
				hoch++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel[(hoch % 8) + 4].field.push_back(jojo);
			ziel[(hoch % 8) + 4].raise_cards();
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

void	move(vector<field_stack>& field_stack, window& win)
{
	Card*	jojo;
	int jojo_card_first = (win.first_click_stack);
	int jojo_card_second = (win.click_stack);

	if ((win.click_stack == 13) || (win.first_click_card == 53))
	{
		win.first_click_stack = 13;
		win.first_click_card = 100;
	}
	else
	{

		if ((win.first_click_stack == 13) || (win.first_click_stack == win.click_stack))
		{
			win.first_click_stack = win.click_stack;
			win.first_click_card = win.click_card;
		}
		else
		{
			//click deck to field 
			if ((win.first_click_stack == 11) && (win.click_stack > 3) && (0 <= win.first_click_card < 53)) // deck to field
			{
				if (((field_stack[jojo_card_first].field.empty() == false) && (field_stack[jojo_card_second].field.empty() == false)) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_colour() != field_stack[jojo_card_second].field.back()->get_card_colour()) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == (field_stack[jojo_card_second].field.back()->get_card_value() - 1)))
				{
					jojo = field_stack[win.first_click_stack].field[win.first_click_card];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

					field_stack[win.click_stack].field.push_back(jojo);
					field_stack[win.click_stack].raise_cards();
				}
				else if ((field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == 13) && (field_stack[jojo_card_second].field.empty() == true))
				{
					jojo = field_stack[win.first_click_stack].field[win.first_click_card];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

					field_stack[win.click_stack].field.push_back(jojo);
					field_stack[win.click_stack].raise_cards();
				}
			}


			if ((win.first_click_stack == 11) && (win.click_stack < 4) && (0 <= win.first_click_card < 53)) // deck to target
			{
				if (field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == 1)
				{
					jojo = field_stack[win.first_click_stack].field[win.first_click_card];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

					// setzt die Ass schon auf das "richtige Feld"

					field_stack[jojo->get_card_colour()].field.push_back(jojo);
				}
				else if ((field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == (field_stack[jojo_card_second].field.back()->get_card_value() + 1)))
				{
					jojo = field_stack[win.first_click_stack].field[win.first_click_card];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

					field_stack[jojo->get_card_colour()].field.push_back(jojo);
				}
				else
				{
					cout << "############################## \n";
					cout << "invalid move, try again! \n";
					cout << "############################## \n";
				}
			}



			// movement field to field 
			if ((win.first_click_stack < 11) && (win.first_click_stack > 3) && (win.click_stack < 11) && (win.click_stack > 3))// field to field
			{
				// @Marcel: Abfrage erweitert; überüprüft ob Karte gelegt werden darf! 

				if (((field_stack[jojo_card_first].field.empty() == false) && (field_stack[jojo_card_second].field.empty() == false)) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_colour() != field_stack[jojo_card_second].field.back()->get_card_colour()) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == (field_stack[jojo_card_second].field.back()->get_card_value() - 1)))
				{
					while (win.first_click_card < field_stack[jojo_card_first].field.size())
					{
						jojo = field_stack[jojo_card_first].field[win.first_click_card];
						// clear the top card of the stack 
						field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

						field_stack[jojo_card_second].field.push_back(jojo);
						field_stack[jojo_card_second].raise_cards();
					}

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s - 1]->undiscover_card();
					}
				}

				// look after valid move, look for King to empty field
				else if ((field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == 13) && (field_stack[jojo_card_second].field.empty() == true))
				{
					// get the top card of the actual stack 
					while (win.first_click_card < field_stack[jojo_card_first].field.size())
					{
						jojo = field_stack[jojo_card_first].field[win.first_click_card];
						// clear the top card of the stack 
						field_stack[jojo_card_first].field.erase(field_stack[win.first_click_stack].field.begin() + win.first_click_card);

						field_stack[jojo_card_second].field.push_back(jojo);
						field_stack[jojo_card_second].raise_cards();
					}

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s - 1]->undiscover_card();
					}
				}
				else
				{
					cout << "############################## \n";
					cout << "invalid move, try again! \n";
					cout << "############################## \n";
				}



			}



			if ((win.first_click_stack < 4) && (win.click_stack < 11) && (win.click_stack > 3) && win.first_click_card < 53) //target to field übergabe
			{
				if (((field_stack[jojo_card_first].field.empty() == false) && (field_stack[jojo_card_second].field.empty() == false)) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_colour() != field_stack[jojo_card_second].field.back()->get_card_colour()) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == (field_stack[jojo_card_second].field.back()->get_card_value() - 1)))
				{
					jojo = field_stack[(win.first_click_stack)].field.back();
					// clear the top card of the stack 
					field_stack[(win.first_click_stack)].field.pop_back();

					field_stack[win.click_stack].field.push_back(jojo);
					field_stack[win.click_stack].raise_cards();
				}
				else
				{
					cout << "############################## \n";
					cout << "invalid move, try again! \n";
					cout << "############################## \n";
				}
			}



			if ((win.first_click_stack > 3) && (win.first_click_stack < 11) && (win.click_stack < 4) && win.first_click_card < 53) // field to target_stack übergabe
			{
				if (((field_stack[jojo_card_first].field.empty() == false) && (field_stack[jojo_card_second].field.empty() == false)) &&
					(field_stack[jojo_card_first].field.at(win.first_click_card)->get_card_value() == (field_stack[jojo_card_second].field.back()->get_card_value() + 1)))
				{
					// get the top card of the actual stack 
					jojo = field_stack[win.first_click_stack].field.back();
					// clear the top card of the stack 
					field_stack[win.first_click_stack].field.pop_back();

					field_stack[jojo->get_card_colour()].field.push_back(jojo);

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s - 1]->undiscover_card();
					}
				}
				else
				{
					cout << "############################## \n";
					cout << "invalid move, try again! \n";
					cout << "############################## \n";
				}
			}



			win.first_click_stack = 13; //rücksetzen des ersen clicks
			win.first_click_card = 100;

			win.x_mouse = 0;
			win.y_mouse = 0;

		}
	}

	if (win.click_stack == 11 && win.click_card == 53) //mausklick auf verdecktes deck
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

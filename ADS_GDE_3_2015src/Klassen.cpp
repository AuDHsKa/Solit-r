#include "stdafx.h"
#include "Klassen.h"
#include <iostream>

/********************************************************************************
	Class Cards		occupy the play cards
********************************************************************************/

void	Card::set_card_colour(suit col)
{
	colour = col;
}

void	Card::set_card_value(val val)
{
	value = val;
}

void	Card::hide_card()
{
	hidden = true;
}

void	Card::undiscover_card()
{
	hidden = false;
}

suit		Card::get_card_colour()
{
	return colour;
}

val		Card::get_card_value()
{
	return value;
}

bool	Card::is_card_hidden()
{
	return	hidden;
}



/********************************************************************************
			field_stack		occupy the play cards
********************************************************************************/

void	field_stack::set_stack_count(size_t c)
{
	count = c;
}

void	field_stack::set_cards_hidden(size_t c)
{
	cards_hidden = c;
}

void	field_stack::raise_hidden_cards()
{
	cards_hidden++;
}


void	field_stack::reduce_hidden_cards()
{
	cards_hidden--;
}


size_t	field_stack::get_stack_count()
{
	return count;
}

size_t	field_stack::get_cards_hidden()
{
	return cards_hidden;
}



/********************************************************************************
		functions for operate with cards and stacks
********************************************************************************/

void	show_cards(Card*	rd, size_t	length)
{
	string	farbe, wert;
	for (size_t i = 0; i < length; i++)
	{

		// Dient nur zur anschaulichkeit bei der Konsolenausgabe zur schnelleren Ueberpruefung 
		switch (rd[i].get_card_colour())
		{
			// Gibt den nummern einen Namen
		case	0:	farbe = "Karo";
			break;
		case	1:	farbe = "Herz";
			break;
		case	2:	farbe = "Spades";
			break;
		case	3:	farbe = "Kreutz";
			break;
		default:
			break;
		}

		cout << "The colour of card " << i + 1 << " is " << farbe << "\n";

		// Dient nur zur anschaulichkeit bei der Konsolenausgabe zur schnelleren Ueberpruefung 
		if (rd[i].get_card_value() > 10 || rd[i].get_card_value() == 1)
		{
			switch (rd[i].get_card_value())
			{
				// Gibt den nummern einen Namen
			case	1:	wert = "Ass";
				break;
			case	11:	wert = "Bube";
				break;
			case	12:	wert = "Dame";
				break;
			case	13:	wert = "Koenig";
				break;
			default:
				break;
			}
			cout << "The value of card " << i + 1 << " is " << wert << "\n";
		}
		else
		{
			cout << "The value of card " << i + 1 << " is " << rd[i].get_card_value() << "\n";
		}
	}
}

void	initialize_cards(vector<Card>&	ca)
{
	int		count = 0;
	suit	col;
	val	num;

	for (int yy = 0; yy < 4; yy++)
	{
		switch (yy)
		{
		case	0:	col = diamonds;
			break;
		case	1:	col = spades;
			break;
		case	2:	col = hearts;
			break;
		case	3:	col = clubs;
			break;
		default:
			break;
		}

		for (int ii = 0; ii < 13; ii++)
		{
			num = (val)(ii + 1);
			ca[13 * yy + ii].set_card_colour(col);
			ca[13 * yy + ii].set_card_value(num);
		}
	}
}

window::window()
{
}


window::~window()
{
}

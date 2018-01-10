#include "stdafx.h"


#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__


/***************************************************************************************
Funktion:				void	mein_austeilen(vector<field_stack>& ziel)
Bestimmung/Zweck:		teilt die Karten auf dem Spielfeld aus
Eingangsparameter:		field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/

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

	// time(NULL) und "time.h" eingefügt, füe immer andere Zufallszahl
	srand(time(NULL));

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

/***************************************************************************************
Funktion:				void	austeilen(vector<field_stack>& ziel)
Bestimmung/Zweck:		teilt die Karten auf dem Spielfeld aus
Eingangsparameter:		field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/

void	austeilen(vector<field_stack>& ziel)
{
	size_t	pp = 0;
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;

	// eingefügt 
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

/***************************************************************************************
Funktion:				void	clear_field(vector<field_stack>&	field_stack)
Bestimmung/Zweck:		löscht die Karten auf dem Feld und dem Zielstack
Eingangsparameter:		field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/

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

/***************************************************************************************
Funktion:				void	initialize_field(vector<field_stack>&	field_stack)
Bestimmung/Zweck:		initialisiert die Klasse field_stack mit der Anzahl der Karten, 
						welche beim Auslegen auf dem entsprechenden Feld erlaubt sind
Eingangsparameter:		field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/

void	initialize_field(vector<field_stack>&	field_stack)
{
	for (size_t i = 4; i < 11; i++)
	{
		field_stack.at(i).set_stack_count(i - 3);
	}

	field_stack.at(11).set_stack_count(24);
}

/********************************************************************************************************************
Funktion:				void	initialize_target(vector<field_stack>& field_stack, vector<Card>& cards)
Bestimmung/Zweck:		initialisiert die Zielstapel mit den Karten in der richtigen Reihenfolge
Eingangsparameter:		field_stack, cards
Ausgangsparameter:		kein Rückgabewert
*********************************************************************************************************************/

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

/*************************************************************************************
Funktion:				void	set_win_clicks(window& win)
Bestimmung/Zweck:		initialisiert die Mausklicks auf die default Werte
Eingangsparameter:		win
Ausgangsparameter:		kein Rückgabewert
**************************************************************************************/

void	set_win_clicks(window& win)
{
	win.first_click_card = 100;
	win.first_click_stack = 13;
	win.second_click_card = 100;
	win.second_click_stack = 13;
}
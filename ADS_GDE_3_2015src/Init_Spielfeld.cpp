#include "stdafx.h"


#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__


/***************************************************************************************
Funktion:				void	austeilen(vector<field_stack>& ziel)
Bestimmung/Zweck:		teilt die Karten auf dem Spielfeld aus
Eingangsparameter:		field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/

void	austeilen(vector<field_stack>& ziel)
{
	size_t	pp = 0;
	size_t	min = 0;		// minimalzahl der pseudozufallsvariable
	size_t	max = 7;		// maximalzahl der pseudozufallsvariable
	size_t	hoch = 0;		// Pseudozufallsvariable
	size_t	iii = 0;
	Card*	jojo;			// zwischenspeicher einer Kartenreferenz

	// eingefügt; holt die aktuelle Zeit
	srand(time(NULL));

	// take every card of every stack on the target field 
	for (size_t i = 0; i < 52; i++)
	{
		
			hoch = min + rand() % (max - min + 1);		// die Pseudozufallszahl im Interval [min;max] wird gebildet

			while (ziel.at(hoch % 4).field.empty())		// es wird geprüft, ob der Zielstapel auf den man zugreifen möchte leer ist
			{
				hoch++;									// wenn der Stapel leer ist, erhöhe die zufallszahl => gehe zum nächsten Stapel
			}

			jojo = ziel.at(hoch % 4).field.back();		// hole die oberste Karte vom Zielstapel
			ziel.at(hoch % 4).field.pop_back();			// lösche die oberste Karte vom Zielstapel

			while (ziel.at((hoch % 8) + 4).field.size() == ziel.at((hoch % 8) + 4).get_stack_count())	// Überprüft, ob der Feldstapel die maximalanzahl an karten bereits aufgenommen hat
			{
				hoch++;									// wenn der Stapel "voll" ist, erhöhe die Variable => gehe zum nächsten Feldstapel
			}

			// set the card from target stack on the (hoch) field stack
			ziel.at((hoch % 8) + 4).field.push_back(jojo);				// lege die Ausgewählte Karte oben auf den neuen Feldstapel
	}


	// verdecke alle Karten auf den Feldstapel, bis auf die oberste
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
		if (!(field_stack.at(yy).field.empty()))		// wenn der Stapel nicht leer ist, leere ihn 
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
		field_stack.at(i).set_stack_count(i - 3);		// setze die Anzahl an Karten, welche beim Auslegen auf diesem Stapel erlaubt sind
	}

	field_stack.at(11).set_stack_count(24);				// setze die Anzahl an Karten, welche beim Auslegen auf diesem Stapel erlaubt sind
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
			field_stack.at(yy).field.push_back(&cards.at(13 * yy + ii));		// lege die Refernez der Karten in der Richtigen Reihenfolge auf die Zielstapel
			field_stack.at(yy).field.at(ii)->undiscover_card();					// decke alle Karten auf den Zielstapel auf
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
	win.first_click_card = 100;			// lege einen Defaultwert für die Mausclicks fest
	win.first_click_stack = 13;			// lege einen Defaultwert für die Mausclicks fest
	win.second_click_card = 100;		// lege einen Defaultwert für die Mausclicks fest
	win.second_click_stack = 13;		// lege einen Defaultwert für die Mausclicks fest
}
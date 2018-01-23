#include "stdafx.h"
#include <string>
#include <vector>

#define		__Klassen__
//#define Auswerten
#define mydistri
//#define zufall

using namespace std;

/*!
**	The colour of the cards
**	Representiert die Farbe der Spielkarten
!*/

enum suit { diamonds, spades, hearts, clubs };

/*!
**	The value of the cards
**	Representiert die Werte der Spielkarten
!*/

enum val { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };

/*!
*	Class Card:
*	The
!*/

class	Card									// beschreibt die einzelne Karte
{
private:

	suit	colour;								// enthält die "Farbe" der Spielkarten (Herz, Kreutz) 
	val		value;								// enthält den Wert der Spielkarte (z.B. König, Dame, Bube) 
	bool	hidden;								// beschreibt ob die Karte verdeckt (true) oder offen (false) ist 

public:

	void	set_card_colour(suit col);			// initialisiert die Karte mit der entsprechenden Farbe
	void	set_card_value(val val);			// initialisiert die Karte mit dem entsprechenden Wer
	void	hide_card();						// verdeckt die Karte
	void	undiscover_card();					// legt die Karte offen
	suit	get_card_colour();					// gibt die Farbe der Karte zurück
	val		get_card_value();					// gibt den Wert der Karte zurück
	bool	is_card_hidden();					// gibt an, ob die Karte verdeckt ist (true)
};


class	field_stack								// beschreibt die Spielstapel auf dem Feld
{
private:
	size_t		count;							// the number of cards which are allowed to stay at this stack
	size_t		cards_hidden;					// gibt an, wie viel Karten auf dem Stapel verdeckt sind

public:
	vector<Card*>	field;						// der Stapel an sich, welcher die Zeiger auf die Karten enthält
	void	set_stack_count(size_t c);			// initialisiert den Stapel mit der Anzahl an Karten, welche beim Austeilen auf dem Stapel erlaubt sind
	void	set_cards_hidden(size_t c);			// initialisiert den Stapel mit der Anzahl an Karten, welche beim Austeilen auf dem Stapel verdeckt sind
	void	raise_hidden_cards();				// erhöhe die Anzahl an verdeckten Karten
	void	reduce_hidden_cards();				// veringere die Anzahl an verdeckten Karten
	size_t	get_stack_count();					// gibt die Anzahl an Karten zurück, welche beim Austeilen auf dem Stack erlaubt sind
	size_t	get_cards_hidden();					// gibt die Anzahl an Karten zurück, welche beim Austeilen auf dem Stack verdeckt sind 
};

void	initialize_cards(vector<Card>&	ca);

void	show_cards(Card*	rd, size_t	length);

class window
{
public:
	window();
	~window();

	int wide;
	int height;

	int x_mouse;
	int y_mouse;

	int test;
	int first_click_stack;
	int first_click_card;
	int second_click_stack;
	int second_click_card;
	size_t statistik;

	Card*	old_card_one;
	Card*	old_card_second;

};

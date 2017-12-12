#include "stdafx.h"
#include <string>
#include <vector>

#define		__Klassen__

using namespace std;

/*!
**	The colour of the cards
!*/

enum suit { diamonds, spades, hearts, clubs };

/*!
**	The value of the cards
!*/

enum val { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };

/*!
*	Class Card:
*	The
!*/

class	Card
{
private:

	suit	colour;
	val		value;
	bool	hidden;

public:

	void	set_card_colour(suit col);
	void	set_card_value(val val);
	void	hide_card();
	void	undiscover_card();
	suit	get_card_colour();
	val		get_card_value();
	bool	is_card_hidden();
};


class	field_stack
{
private:
	size_t		count;							// the number of cards which are allowed to stay at this stack
	size_t		cards_hidden;

public:
	vector<Card*>	field;
	void	set_stack_count(size_t c);
	void	set_cards_hidden(size_t c);
	void	raise_hidden_cards();
	void	reduce_hidden_cards();
	size_t	get_stack_count();
	size_t	get_cards_hidden();
};

void	initialize_cards(vector<Card>&	ca);

void	show_cards(Card*	rd, size_t	length);
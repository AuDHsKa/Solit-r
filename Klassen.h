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
	//Card(suit col, val val, bool hide){
	//	set_card_color(col);
	//	set_card_value(val);
	//	hide_card();
	//};
};

//Card(suit cool, val vaal, bool hide)
//{
//	Card::set_card_color(col);
//	Card::set_card_value(val);
//	Card::hide_card();
//}




class	field_stack
{
private:
	size_t		count;							// the number of cards which are allowed to stay at this stack
	size_t		number_of_cards;				// the number of cards which are actually on this stack
	size_t		cards_hidden;
	size_t		cards_open;

public:
	vector<Card*>	field;
	void	set_stack_count(size_t c);
	void	set_stack_NOF(size_t nof);
	void	raise_cards();
	size_t	get_stack_count();
	size_t	get_stack_NOF();
	size_t	get_cards_hidden();
	size_t	get_cards_open();



	//field_stack(size_t co)
	//{
	//	field_stack::set_stack_count(co);
	//};
	//field_stack();
	//~field_stack();
};

//class	field_stack
//{
//private:
//	int		count;							// the number of cards which are allowed to stay at this stack
//	int		number_of_cards;				// the number of cards which are actually on this stack
//	//int		cards_hidden;					
//	//int		cards_open;
//	deque<Card>	*list;
//
//public:
//	void	set_stack_count(int c);
//	void	set_stack_NOF(int nof);
//
//	void	insert_card_end(Card* li);
//	void	remove_card_end();
//	Card	get_card();
//};

void	initialize_cards(vector<Card>&	ca);

void	show_cards(Card*	rd, size_t	length);
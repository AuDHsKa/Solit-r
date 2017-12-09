#include "stdafx.h"
#include <stack>
#include <iostream>

#ifndef __Klassen__
	#include "Klassen.h"
#endif // !__Klassen__


void	austeilen(vector<field_stack>& ziel);

void	move(int mclick[2], int mclick_first[2], vector<field_stack>& ziel);

void	take_card_from_field_to_field(vector<field_stack>&	f1);

void	take_card_from_deck_to_field(vector<field_stack>&	f1);
#include "stdafx.h"
#include <stack>
#include <iostream>

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__


void	austeilen(vector<field_stack>& ziel);

void	take_card_from_field_to_field(vector<field_stack>&	f1);

void	take_card_from_deck_to_field(vector<field_stack>&	f1);

void	move(vector<field_stack>& ziel, window& win);

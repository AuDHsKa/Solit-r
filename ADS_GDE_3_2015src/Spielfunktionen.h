#include "stdafx.h"
#include <stack>
#include <iostream>

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#ifndef __window__
#include "window.h"
#endif

void	austeilen(vector<field_stack>& ziel);

void	move(vector<field_stack>& ziel, window& win);

void	take_card_from_field_to_field(vector<field_stack>&	f1);

void	take_card_from_deck_to_field(vector<field_stack>&	f1);

void	solvealgo ( vector<field_stack>&	f1, window& win);


#include "stdafx.h"


#ifndef __Klassen__
	#include "Klassen.h"
#endif // !__Klassen__


void	copy_cards(vector<Card>& origin, vector<Card*>& copy);

void	zuf_austeilen(vector<field_stack>& ziel);

void	austeilen(vector<field_stack>& ziel);

void	clear_field(vector<field_stack>&	field_stack);

void	initialize_field(vector<field_stack>&	field_stack);

void	initialize_target(vector<field_stack>& field_stack, vector<Card>& cards);

void	set_win_clicks(window& win);
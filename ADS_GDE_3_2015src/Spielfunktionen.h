#include "stdafx.h"
#include <stack>
#include <iostream>

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#ifndef __window__
#include "window.h"
#endif

void	copy_cards(vector<Card>& origin, vector<Card*>& copy);

void	zuf_austeilen(vector<field_stack>& ziel);

void	austeilen(vector<field_stack>& ziel);

void	playing_rules(vector<field_stack>& ziel, window& win);

void window_move(vector<field_stack>& field_stack, window& win);

void	move_cards(vector<field_stack>& ziel, window& win);

size_t	solvealgo(vector<field_stack>&	f1, window& win);

void	statistik(vector<field_stack>&	field_stack, window& win, vector<Card>& cards);

size_t	look_for_game_won(vector<field_stack>&	field_stack);

void	gewonnen();

void	clear_field(vector<field_stack>&	field_stack);

void	initialize_field(vector<field_stack>&	field_stack);

void	initialize_target(vector<field_stack>& field_stack, vector<Card>& cards);

void	set_win_clicks(window& win);


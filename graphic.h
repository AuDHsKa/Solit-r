#ifndef __Klassen__
	#include "Klassen.h"
#endif

#ifndef stack
	#include <stack>
#endif

void newwindow(int b, int h); //  windowsweite, windowshöhe

int button(int x, int y, int b, int h); // maus x, maus y, windowsweite, windowshöhe

void w_target_field(int x, int y, stack<Card*>* tsp, int target_field);

void w_field(int x, int y, vector<field_stack>& f1, int feld);


void w_deck(int x,int  y, vector<field_stack>& deck);

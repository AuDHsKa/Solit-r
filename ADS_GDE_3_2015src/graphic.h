#ifndef __Klassen__
	#include "Klassen.h"
#endif

#ifndef stack
	#include <stack>
#endif

void fieldclick(int x, int y, int mclick[2], stack<Card*>* target_stack, vector<field_stack>& field_stack);//ruft alle funktionen auf

void newwindow(int b, int h); //  windowsweite, windowshöhe

int button(int x, int y, int b, int h); // maus x, maus y, windowsweite, windowshöhe

int w_target_field(int x, int y, stack<Card*>* tsp, int target_field);

int w_field(int x, int y, vector<field_stack>& f1, int feld);

int w_deck(int x,int  y, vector<field_stack>& deck);

#ifndef __Klassen__
	#include "Klassen.h"
#endif

#ifndef stack
	#include <stack>
#endif

void fieldclick(int x, int y, int mclick[2], vector<field_stack>& field_stack, int windowswide, int windowsheight);//ruft alle funktionen auf

void newwindow(int b, int h); //  windowsweite, windowshöhe

int button(int x, int y, int b, int h); // maus x, maus y, windowsweite, windowshöhe

int w_target_field(int x, int y, vector<field_stack>& tsp, int target_field);

int w_field(int x, int y, vector<field_stack>& f1, int feld);

int w_deck(int x,int  y, vector<field_stack>& deck);

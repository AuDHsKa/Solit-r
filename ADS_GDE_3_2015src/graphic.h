#ifndef __Klassen__
#include "Klassen.h"
#endif

#ifndef stack
#include <stack>
#endif

#ifndef __window__
#include "window.h"
#endif

void click_window(vector<field_stack>& field_stack, window& win);//ruft alle funktionen auf

void newwindow(window& win); //  windowsweite, windowshöhe

int button(window& win); // maus x, maus y, windowsweite, windowshöhe

int w_field(int x, int y, vector<field_stack>& f1, int feld);

int w_deck(int x, int  y, vector<field_stack>& deck);

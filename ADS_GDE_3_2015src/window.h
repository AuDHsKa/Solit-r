#pragma once
#include "stdafx.h"
#include <string>
#include <vector>

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__


#define __window__


class window
{
public:
	window();
	~window();

	int wide;
	int height;

	int x_mouse;
	int y_mouse;
	
	int test;
	int first_click_stack;
	int first_click_card;
	int second_click_stack;
	int second_click_card;

	Card*	old_card_one;
	Card*	old_card_second;

};


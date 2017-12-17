#pragma once
#include "stdafx.h"
#include <string>
#include <vector>

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
	int old_move_stack_1 = 0;
	int old_move_card_1 = 0;
	int old_move_stack_2 = 0;
	int old_move_card_2 = 0;

};


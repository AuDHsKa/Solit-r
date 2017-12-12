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

	int first_click_stack;
	int first_click_card;
	int second_click_stack;
	int second_click_card;

};


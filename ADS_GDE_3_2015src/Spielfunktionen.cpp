#include "stdafx.h"

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#include <stack>
#include <iostream>

void	austeilen(stack<Card*>* start, vector<field_stack>& ziel)
{
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;


	// take every card of every stack on the target field 
	for (size_t i = 0; i < 13; i++)
	{
		// go for every stack on the target field
		for (size_t ii = 0; ii < 4; ii++)
		{

			hoch = min + rand() % (max - min + 1);

			// get the top card of the actual stack 
			jojo = start[ii].top();
			// clear the top card of the stack 
			start[ii].pop();

			//// ask if the field stack is full (begin of a game)
			//if (field_stack[hoch % 7].get_stack_NOF() == field_stack[hoch % 7].get_stack_count())
			//{
			//	hoch++;
			//	cout << "gleich\n";
			//}

			while ((ziel[hoch % 8].get_stack_NOF() == ziel[hoch % 8].get_stack_count()))
			{
				hoch++;
				//cout << "gleich\n";
				//iii++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel[hoch % 8].field.push_back(jojo);
			ziel[hoch % 8].raise_cards();
			hoch++;
		}

	}
}
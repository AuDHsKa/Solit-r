#include "stdafx.h"

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#include <stack>
#include <iostream>

#ifndef graphic.h
#include "graphic.h"
#endif // !graphic.h



void	austeilen(stack<Card*>* start, vector<field_stack>& ziel)
{
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;

	// eingefügt 
	srand(time(NULL));

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

void	move(int mclick[2], int mclick_first[2], stack<Card*>* target_stack, vector<field_stack>& field_stack)
{
	Card*	jojo;
	int jojo_card_first = (mclick_first[0]-5);
	int jojo_card_second = (mclick[0] - 5);

	if ( (mclick[0] == 0) || (mclick_first[1] == 53))
	{
		mclick_first[0] = 0;
		mclick_first[1] = 100;
	}
	else
	{
		
		if ( (mclick_first[0] == 0) || (mclick_first[0] == mclick[0]) )
		{
				mclick_first[0] = mclick[0];
				mclick_first[1] = mclick[1];
		}
		else
		{
				if ((mclick_first[0] == 12) && (mclick_first[1] == 1)) // deck to field
				{
					jojo = field_stack[jojo_card_first].field.back();
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.pop_back();

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();
				}    

				if ((mclick_first[0] < 12) && (mclick[0] < 12) && (mclick_first[0] > 4) && (mclick[0] > 4))// field to field
				{
					// get the top card of the actual stack 
					jojo = field_stack[jojo_card_first].field.back();
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.pop_back();

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();

				}

				if ((mclick_first[0] < 5) && (mclick[0] < 12) && (mclick[0] > 4) && mclick_first[1] < 53) //target to field übergabe
				{
					jojo = target_stack[ (mclick_first[0]-1) ].top();
					// clear the top card of the stack 
					target_stack[ (mclick_first[0]-1) ].pop();

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();
				}

				if ((mclick_first[0] > 5) && (mclick[0] < 5) && mclick_first[1] < 53) //target to field übergabe
				{
					// get the top card of the actual stack 
					jojo = field_stack[jojo_card_first].field.back();
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.pop_back();

					target_stack[(mclick[0]-1)].push(jojo);
				}

				fieldclick(0, 0, mclick, target_stack, field_stack, 700, 600);

				mclick_first[0] = 0;
				mclick_first[1] = 100;
		}
	}


}
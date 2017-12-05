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

			while ( ziel[hoch % 8].get_stack_NOF() == ziel[hoch % 8].get_stack_count() )
			{
				hoch++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel[hoch % 8].field.push_back(jojo);
			ziel[hoch % 8].raise_cards();
		}

	}

	for (size_t i = 1; i < 8; i++)
	{
		for (size_t ii = 0; ii < (ziel[i].field.size()-1); ii++)
		{
			ziel[i].field[ii]->hide_card();
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
				if ((mclick_first[0] == 12) && (mclick[0] > 4) && (0 < mclick_first[1] < 53)) // deck to field
				{
					jojo = field_stack[jojo_card_first].field[mclick_first[1]];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[jojo_card_first].field.begin()+mclick_first[1]);

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();
				}    

				if ((mclick_first[0] == 12) && (mclick[0] < 5) && (0 < mclick_first[1] < 53)) // deck to target
				{
					jojo = field_stack[jojo_card_first].field[mclick_first[1]];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[jojo_card_first].field.begin() + mclick_first[1]);

					target_stack[(mclick[0] - 1)].push(jojo);
				}

				if ((mclick_first[0] < 12)  && (mclick_first[0] > 4) && (mclick[0] < 12) && (mclick[0] > 4))// field to field
				{
					// get the top card of the actual stack 
					jojo = field_stack[jojo_card_first].field.back();
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.pop_back();

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s-1]->undiscover_card();
					}
					

				}


				if ((mclick_first[0] < 5) && (mclick[0] < 12) && (mclick[0] > 4) && mclick_first[1] < 53) //target to field übergabe
				{
					jojo = target_stack[ (mclick_first[0]-1) ].top();
					// clear the top card of the stack 
					target_stack[ (mclick_first[0]-1) ].pop();

					field_stack[jojo_card_second].field.push_back(jojo);
					field_stack[jojo_card_second].raise_cards();
				}

				if ((mclick_first[0] > 4) && (mclick_first[0] < 12) && (mclick[0] < 5) && mclick_first[1] < 53) // field to target_stack übergabe
				{
					// get the top card of the actual stack 
					jojo = field_stack[jojo_card_first].field.back();
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.pop_back();

					target_stack[(mclick[0]-1)].push(jojo);

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s - 1]->undiscover_card();
					}
				}

				fieldclick(0, 0, mclick, target_stack, field_stack, 700, 600);

				mclick_first[0] = 0;
				mclick_first[1] = 100;
		}
	}

	if ( mclick[0] == 12 && mclick[1] == 0) //mausklick auf verdecktes deck
	{
		int c = 0;

		for (int i = 0; i < field_stack[7].field.size(); i++)
		{
			if ((field_stack[7].field[i]->is_card_hidden()) == 1)
			{
				c++;
			}
		}

		if (c == 0)
		{
			for (size_t i = 0; i < (field_stack[7].field.size()); i++)
			{
				field_stack[7].field[i]->hide_card();
			}
		}
		else
		{
			field_stack[7].field[c-1]->undiscover_card();
		}

		fieldclick(0, 0, mclick, target_stack, field_stack, 700, 600);

		mclick_first[0] = 0;
		mclick_first[1] = 100;
	}


}

//void	Spielregeln(int mclick[2], int mclick_first[2])
#include "stdafx.h"

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#include <stack>
#include <iostream>

#ifndef graphic.h
#include "graphic.h"
#endif // !graphic.h



void	austeilen(vector<field_stack>& ziel)
{
	size_t	min = 0;
	size_t	max = 7;
	size_t	hoch = 0;
	size_t	iii = 0;
	Card*	jojo;

	// eingefügt 
	srand(time_t(NULL));

	// take every card of every stack on the target field 
	for (size_t i = 0; i < 13; i++)
	{
		// go for every stack on the target field
		for (size_t ii = 0; ii < 4; ii++)
		{

			hoch = min + rand() % (max - min + 1);

			jojo = ziel[ii].field.back();
			ziel[ii].field.pop_back();

			//// get the top card of the actual stack 
			//jojo = start[ii].top();
			//// clear the top card of the stack 
			//start[ii].pop();

			while ( ziel[(hoch % 8) + 4].get_stack_NOF() == ziel[(hoch % 8) + 4].get_stack_count() )
			{
				hoch++;
			}

			// set the card from target stack on the (hoch) field stack
			ziel[(hoch % 8) + 4].field.push_back(jojo);
			ziel[(hoch % 8) + 4].raise_cards();
		}

	}

	for (size_t i = 4; i < 12; i++)
	{
		for (size_t ii = 0; ii < (ziel[i].field.size()-1); ii++)
		{
			ziel[i].field[ii]->hide_card();
		}
	}
}

void	move(int mclick[2], int mclick_first[2], vector<field_stack>& field_stack)
{
	Card*	jojo;
	int jojo_card_first = (mclick_first[0]);
	int jojo_card_second = (mclick[0]);

	if ( (mclick[0] == 13) || (mclick_first[1] == 53))
	{
		mclick_first[0] = 13;
		mclick_first[1] = 100;
	}
	else
	{
		
		if ( (mclick_first[0] == 13) || (mclick_first[0] == mclick[0]) )
		{
				mclick_first[0] = mclick[0];
				mclick_first[1] = mclick[1];
		}
		else
		{
				if ((mclick_first[0] == 11) && (mclick[0] > 3) && (0 < mclick_first[1] < 53)) // deck to field
				{
					jojo = field_stack[mclick_first[0]].field[mclick_first[1]];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[mclick_first[0]].field.begin()+mclick_first[1]);

					field_stack[mclick[0]].field.push_back(jojo);
					field_stack[mclick[0]].raise_cards();
				}    

				if ((mclick_first[0] == 11) && (mclick[0] < 4) && (0 < mclick_first[1] < 53)) // deck to target
				{
					jojo = field_stack[mclick_first[0]].field[mclick_first[1]];
					// clear the top card of the stack 
					field_stack[jojo_card_first].field.erase(field_stack[mclick_first[0]].field.begin() + mclick_first[1]);

					field_stack[mclick[0]].field.push_back(jojo);
				}

				if ((mclick_first[0] < 11)  && (mclick_first[0] > 3) && (mclick[0] < 11) && (mclick[0] > 3))// field to field
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


				if ((mclick_first[0] < 4) && (mclick[0] < 11) && (mclick[0] > 3) && mclick_first[1] < 53) //target to field übergabe
				{
					jojo = field_stack[ (mclick_first[0]) ].field.back();
					// clear the top card of the stack 
					field_stack[ (mclick_first[0]) ].field.pop_back();

					field_stack[mclick[0]].field.push_back(jojo);
					field_stack[mclick[0]].raise_cards();
				}

				if ((mclick_first[0] > 3) && (mclick_first[0] < 11) && (mclick[0] < 4) && mclick_first[1] < 53) // field to target_stack übergabe
				{
					// get the top card of the actual stack 
					jojo = field_stack[mclick_first[0]].field.back();
					// clear the top card of the stack 
					field_stack[mclick_first[0]].field.pop_back();

					field_stack[mclick[0]].field.push_back(jojo);

					size_t s = field_stack[jojo_card_first].field.size(); // nächste karte umdrehen
					if (s)
					{
						field_stack[jojo_card_first].field[s - 1]->undiscover_card();
					}
				}

				fieldclick(0, 0, mclick, field_stack, 700, 600);

				mclick_first[0] = 13;
				mclick_first[1] = 100;
		}
	}

	if ( mclick[0] == 11 && mclick[1] == 0) //mausklick auf verdecktes deck
	{
		int c = 0;

		for (size_t i = 0; i < field_stack[11].field.size(); i++)
		{
			if ((field_stack[11].field[i]->is_card_hidden()) == 1)
			{
				c++;
			}
		}

		if (c == 0)
		{
			for (size_t i = 0; i < (field_stack[11].field.size()); i++)
			{
				field_stack[11].field[i]->hide_card();
			}
		}
		else
		{
			field_stack[11].field[c-1]->undiscover_card();
		}

		fieldclick(0, 0, mclick, field_stack, 700, 600);

		mclick_first[0] = 0;
		mclick_first[1] = 100;
	}


}

//void	Spielregeln(int mclick[2], int mclick_first[2])
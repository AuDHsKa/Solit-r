#include <stdio.h>

#ifndef __k7scan2__
	#include "k7scan2.h"
#endif // !k7scan2.h

void	read_data(vector<Card>& arr, stack<Card*>*	target_stack, vector<field_stack>& feld);

void	write_data(vector<Card>& arrW, stack<Card*>*	target_stackW, vector<field_stack>& feldW);

char* zeit();

void output(char *karten, char * name);

void	delete_data(vector<Card>& arrd, stack<Card*>*	target_stackd, vector<field_stack>& feldd);

void	write_log_data();
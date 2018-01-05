#include <stdio.h>

#ifndef __k7scan2__
#include "k7scan2.h"
#endif // !k7scan2.h
#define		__einaus__

#ifndef __window__
#include "window.h"
#endif

void	get_arr(vector<Card>& arrl);

void	read_data(vector<field_stack>& feld);

void	write_data(vector<field_stack>& feldW);

char*	zeit();

void	output(char *karten, char * name);

void	delete_data(vector<field_stack>& feldd);

void	write_log_data(vector<field_stack>& feldl, window& wind);
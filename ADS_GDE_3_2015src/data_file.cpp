#include "stdafx.h"
#include "data_file.h"

#include <stack>
#include <iostream>
#include <string>
#include <map>
#include <deque>

#include <vector>

#ifndef __Klassen__
#include "Klassen.h"
#endif

#ifndef __k7scan2__
#include "k7scan2.h"
#endif 
using namespace std;

void read_file(vector<Card>& cards)
{
	FILE *inf;
	char fistr[100];
	printf("Enter filename:\n");
	gets_s(fistr);

	inf = fopen(fistr, "r");
	if (inf == NULL) {
		printf("Cannot open input file %s\n", fistr);

	}

	//cout << cards<< "\n";
	CParser obj;
	//obj.uebergabe(cards);
	//obj.InitParse(inf, stderr, stdout);


	// obj.pr_tokentable();

	//obj.yyparse();
}


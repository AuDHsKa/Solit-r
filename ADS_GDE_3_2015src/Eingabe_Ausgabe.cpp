#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>//ctime.h
#ifndef __Klassen__
#include "Klassen.h"
#endif
#ifndef __k7scan2__
#include "k7scan2.h"
#endif // !k7scan2.h


/*
//David Kommentar
*/
void	read_data(vector<Card>& arr, stack<Card*>*	target, vector<field_stack>& feld)
{
	FILE *inf;
	char fistr[100] = "";
	printf("Enter filename:\n");
	gets(fistr);
	if (strlen(fistr) == 0) strcpy(fistr, "in1.txt");
	inf = fopen(fistr, "r");
	if (inf == NULL){
		printf("Cannot open input file %s\n", fistr);
		//return 0;
	}
	CParser obj;
	//obj.uebergabe(arr);
	obj.InitParse(inf, stderr, stdout);
	//	obj.pr_tokentable();
	obj.yyparse(arr,feld,target);
	//char c; cin >> c;
	fclose(inf);

	//return 0;
}
char*  zeit()
{
	int jetzt;
	int YY;
	int MM;
	int TT;
	int hh;
	int mm;
	int se;
	char ccw[100];
	char ddw[100];
	char* cct;
	char* dd;
	time_t sekunden = time(NULL);
	tm *uhr = localtime(&sekunden);
	se = uhr->tm_sec;
	mm = uhr->tm_min;
	hh = uhr->tm_hour;
	TT = uhr->tm_mday;
	MM = uhr->tm_mon;
	YY = uhr->tm_year;
	cct = itoa((YY + 1900), ccw, 10);
	dd = itoa((MM + 1), ddw, 10);
	strcat(cct, dd);
	dd = itoa(TT, ddw, 10);
	strcat(cct, dd);
	dd = itoa(hh, ddw, 10);
	strcat(cct, dd);
	dd = itoa(mm, ddw, 10);
	strcat(cct, dd);
	dd = itoa(se, ddw, 10);
	strcat(cct, dd);
	jetzt = atoi(cct);
	return cct;
}

void output(char *karten, char* name)
{
	FILE *inf;
	int erri = 1;
	
	char ccw [100];
	char ddw[100];
	
	char* dd;
	
	string fistr;
	//fistr = "outdaten.txt"
	
	if ((inf = _fsopen(name, "a", _SH_DENYWR)) != NULL)
	{
		fprintf(inf, karten);
		fclose(inf);
	}

	erri = 2;


}
void	write_data(vector<Card>& arrw, stack<Card*>*	targetw, vector<field_stack>& feldw)
{
	stack<Card*> helpstack;
	int uu = 0;
	int nn = 0;
	int  coll;
	int  wall = 0;
	bool hidd;
	int  hidden;
	char  karte[20];
	char*  karten;
	char cc [100] ="";
	char* ccst ;
	int cci;
	char* leer;
	int len;
	char ausgabedatennam[100]="outdaten.txt";
	//char namen[200];
	ccst = zeit();
	//ccst = itoa(cci, cc, 10);
	strcat(ccst, ausgabedatennam);
	strcat(cc,ccst);
	

	for (nn = 0; nn < 4; nn++)
	{
		uu = targetw[nn].size();
		switch (nn)
		{
		case(0) :
			karten = "Spades:";
			break;
		case(1) :
			karten = "Hearts:";
			break;
		case(2) :
			karten = "Diamonds:";
			break;
		case(3) :
			karten = "Clubs:";
			break;
		default:
			break;
		}
		output(karten, cc);
		for (int zz = 0; zz < uu; zz++)
		{
			// get the top card of the actual stack 
			helpstack.push(targetw[nn].top());
			// clear the top card of the stack 
			targetw[nn].pop();

		}
		for (int zz = 0; zz < uu; zz++)
		{

			
			targetw[nn].push(helpstack.top());
			helpstack.pop();
			coll = targetw[nn].top()->get_card_colour();
			wall = targetw[nn].top()->get_card_value();
			hidd = targetw[nn].top()->is_card_hidden();
			if (hidd == true)
			{
				hidden = 1;
			}
			else
			{
				hidden = 0;
			}
			karten = itoa((coll * 1000 + wall * 10 + hidden), karte, 10);
			len = strlen(karten);
			while ( len< 4)
			{
				leer = "0";
				output(leer, cc);
				len++;
			} 
			output(karten,cc);

			//printf("%s\n", karten);
			if ((zz + 1) < uu)
			{
			karten = ",";
			output(karten,  cc);
			}
			
		}
		karten = ";\n";
		output(karten, cc);
	}
	
}


void	delete_data(vector<Card>& arr, stack<Card*>*	target, vector<field_stack>& feld)
{

}
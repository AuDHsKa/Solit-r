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

#include "Eingabe_Ausgabe.h"

/*
//David Kommentar
*/
const	size_t	length = 52;
vector<Card>	arr(length);

void	read_data(vector<field_stack>& feld)
{
	FILE *inf;
	char fistr[100] = "";
	printf("Enter filename:\n");
	gets_s(fistr);
	
	if (strlen(fistr) == 0) strcpy(fistr, "in1.txt");
	inf = fopen(fistr, "r");
	if (inf == NULL) {
		printf("Cannot open input file %s\n", fistr);
	}
	else
	{
		CParser obj;
		//obj.uebergabe(arr);
		obj.InitParse(inf, stderr, stdout);
		//	obj.pr_tokentable();
		obj.yyparse(arr, feld);
		//char c; cin >> c;
	}

	fclose(inf);
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

	char ccw[100];
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

void	write_data(vector<field_stack>& feldw)
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
	char cc[100] = "";
	char* ccst;
	int cci;
	char* leer;
	int len;
	char ausgabedatennam[100] = "outdaten.txt";
	//char namen[200];
	ccst = zeit();
	//ccst = itoa(cci, cc, 10);
	strcat(ccst, ausgabedatennam);
	strcat(cc, ccst);


	for (nn = 0; nn < 12; nn++)
	{
		uu = feldw[nn].field.size();
		switch (nn)
		{
		case(0):
			karten = "Spades:";
			break;
		case(1):
			karten = "Hearts:";
			break;
		case(2):
			karten = "Diamonds:";
			break;
		case(3):
			karten = "Clubs:";
			break;
		case(4):
			karten = "StackA:";
			break;
		case(5):
			karten = "StackB:";
			break;
		case(6):
			karten = "StackC:";
			break;
		case(7):
			karten = "StackD:";
			break;
		case(8):
			karten = "StackE:";
			break;
		case(9):
			karten = "StackF:";
			break;
		case(10):
			karten = "StackG:";
			break;
		case(11):
			karten = "StackDECK:";
			break;
		default:
			break;
		}

		output(karten, cc);
		for (int zz = 0; zz < uu; zz++)
		{




			coll = feldw[nn].field[zz]->get_card_colour();
			wall = feldw[nn].field[zz]->get_card_value();
			hidd = feldw[nn].field[zz]->is_card_hidden();
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
			while (len< 4)
			{
				leer = "0";
				output(leer, cc);
				len++;
			}
			output(karten, cc);

			//printf("%s\n", karten);
			if ((zz + 1) < uu)
			{
				karten = ",";
				output(karten, cc);
			}

		}
		karten = ";\n";
		output(karten, cc);
	}

}


void	delete_data(vector<field_stack>& felde)
{
	int sz = 0;
	for (int del = 0; del < 12; del++)
	{
		sz = (felde[del].field.size());

		while (sz > 0)
		{
			felde[del].field.pop_back();
			sz = (felde[del].field.size());
		}
	}
	;
}

void get_arr(vector<Card>& arrl)
{
	arr = arrl;
}

void	write_log_data(int kartennummer, int start, int ziel)
{
	int colo;
	int vaul;
	int feldw;
	int reihew;
	int stzi;
	char cfeldw[5];
	char* cfelwst;
	char* name;
	char logname[100] = "logfile.txt";
	char* printout;
	colo = arr[kartennummer].get_card_colour();
	vaul = arr[kartennummer].get_card_value();
	switch (colo)
	{
	case(0):
		printout = "Pik ";
		break;
	case(1):
		printout = "Herz ";
		break;
	case(2):
		printout = "Karo ";
		break;
	case(3):
		printout = "Kreuz ";
		break;
	default:
		printout = "kiene Farbe";
		break;

	}
	output(printout, logname);
	switch (vaul)
	{
	case(0):
		printout = "0 ";
		break;
	case(1):
		printout = "ASS ";
		break;
	case(2):
		printout = "2 ";
		break;
	case(3):
		printout = "3 ";
		break;
	case(4):
		printout = "4 ";
		break;
	case(5):
		printout = "5 ";
		break;
	case(6):
		printout = "6 ";
		break;
	case(7):
		printout = "7 ";
		break;
	case(8):
		printout = "8 ";
		break;
	case(9):
		printout = "9 ";
		break;
	case(10):
		printout = "10 ";
		break;
	case(11):
		printout = "Bube ";
		break;
	case(12):
		printout = "Dame ";
		break;
	case(13):
		printout = "König ";
		break;
	default:
		printout = "kienen Wert";
		break;

	}
	output(printout, logname);

	for (int gg = 0; gg < 2; gg++)
	{
		if (gg == 0)
		{
			stzi = start;
		}
		else
		{
			printout = " -> ";
			output(printout, logname);
			stzi = ziel;
		}
		feldw = stzi / 100;
		reihew = stzi - feldw * 100;

		if (feldw < 4)
		{
			cfelwst = itoa(feldw, cfeldw, 10);
			name = "Zeilstapel";

		}
		else
		{
			cfelwst = itoa(feldw - 4, cfeldw, 10);
			name = "Feldstapel";

		}

		printout = name;
		output(printout, logname);
		printout = cfelwst;
		output(printout, logname);
		printout = " Reihe";
		output(printout, logname);
		printout = itoa(reihew, cfeldw, 10);
		output(printout, logname);
	}
	printout = "\n";
	output(printout, logname);
}
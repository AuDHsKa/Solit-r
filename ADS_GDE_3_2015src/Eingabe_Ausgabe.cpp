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
vector<Card> arr(length);

void get_arr(vector<Card>& arrl)
{
	arr = arrl;
}

void	read_data(vector<field_stack>& feld)
/*	Von k7scan2 übernommenes "Main" zum Aufruf der einzulesenden Datei
	und zur Ausfürhrung von k7scan2
*/
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
		obj.InitParse(inf, stderr, stdout);
		//	obj.pr_tokentable();
		obj.yyparse(arr, feld);
		
	}

	fclose(inf);
}

char*	zeit()
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

void	output(char *Ausgabetext, char* dateiname)
/*  Schreiben in die Ausgabedatei, dabei wird der Übergeben 
	Text an die auf zu rufenden Datei angefügt bzw. wenn noch 
	keine Datei vorhanden ist wird sie Erzeugt.
*/
{
	FILE *Ausgabedatei;
	
	if ((Ausgabedatei = _fsopen(dateiname, "a", _SH_DENYWR)) != NULL)// "a" Die  Daten werden an die Datei hinten angefügt
	{
		fprintf(Ausgabedatei, Ausgabetext);
		fclose(Ausgabedatei);
	}
	else
	{
		cout << "Datei konnte nicht geöfnet werden"; 
	}
		
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



void	write_log_data(vector<field_stack>& feldl, window& wind)
{
	/* Erzeugt den Ausgabe String des Logfiles 
	** in printout wird mit Text der String zusammen gebaut
	*/
	int colo;
	int vaul;
	int feldw;
	int reihew;
	int stzi;
	char cfeldw[5];
	//char* cfelwst;
	string Text;
	char logname[100] = "logfile.txt";
	string printout;
	char* printarr;
	colo = feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_colour();
	vaul = feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_value();
	printout = "Karte: ";
	switch (feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_colour()) // Farbe der Karte
	{
	case(1):
		Text = "Pik ";
		break;
	case(2):
		Text = "Herz ";
		break;
	case(0):
		Text = "Karo ";
		break;
	case(3):
		Text = "Kreuz ";
		break;
	default:
		Text = "keine Farbe";
		break;

	}
	printout = printout + Text;
	
	switch (feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_value()) //Wert der Karte
	{
	case(0):
		Text = "0 ";
		break;
	case(1):
		Text = "ASS ";
		break;
	case(2):
		Text = "2 ";
		break;
	case(3):
		Text = "3 ";
		break;
	case(4):
		Text = "4 ";
		break;
	case(5):
		Text = "5 ";
		break;
	case(6):
		Text = "6 ";
		break;
	case(7):
		Text = "7 ";
		break;
	case(8):
		Text = "8 ";
		break;
	case(9):
		Text = "9 ";
		break;
	case(10):
		Text = "10 ";
		break;
	case(11):
		Text = "Bube ";
		break;
	case(12):
		Text = "Dame ";
		break;
	case(13):
		Text = "König ";
		break;
	default:
		Text = "keinen Wert ";
		break;

	}
	
	printout = printout+ Text;
	if ((strlen(const_cast<char*>(printout.c_str())))<16) //Nur zur Schönheit des Logfiles kann man auch weglassen 
	{
		Text = "\t"; // 
		printout = printout + Text;
	}
	Text = "\tVon: Startstapel ";
	printout = printout + Text;
	Text = itoa(wind.first_click_stack, cfeldw, 10); //Stapel
	printout = printout + Text;
	Text = "\t Startreihe ";
	printout = printout + Text;
	Text = itoa(wind.first_click_card, cfeldw, 10); // Reihe
	printout = printout + Text;
	Text = "\t -> Nach: ";
	printout = printout + Text;
	Text = " Zielstapel ";
	printout = printout + Text;
	Text = itoa(wind.second_click_stack, cfeldw, 10); // Stapel
	printout = printout + Text;
	Text = "\t Zielreihe ";
	printout = printout + Text;
	Text = itoa((wind.second_click_card+1), cfeldw, 10);// +1 weil die Karte oben drauf gelegt wird also Reihe +1
	printout = printout + Text;
	Text = "\n"; // Neue Zeile
	printout = printout + Text;
	output(const_cast<char*>(printout.c_str()), logname);
}
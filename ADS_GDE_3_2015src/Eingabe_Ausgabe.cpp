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


void	read_data(vector<field_stack>& feld, vector<Card>& arrl)
/*	Von k7scan2 übernommenes "Main" zum Aufruf der einzulesenden Datei
und zur Ausfürhrung von k7scan2
*/
{
	FILE *inf;
	char fistr[100] = "";
	printf("Enter filename:\n");
	cin>>fistr;

	if (strlen(fistr) == 0) 
	{
		strcpy_s(fistr, "daten.txt");
	}
	if (fopen_s(&inf,fistr, "r") != NULL) // Achtung neue Fopen gibt Null zurück wenn die Datei geöffnet wurde 
	{
		printf("Cannot open input file %s\n", fistr);
	}
	else
	{
		output(fistr, "logfile.txt");
		output("\n", "logfile.txt");
		CParser obj;
		obj.InitParse(inf, stderr, stdout);
		//	obj.pr_tokentable();
		obj.yyparse(arrl, feld);

	}

	fclose(inf);
}

char*	zeit()
{
	char ccw[100];
	char ddw[100];
	char cct;
	char dd;
	struct tm uhr;
	time_t sekunden = time(NULL);
	localtime_s( &uhr ,&sekunden);
	cct = _itoa_s((uhr.tm_year + 1900), ccw, 10);
	dd = _itoa_s((uhr.tm_mon + 1), ddw, 10);
	strcat(ccw, ddw);
	dd = _itoa_s(uhr.tm_mday, ddw, 10);
	strcat(ccw, ddw);
	dd = _itoa_s(uhr.tm_hour, ddw, 10);
	strcat(ccw, ddw);
	dd = _itoa_s(uhr.tm_min, ddw, 10);
	strcat(ccw, ddw);
	dd = _itoa_s(uhr.tm_sec, ddw, 10);
	strcat(ccw, ddw);
	
	return ccw;
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
		cout << "\nDatei konnte nicht geöfnet werden\n";
	}

}

void	write_data(vector<field_stack>& feldw)
{
	//stack<Card*> helpstack;
	int Felstapelgroesse = 0;
	int Feldstapelnummer = 0;
	int  coll;
	int  wall = 0;
	bool hidd;
	int  hidden;
	char  karte[20];
	char*  karten;
	char Datanamen[100] = "";
	char* Datazeitstempel;

	char* leer;
	int len;
	char ausgabedatennam[100] = "outdaten.txt";// Grundnamen der Ausgabedatei
	
	Datazeitstempel = zeit();// Suchen der Aktuellenzeit und Rückgabe zur Dateinamen Erstellung
	
	strcat(Datazeitstempel, ausgabedatennam);
	strcat(Datanamen, Datazeitstempel);


	for (Feldstapelnummer = 0; Feldstapelnummer < 12; Feldstapelnummer++)
	{
		Felstapelgroesse = feldw[Feldstapelnummer].field.size();
		//Namen der Stapel in der Datei
		switch (Feldstapelnummer)
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
		case(4) :
			karten = "StackA:";
			break;
		case(5) :
			karten = "StackB:";
			break;
		case(6) :
			karten = "StackC:";
			break;
		case(7) :
			karten = "StackD:";
			break;
		case(8) :
			karten = "StackE:";
			break;
		case(9) :
			karten = "StackF:";
			break;
		case(10) :
			karten = "StackG:";
			break;
		case(11) :
			karten = "StackDECK:";
			break;
		default:
			break;
		}

		output(karten, Datanamen);
		for (int zz = 0; zz < Felstapelgroesse; zz++)
		{




			coll = feldw[Feldstapelnummer].field[zz]->get_card_colour();
			wall = feldw[Feldstapelnummer].field[zz]->get_card_value();
			hidd = feldw[Feldstapelnummer].field[zz]->is_card_hidden();
			if (hidd == true)
			{
				hidden = 1;
			}
			else
			{
				hidden = 0;
			}
			karten = _itoa((coll * 1000 + wall * 10 + hidden), karte, 10);
			len = strlen(karten);
			while (len< 4)
			{
				leer = "0";
				output(leer, Datanamen);
				len++;
			}
			output(karten, Datanamen);

			if ((zz + 1) < Felstapelgroesse)
			{
				karten = ",";//Ternung der Karten durch Komma in der Datei
				output(karten, Datanamen);
			}

		}
		karten = ";\n"; //Zeilen ende in der Datei
		output(karten, Datanamen);
	}

}


void	delete_data(vector<field_stack>& felde)
{
	int sz = 0;
	for (int del = 0; del < 12; del++)
	{
		sz = (felde.at(del).field.size());

		while (sz > 0)
		{
			felde.at(del).field.pop_back();
			sz = (felde.at(del).field.size());
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
	//int feldw;
	//int reihew;
	//int stzi;
	char cfeldw[5]; // Variabel zur Umwandlung von einem Interger in einen Char benötigt
	//char* cfelwst;
	string Text; // Zwischenspeicher um den Text an printout dran zu hängen
	char logname[100] = "logfile.txt";
	string printout; // Hier wird der kommpelte Text zur Ausgabe gesammelt
	//char* printarr;
	colo = feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_colour();
	vaul = feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_value();
	printout = "Karte: ";
	// Text aus gabe der Kartenfarbe
	switch (feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_colour()) // Farbe der Karte
	{
	case(1) :
		Text = "Pik ";
		break;
	case(2) :
		Text = "Herz ";
		break;
	case(0) :
		Text = "Karo ";
		break;
	case(3) :
		Text = "Kreuz ";
		break;
	default:
		Text = "keine Farbe";
		break;

	}
	printout = printout + Text;
	// Umwandlung des Wertes in Text z. B. eine 1 wird zu "ASS " dient rein zur Bessern Lesbarkeit in der Datei
	switch (feldl[wind.first_click_stack].field[wind.first_click_card]->get_card_value()) //Wert der Karte
	{
	case(0) :
		Text = "0 ";
		break;
	case(1) :
		Text = "ASS ";
		break;
	case(2) :
		Text = "2 ";
		break;
	case(3) :
		Text = "3 ";
		break;
	case(4) :
		Text = "4 ";
		break;
	case(5) :
		Text = "5 ";
		break;
	case(6) :
		Text = "6 ";
		break;
	case(7) :
		Text = "7 ";
		break;
	case(8) :
		Text = "8 ";
		break;
	case(9) :
		Text = "9 ";
		break;
	case(10) :
		Text = "10 ";
		break;
	case(11) :
		Text = "Bube ";
		break;
	case(12) :
		Text = "Dame ";
		break;
	case(13) :
		Text = "König ";
		break;
	default:
		Text = "keinen Wert ";
		break;

	}

	printout = printout + Text;
	if ((strlen(const_cast<char*>(printout.c_str())))<16) //Nur zur Schönheit des Logfiles kann man auch weglassen 
	{
		Text = "\t"; // 
		printout = printout + Text;
	}
	Text = "\tVon: Startstapel ";
	printout = printout + Text;
	Text = _itoa(wind.first_click_stack, cfeldw, 10); //Stapel
	printout = printout + Text;
	Text = "\t Startreihe ";
	printout = printout + Text;
	if (wind.first_click_card < 53) //Wenn noch keine Karte auf dem Stapel liegt
	{
		Text = _itoa(wind.first_click_card, cfeldw, 10); // Reihe
	}
	else
	{
		Text = "0"; // Da wenn derr Stapel lehr ist 53 als Wert übergeben wird
	}
	printout = printout + Text;
	Text = "\t -> Nach: ";
	printout = printout + Text;
	Text = " Zielstapel  ";
	printout = printout + Text;
	Text = _itoa(wind.second_click_stack, cfeldw, 10); // Stapel
	printout = printout + Text;
	Text = "\t Zielreihe ";
	printout = printout + Text;
	if ((wind.second_click_card + 1) < 53) //Wenn noch keine Karte auf dem Stapel liegt
	{
		Text = _itoa((wind.second_click_card + 1), cfeldw, 10);// +1 weil die Karte oben drauf gelegt wird also Reihe +1
	}
	else
	{
		Text = "0"; // Da wenn derr Stapel lehr ist 53 als Wert übergeben wird
	}

	printout = printout + Text;
	Text = "\n"; // Neue Zeile
	printout = printout + Text;
	output(const_cast<char*>(printout.c_str()), logname);// Ausgabe in die Datei
}
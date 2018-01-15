// k7scan1.cpp : Definiert den Einsprungpunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "k7scan2.h"
#include <stack>
#ifndef __Klassen__
#include "Klassen.h"

#endif // !__Klassen__
//#include "parser.h"


const int STRING1 = 3;
const int IDENTIFIER = 4;
const int INTEGER1 = 5;
const int REALNUMBER = 6;

const int TOKENSTART = 300;
const int CLUBS = 304;
const int SPADES = 305;
const int HEARDS = 306;
const int DIAMONDS = 307;
const int STACKA = 308;
const int STACKB = 309;
const int STACKC = 310;
const int STACKD = 311;
const int STACKE = 312;
const int STACKF = 313;
const int STACKG = 314;

const int STACKDECK = 315;

const int lengt = 52;


#pragma warning(disable:4786)
#include <iostream>
#include <string>
#include <map>

using namespace std;
#define	Getc(s)			getc(s)
#define	Ungetc(c)		{ungetc(c,IP_Input); ugetflag=1;}
/***********************************************************************************************
Funktion:				k7scan2
Bestimmung/Zweck:		Rahmenprogramm wurde aus der Vorlesung Algorithmen und  Datenstruckturen
						Übernommen. An Programmteilen an denen etwas geändert wurde ist 
						ein solcher Kommemtarkopf voran gestellt.

************************************************************************************************/

/***************************************************************************************
Funktion:				int CParser::Sucheadresse(int col, int val, vector<Card>& arr)
Bestimmung/Zweck:		Suchen der Kartenadresse im Array und rück gabe dessen
Eingangsparameter:		col(Farbe), val(Wert), Card Array
Ausgangsparameter:		Adresse der Karte im Array
****************************************************************************************/
int CParser::Sucheadresse(int col, int val, vector<Card>& arr)
{

	int Adersse;
	for (Adersse = 0; Adersse < 52; Adersse++)
	{
		
		if (arr[Adersse].get_card_colour() == col &&  arr[Adersse].get_card_value() == val)
		{
			//cout << Adersse << "\n";
			return Adersse; // adressrückgabe
		}
		
	}
	return 53; // Keine Kartenadresse gefungen
}

//------------------------------------------------------------------------
// Adds a character to the string value
void CParser::PushString(char c)
{
	yylval.s += c;
}
//------------------------------------------------------------------------
void CParser::Load_tokenentry(string str, int index)
{
	IP_Token_table[str] = index;
	IP_revToken_table[index] = str;
}
/***************************************************************************************
Funktion:				void CParser::IP_init_token_table()
Bestimmung/Zweck:		Die Tabelle wurde um die Stapel  zur Erkenung erweitert 

****************************************************************************************/
void CParser::IP_init_token_table()
{
	Load_tokenentry("STRING1", 3);
	Load_tokenentry("IDENTIFIER", 4);
	Load_tokenentry("INTEGER1", 5);
	Load_tokenentry("REALNUMBER", 6);

	int ii = TOKENSTART;
	Load_tokenentry("AND", ii++);
	Load_tokenentry("OR", ii++);
	Load_tokenentry("Begin", ii++);
	Load_tokenentry("End", ii++);
	Load_tokenentry("Clubs", ii++);
	Load_tokenentry("Spades", ii++);
	Load_tokenentry("Hearts", ii++);
	Load_tokenentry("Diamonds", ii++);
	Load_tokenentry("StackA", ii++);
	Load_tokenentry("StackB", ii++);
	Load_tokenentry("StackC", ii++);
	Load_tokenentry("StackD", ii++);
	Load_tokenentry("StackE", ii++);
	Load_tokenentry("StackF", ii++);
	Load_tokenentry("StackG", ii++);
	Load_tokenentry("StackDECK", ii++);

}
//------------------------------------------------------------------------

void CParser::pr_tokentable()
{

	typedef map<string, int>::const_iterator CI;
	const char* buf;

	printf("Symbol Table ---------------------------------------------\n");

	for (CI p = IP_Token_table.begin(); p != IP_Token_table.end(); ++p) {
		buf = p->first.c_str();
		printf(" key:%s", buf);
		printf(" val:%d\n", p->second);;
	}
}
//------------------------------------------------------------------------
/***************************************************************************************
Funktion:				int	CParser::yyparse(vector<Card>&	arr, vector<field_stack>& feld)
Bestimmung/Zweck:		Auswertung der eingelensen Werte und deren weiter Verarbeitung
Eingangsparameter:		Card, field_stack
Ausgangsparameter:		kein Rückgabewert
****************************************************************************************/
int	CParser::yyparse(vector<Card>&	arr, vector<field_stack>& feld)
{

	int tok;
	int wert = 1;
	int farb;
	int hidden;
	//int wo = 0; unten nur für den Else Zweig ist aber auskommentiert

	if (prflag)fprintf(IP_List, "%5d ", (int)IP_LineNumber);
	/*
	*	Go parse things!
	*/
	while ((tok = yylex()) != 0) {
		//printf("%d ", tok);
		switch (tok)
		{
		case(STRING1):

			printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			break;
		case(INTEGER1):
			// Erkennung der Karte und Auswertung
			//cout << stapel << "\n";
			farb = yylval.i;
			farb = farb / 1000; // Berechnung der Farbe
			wert = (yylval.i - farb * 1000) / 10; // Berechnung des Wertes
			hidden = yylval.i % 2; // wenn hidden = 1 dann ist die Karte Verdekt wenn hidden = 0 dann ist die karte offen
								   //cout << "Wir sind hierher gekommen!";
								   //field_stack. = 
			if (hidden == 1)
			{
				arr[CParser::Sucheadresse(farb, wert, arr)].hide_card();// Verdecken 
			}
			else
			{
				arr[CParser::Sucheadresse(farb, wert, arr)].undiscover_card(); // Aufdecken
			}
			//Übergabe
			feld[stapel].field.push_back(&arr[CParser::Sucheadresse(farb, wert, arr)]);// Erstellung der Karte

			
			break;
		case(REALNUMBER):
			printf("%s %g ", IP_revToken_table[tok].c_str(), yylval.d);
			break;
		case(IDENTIFIER):
			printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			break;
			//Stapel Übergabe und Speicherung
		case(CLUBS):// Kreuz
			stapel = 3;
			//cout << stapel << "\n";
			break;
		case(SPADES): //Pik
			stapel = 0;
			//cout << stapel << "\n";
			break;
		case(HEARDS): // Herz
			stapel = 1;
			//cout << stapel << "\n";
			break;
		case(DIAMONDS): //Karo
			stapel = 2;
			//cout << stapel << "\n";
			break;
		case(STACKA):
			stapel = 4;
			//cout << stapel << "\n";
			break;
		case(STACKB):
			stapel = 5;
			//cout << stapel << "\n";
			break;
		case(STACKC):
			stapel = 6;
			//cout << stapel << "\n";
			break;
		case(STACKD):
			stapel = 7;
			//cout << stapel << "\n";
			break;
		case(STACKE):
			stapel = 8;
			//cout << stapel << "\n";
			break;
		case(STACKF):
			stapel = 9;
			//cout << stapel << "\n";
			break;
		case(STACKG):
			stapel = 10;
			//cout << stapel << "\n";
			break;
		case(STACKDECK):
			stapel = 11;
			//cout << stapel << "\n";
			break;
		default:

			if (tok >= TOKENSTART)
			{
				printf("%s ", IP_revToken_table[tok].c_str());
			}
				
			//else
			//{
				//printf("%c ", tok);
			//	wo++; // Damit der Else Zweig ausgeführt wird 
			//}

			break;


		}

		//		if(!prflag)printf("\n");
	}
	return 0;

}
//------------------------------------------------------------------------

/*
*	Parse Initfile:
*
*	  This builds the context tree and then calls the real parser.
*	It is passed two file streams, the first is where the input comes
*	from; the second is where error messages get printed.
*/
void CParser::InitParse(FILE *inp, FILE *err, FILE *lst)

{

	/*
	*	Set up the file state to something useful.
	*/
	IP_Input = inp;
	IP_Error = err;
	IP_List = lst;

	IP_LineNumber = 1;
	ugetflag = 0;
	/*
	*	Define both the enabled token and keyword strings.
	*/
	IP_init_token_table();
}
//------------------------------------------------------------------------

/*
*	yyerror:
*
*	  Standard error reporter, it prints out the passed string
*	preceeded by the current filename and line number.
*/
void CParser::yyerror(char *ers)

{
	fprintf(IP_Error, "line %d: %s\n", IP_LineNumber, ers);
}
//------------------------------------------------------------------------

int CParser::IP_MatchToken(string &tok)
{
	int retval;
	if (IP_Token_table.find(tok) != IP_Token_table.end()) {
		retval = (IP_Token_table[tok]);
	}
	else {
		retval = (0);
	}
	return retval;
}
const int TT_EOF = 0;
const int TT_NUMBER = 1;
const int TT_WORD = 2;
//------------------------------------------------------------------------
int CParser::yylexret(int retv)			//sets ttype ,yylval, sval, nval
{
	switch (retv) {
	case EOF:
		ttype = TT_EOF;
		break;
	case REALNUMBER:
		nval = yylval.d;
		ttype = TT_NUMBER;
		break;
	case INTEGER1:
		nval = yylval.i;
		ttype = TT_NUMBER;
		break;
	case STRING1:
		sval = yylval.s;
		ttype = TT_WORD;
		break;
	case IDENTIFIER:
		sval = yylval.s;
		ttype = TT_WORD;

		break;
	default:
		;

	};
	return(retv);
}
//------------------------------------------------------------------------

/*
*	yylex:
*
*/
int CParser::yylex()
{
	//Locals
	int c;
	lexstate s;
	/*
	*	Keep on sucking up characters until we find something which
	*	explicitly forces us out of this function.
	*/
	for (s = L_START, yytext = ""; 1;) {
		c = Getc(IP_Input);
		yytext = yytext + (char)c;
		lineincr = 0;
		if (!ugetflag) {
			if (c != EOF)if (prflag)fprintf(IP_List, "%c", c);
		}
		else ugetflag = 0;
		switch (s) {
			//Starting state, look for something resembling a token.
		case L_START:
			if (isdigit(c)) {
				s = L_INT;
			}
			else if (isalpha(c) || c == '\\') {
				s = L_IDENT;
			}
			else if (isspace(c)) {
				if (c == '\n') {
					IP_LineNumber += 1;
					lineincr = 1;
					if (prflag)
						fprintf(IP_List, "%5d ", (int)IP_LineNumber);
				}
				yytext = "";
			}
			else if (c == '/') {
				yytext = "";
				s = L_COMMENT;
			}
			else if (c == '"') {
				s = L_STRING;
				yylval.s = "";
			}
			else if (c == EOF) {
				return yylexret('\0');
			}
			else {
				return yylexret(c);
			}
			break;

		case L_COMMENT:
			if (c == '/')
				s = L_LINE_COMMENT;
			else	if (c == '*')
				s = L_TEXT_COMMENT;
			else {
				Ungetc(c);
				return yylexret('/');	/* its the division operator not a comment */
			}
			break;
		case L_LINE_COMMENT:
			if (c == '\n') {
				s = L_START;
				Ungetc(c);
			}
			yytext = "";
			break;
		case L_TEXT_COMMENT:
			if (c == '\n') {
				IP_LineNumber += 1;
			}
			else if (c == '*')
				s = L_END_TEXT_COMMENT;
			yytext = "";
			break;
		case L_END_TEXT_COMMENT:
			if (c == '/') {
				s = L_START;
			}
			else {
				s = L_TEXT_COMMENT;
			}
			yytext = "";
			break;

			/*
			*	Suck up the integer digits.
			*/
		case L_INT:
			if (isdigit(c)) {
				break;
			}
			else {
				if (c == '.') {
					s = L_FLOAT;
				}
				else {
					if (c == 'E' || c == 'e') {
						s = L_EXP;
					}
					else {
						Ungetc(c);
						yylval.s = yytext.substr(0, yytext.size() - 1);
						yylval.i = atoi(yylval.s.c_str());
						return yylexret(INTEGER1);
					}
				}
			}
			break;
		case L_FLOAT:
			if (isdigit(c)) {
				break;
			}
			else {
				if (c == 'E' || c == 'e') {
					s = L_EXP;
					break;
				}
				else {
					Ungetc(c);
					yylval.s = yytext.substr(0, yytext.size() - 1);
					yylval.d = atof(yylval.s.c_str());
					return yylexret(REALNUMBER);
				}
			}
			break;
		case L_EXP:
			if (isdigit(c)) {
				break;
			}
			else {
				if (c == '-' || c == '+') {
					break;
				}
				else {
					Ungetc(c);
					yylval.s = yytext.substr(0, yytext.size() - 1);
					yylval.d = atof(yylval.s.c_str());
					return yylexret(REALNUMBER);
				}
			}
			break;
		case L_REAL:
			if (isdigit(c)) {
				break;
			}
			else {
				Ungetc(c);
				yylval.s = yytext.substr(0, yytext.size() - 1);
				yylval.d = atof(yylval.s.c_str());
				return yylexret(REALNUMBER);
			}

			/*
			*	Grab an identifier, see if the current context enables
			*	it with a specific token value.
			*/

		case L_IDENT:
			if (isalpha(c) || isdigit(c) || c == '_')
				break;
			Ungetc(c);
			yytext = yytext.substr(0, yytext.size() - 1);
			yylval.s = yytext;
			if (c = IP_MatchToken(yytext)) {
				return yylexret(c);
			}
			else {
				return yylexret(IDENTIFIER);
			}

			/*
			*	Suck up string characters but once resolved they should
			*	be deposited in the string bucket because they can be
			*	arbitrarily long.
			*/
		case L_STRING2:
			s = L_STRING;
			if (c == '"') {// >\"< found
				PushString((char)c);
			}
			else {
				if (c == '\\') {// >\\< found
					PushString((char)c);
				}
				else {
					PushString((char)'\\');// >\x< found
					PushString((char)c);
				}
			}
			break;
		case L_STRING:
			if (c == '\n')
				IP_LineNumber += 1;
			else if (c == '\r')
				;
			else	if (c == '"' || c == EOF) {
				return (STRING1);
			}
			else	if (c == '\\') {
				s = L_STRING2;
				//PushString((char)c);
			}
			else
				PushString((char)c);
			break;
		default: printf("***Fatal Error*** Wrong case label in yylex\n");
		}
	}
}
//------------------------------------------------------------------------
/*
int main(int argc, char* argv[])
{

FILE *inf;
char fistr[100] = "";
printf("Enter filename:\n");
gets(fistr);
if(strlen(fistr)==0) strcpy (fistr,"in1.txt");
inf = fopen(fistr,"r");
if(inf==NULL){
printf("Cannot open input file %s\n",fistr);
return 0;
}
CParser obj;
obj.InitParse(inf,stderr,stdout);
//	obj.pr_tokentable();
obj.yyparse();
char c; cin>>c;


return 0;
}

*/

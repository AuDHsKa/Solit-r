// k7scan1.cpp : Definiert den Einsprungpunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "k7scan2.h"
#include <stack>
#ifndef __Klassen__
#include "Klassen.h"

#endif // !__Klassen__
//#include "parser.h"


const int STRING1=3;
const int IDENTIFIER=4;
const int INTEGER1=5;
const int REALNUMBER=6;

const int TOKENSTART=300;
const int CLUBS=304;
const int SPADES=305;
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
/*
class CParser
{
public:
	/*
	 *	Lexical analyzer states.
	 
	enum lexstate{L_START,L_INT,L_REAL,L_EXP,L_FLOAT,L_IDENT,L_STRING,L_STRING2,
		L_COMMENT,L_TEXT_COMMENT,L_LINE_COMMENT,L_END_TEXT_COMMENT};


	string yytext;								//input buffer
	struct tyylval{								//value return
		string s;								//structure
		int i;
		double d;
	}yylval;
	int ttype;									//returnvalues according to the java tokenizer
	string sval;								// word token
	double nval;								// number token
	int lineincr;								// to create TT_EOL
	FILE *IP_Input;								//Input File
	FILE *IP_Error;								//Error Output
	FILE *IP_List;								//List Output
	int  IP_LineNumber;							//Line counter
	int ugetflag;								//checks ungets
	int prflag;									//controls printing
	map<string,int> IP_Token_table;				//Tokendefinitions
	map<int,string> IP_revToken_table;			//reverse Tokendefinitions


	int CParser::yylex();						//lexial analyser
	int CParser::yylexret(int retv);			//sets ttype ,yylval, sval, nval
	void CParser::yyerror(char *ers);			//error reporter
	int CParser::IP_MatchToken(string &tok);	//checks the token
	void CParser::InitParse(FILE *inp,FILE *err,FILE *lst);
	int	CParser::yyparse();						//parser
	void CParser::pr_tokentable();				//test output for tokens
	void CParser::IP_init_token_table();		//loads the tokens
	void CParser::Load_tokenentry(string str,int index);//load one token
	void CParser::PushString(char c);			//Used for dtring assembly
	CParser(){IP_LineNumber = 1;ugetflag=0;prflag=0;};	//Constructor
};*/
//------------------------------------------------------------------------
//void CParser::uebergabe(vector<Card>& add)
//{
//	// Übergabe der Karten
//	CParser::add = add;
//	//cout << add <<"\n";
//	//show_cards(add, lengt);
//}

int CParser::Sucheadresse(int col, int val, vector<Card>& arr)
{

	int zz;
	for (zz = 0; zz < 52; zz++)
	{
		//cout << "Wir sind hierher gekommen!";
		if (arr[zz].get_card_colour() == col &&  arr[zz].get_card_value()==val)
		{
			//cout << zz << "\n";
			return zz; // adressrückgabe
		}
		//else return NULL;
	}
	//return nullptr;
}

//------------------------------------------------------------------------
// Adds a character to the string value
void CParser::PushString(char c)
{
	yylval.s += c;
}
//------------------------------------------------------------------------
void CParser::Load_tokenentry(string str,int index)
{
	IP_Token_table[str]=index;
	IP_revToken_table[index]=str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("STRING1",3);
	Load_tokenentry("IDENTIFIER",4);
	Load_tokenentry("INTEGER1",5);
	Load_tokenentry("REALNUMBER",6);

	int ii=TOKENSTART;
	Load_tokenentry("AND",ii++);
	Load_tokenentry("OR",ii++);
	Load_tokenentry("Begin",ii++);
	Load_tokenentry("End",ii++);
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
	
	typedef map<string,int>::const_iterator CI;
	const char* buf;

	printf( "Symbol Table ---------------------------------------------\n");

	for(CI p=IP_Token_table.begin(); p!=IP_Token_table.end(); ++p){
		buf = p->first.c_str();
		printf(" key:%s", buf);
		printf(" val:%d\n", p->second);;
	}
}
//------------------------------------------------------------------------

int	CParser::yyparse(vector<Card>&	arr, vector<field_stack>& feld, stack<Card*>* startfeld)
{

	int tok;
	int wert = 1;
	int farb;
	int hidden;
	int wo=0;

	if(prflag)fprintf(IP_List,"%5d ",(int)IP_LineNumber);
	/*
	*	Go parse things!
	*/
	while ((tok = yylex()) != 0){
		//printf("%d ", tok);
		switch (tok)
		{
		case(STRING1) :

			printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			break;
		case(INTEGER1) :
			//printf("%s %d ", IP_revToken_table[tok].c_str(), yylval.i);
			//cout << stapel << "\n";
			farb = yylval.i;
			farb = farb / 1000; // Berechnung der Farbe
			wert = (yylval.i - farb * 1000) / 10; // Berechnung des Wertes
			hidden = yylval.i % 2; // wenn hidden = 1 dann ist die Karte Verdekt wenn hidden = 0 dann ist die karte offen
			//cout << "Wir sind hierher gekommen!";
			//field_stack. = 
			if (hidden == 1)
			{
				arr[CParser::Sucheadresse(farb, wert, arr)].hide_card();
			}
			else
			{
				arr[CParser::Sucheadresse(farb, wert, arr)].undiscover_card();
			}
			if (stapel < 4)
			{
				startfeld[stapel].push(&arr[CParser::Sucheadresse(farb, wert, arr)]);
				
			}
			else
			{
				feld[stapel - 4].field.push_back(&arr[CParser::Sucheadresse(farb, wert, arr)]);
			}
			//Übergabe
			break;
		case(REALNUMBER) :
			printf("%s %g ", IP_revToken_table[tok].c_str(), yylval.d);
			break;
		case(IDENTIFIER) :
			printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			break;
		case(CLUBS) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 3;
			//cout << stapel << "\n";
			break;
		case(SPADES) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 0;
			//cout << stapel << "\n";
			break;
		case(HEARDS) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 1;
			//cout << stapel << "\n";
			break;
		case(DIAMONDS) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 2;
			//cout << stapel << "\n";
			break;
		case(STACKA) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 4;
			//cout << stapel << "\n";
			break;
		case(STACKB) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 5;
			//cout << stapel << "\n";
			break;
		case(STACKC) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 6;
			//cout << stapel << "\n";
			break;
		case(STACKD) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 7;
			//cout << stapel << "\n";
			break;
		case(STACKE) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 8;
			//cout << stapel << "\n";
			break;
		case(STACKF) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 9;
			//cout << stapel << "\n";
			break;
		case(STACKG) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 10;
			//cout << stapel << "\n";
			break;
		case(STACKDECK) :
			//printf("%s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			stapel = 11;
			//cout << stapel << "\n";
			break;
		default:

			if (tok >= TOKENSTART)
				printf("%s ", IP_revToken_table[tok].c_str());
			else
			{
				//printf("%c ", tok);
				wo++;
			}
				
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
void CParser::InitParse(FILE *inp,FILE *err,FILE *lst)

{

	/*
	*	Set up the file state to something useful.
	*/
	IP_Input = inp;
	IP_Error = err;
	IP_List  = lst;

	IP_LineNumber = 1;
	ugetflag=0;
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
  fprintf(IP_Error,"line %d: %s\n",IP_LineNumber,ers);
}
//------------------------------------------------------------------------

int CParser::IP_MatchToken(string &tok)
{
	int retval;
	if(	IP_Token_table.find(tok) != IP_Token_table.end()){
		retval = (IP_Token_table[tok]);
	}else{
		retval = (0);
	}
	return retval;
} 
const int TT_EOF=0;
const int TT_NUMBER=1;
const int TT_WORD=2;
//------------------------------------------------------------------------
int CParser::yylexret(int retv)			//sets ttype ,yylval, sval, nval
{
	switch (retv){
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
	for (s = L_START,yytext = ""; 1;){
		c = Getc(IP_Input);
		yytext = yytext + (char)c;
		lineincr = 0;
		if(!ugetflag) { 
			if(c != EOF)if(prflag)fprintf(IP_List,"%c",c);
		}else ugetflag = 0;
		switch (s){
		  //Starting state, look for something resembling a token.
			case L_START:
				if (isdigit(c)){
				  s = L_INT;
				}else if (isalpha(c) || c == '\\' ){
						s = L_IDENT;
				}else if (isspace(c)){
							if (c == '\n'){
								IP_LineNumber += 1;
								lineincr = 1;
								if(prflag)
									fprintf(IP_List,"%5d ",(int)IP_LineNumber);
							}
							yytext = "";
				}else if (c == '/'){
							yytext = "";
							s = L_COMMENT;
				}else if (c == '"'){
							s = L_STRING;
							yylval.s="";
				}else if (c == EOF){
							return yylexret ('\0');
				}else{						
							return yylexret (c);
				}
			break;

			case L_COMMENT:
				if (c == '/') 
					s = L_LINE_COMMENT;
				else	if(c == '*')
							s = L_TEXT_COMMENT;
						else{
								Ungetc(c);
								return yylexret('/');	/* its the division operator not a comment */
							}
			break;
			case L_LINE_COMMENT:
				if ( c == '\n'){
					s = L_START;
					Ungetc(c);
				}
				yytext = "";
			break;
			case L_TEXT_COMMENT:
				if ( c == '\n'){
					IP_LineNumber += 1;
				}else if (c == '*')
							s = L_END_TEXT_COMMENT;
				yytext = "";
			break;
			case L_END_TEXT_COMMENT:
				if (c == '/'){
					s = L_START;
				}else{
					s = L_TEXT_COMMENT;
				}
				yytext = "";
			break;

		  /*
		   *	Suck up the integer digits.
		   */
			case L_INT:
				if (isdigit(c)){
					break;
				}else{
					if (c == '.'){
						s = L_FLOAT;
					}else{	
						if (c == 'E'|| c == 'e'){
							s = L_EXP;
						}else {
							Ungetc(c);
							yylval.s = yytext.substr(0,yytext.size()-1);
							yylval.i = atoi(yylval.s.c_str());
							return yylexret(INTEGER1);
						}
					}
				}
			break;
			case L_FLOAT:
				if (isdigit(c)){
					break;
				}else{	
					if(c == 'E' || c == 'e'){
						s = L_EXP;
						break;
					}else{
						Ungetc(c);
						yylval.s = yytext.substr(0,yytext.size()-1);
						yylval.d = atof(yylval.s.c_str());
						return yylexret(REALNUMBER); 
					}
				} 
			break;
			case L_EXP:
				if (isdigit(c)){
					break;
				}else{	
					if( c== '-' || c== '+'){
						break;
					}else{
						Ungetc(c);
						yylval.s = yytext.substr(0,yytext.size()-1);
						yylval.d = atof(yylval.s.c_str());
						return yylexret(REALNUMBER); 
					}					
				}
			break;
			case L_REAL:
				if (isdigit(c)){
					break;
				}else{
					Ungetc(c);
					yylval.s = yytext.substr(0,yytext.size()-1);
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
				yytext = yytext.substr(0,yytext.size()-1);
				yylval.s = yytext;
				if (c = IP_MatchToken(yytext)){
					return yylexret(c);
				}else{
					return yylexret(IDENTIFIER);
				}

		   /*
		   *	Suck up string characters but once resolved they should
		   *	be deposited in the string bucket because they can be
		   *	arbitrarily long.
		   */
			case L_STRING2:
				s = L_STRING;
				if(c == '"'){// >\"< found
					PushString((char)c);
				}else{
					if(c == '\\'){// >\\< found
						PushString((char)c);
					}else{
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
					 else	if (c == '"' || c == EOF){
								return (STRING1);
							} else	if(c=='\\'){
										s = L_STRING2;
										//PushString((char)c);
									}else
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

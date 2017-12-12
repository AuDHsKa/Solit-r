#include "stdAfx.h"
#include <iostream>
#include <string>
#include <map>
#include <stack>

#ifndef __Klassen__
#include "Klassen.h"
#endif // !__Klassen__

#define		__k7scan2__

using namespace std;
class CParser
{
public:
	/*
	*	Lexical analyzer states.
	*/
	enum lexstate {
		L_START, L_INT, L_REAL, L_EXP, L_FLOAT, L_IDENT, L_STRING, L_STRING2,
		L_COMMENT, L_TEXT_COMMENT, L_LINE_COMMENT, L_END_TEXT_COMMENT
	};


	string yytext;								//input buffer
	struct tyylval {								//value return
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
	map<string, int> IP_Token_table;				//Tokendefinitions
	map<int, string> IP_revToken_table;			//reverse Tokendefinitions
												//vector<Card>& add;
	int stapel;


	int CParser::yylex();						//lexial analyser
	int CParser::yylexret(int retv);			//sets ttype ,yylval, sval, nval
	void CParser::yyerror(char *ers);			//error reporter
	int CParser::IP_MatchToken(string &tok);	//checks the token
	void CParser::InitParse(FILE *inp, FILE *err, FILE *lst);
	int	CParser::yyparse(vector<Card>& arr, vector<field_stack>& feld);						//parser
	void CParser::pr_tokentable();				//test output for tokens
	void CParser::IP_init_token_table();		//loads the tokens
	void CParser::Load_tokenentry(string str, int index);//load one token
	void CParser::PushString(char c);			//Used for dtring assembly

	int CParser::Sucheadresse(int col, int val, vector<Card>& arr); //Adressensucher
	CParser() { IP_LineNumber = 1; ugetflag = 0; prflag = 0; };	//Constructor
};
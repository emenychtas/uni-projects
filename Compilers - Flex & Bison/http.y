%{
#include <cstdio>
#include <iostream>
using namespace std;

#include <string.h>
#include "http.tab.h"
extern "C" int yylex(void);
extern "C++" int yyparse(void);
extern "C" FILE *yyin;
extern "C" char *yytext;
extern int line_number, body_length, content_length, content_header_check;
extern char *method_check, *request_line;
int req_error = 0, empty_lines = 0, unhandled_error = 1, i;
void yyerror(const char *s);

%}

%token ENDL
%token REQUESTLINE
%token CONNECTION DATE TRANSFERENCODING
%token ACCEPTCHARSET REFERER USERAGENT
%token CONTENTLENGTH EXPIRES
%token BODYSTRING
%token END_OF_FILE

%%

Request: Request_Line ENDL Headers Footer { cout << "FILE CHECK COMPLETE!\n"; };

Request_Line: REQUESTLINE | BODYSTRING { yyerror("Bad Request line."); yyerrok; yyclearin; body_length = 0; req_error = 1; };

Headers: Headers Header ENDL | Header ENDL;
Header: ENDLS General_Header { yyerror("Empty line."); cout << "General Header found.\n"; yyerrok; yyclearin; } | ENDLS Request_Header { yyerror("Empty line."); cout << "Request Header found.\n"; yyerrok; yyclearin; } | ENDLS Entity_Header { yyerror("Empty line."); cout << "Entity Header found.\n"; yyerrok; yyclearin; } | General_Header { cout << "General Header found.\n"; } | Request_Header { cout << "Request Header found.\n"; } | Entity_Header { cout << "Entity Header found.\n"; } | ENDLS error { yyerror("Empty line."); yyerror("Bad Header."); yyerrok; yyclearin; body_length = 0; } | error { yyerror("Bad Header."); yyerrok; yyclearin; body_length = 0;};

General_Header: CONNECTION | DATE | TRANSFERENCODING;

Request_Header: ACCEPTCHARSET | REFERER | USERAGENT;

Entity_Header: CONTENTLENGTH | EXPIRES;

Footer: END_OF_FILE { if ( strcmp(method_check, "POST") == 0 ) { yyerror("No body found."); if (content_header_check == 0) { yyerror("No Content Header found."); yyerrok; yyclearin; } else { if (body_length == content_length) cout << "Content length given matches.\n"; else { yyerror("Bad content length."); yyerrok; yyclearin; } } } else cout << "No message body found.\n"; unhandled_error = 0; } | ENDL Message_Body | ENDLS END_OF_FILE { if ( strcmp(method_check, "POST") == 0 ) { yyerror("No body found."); if (content_header_check == 0) { yyerror("No Content Header found."); yyerrok; yyclearin; } else { if (body_length == content_length) cout << "Content length given matches.\n"; else { yyerror("Bad content length."); yyerrok; yyclearin; } } } else cout << "No message body found.\n"; unhandled_error = 0; };

Message_Body: Message_Body BODYSTRING ENDLS END_OF_FILE { if ( strcmp(method_check, "POST") == 0 ) { cout << "Found message body while method was POST.\n"; if (content_header_check == 0) { yyerror("No Content Header found."); yyerrok; yyclearin; } else { if (body_length == content_length) cout << "Content length given matches.\n"; else { yyerror("Bad content length."); yyerrok; yyclearin; } } } else cout << "Found message body.\n"; unhandled_error = 0; } | BODYSTRING  ENDLS END_OF_FILE { if ( strcmp(method_check, "POST") == 0 ) { cout << "Found message body while method was POST.\n"; if (content_header_check == 0) { yyerror("No Content Header found."); yyerrok; yyclearin; } else { if (body_length == content_length) cout << "Content length given matches.\n"; else { yyerror("Bad content length."); yyerrok; yyclearin; } } } else cout << "Found message body.\n"; unhandled_error = 0; } | Message_Body BODYSTRING ENDLS | BODYSTRING ENDLS;

ENDLS: ENDLS ENDL { ++empty_lines; } | ENDL { ++empty_lines; };

%%

int user_input;
FILE *myfile;

main()
{	
	cout << endl << endl << "Welcome! For your convenience, 11 different input files were made" << endl << "to test the protocol's functionality." << endl << "Below you will find each of the input file's number with" << endl << 
"their corresponding test:" << endl << endl << "Enter 1 for a functioning GET request file." << endl <<  "Enter 2 for a functioning POST request file." << endl << "Enter 3 for a file with a bad request line." << endl << "Enter 4 for a GET request file with empty lines." << endl << "Enter 5 for a GET request file with bad headers." << endl << "Enter 6 for a GET request file with mixed errors." << endl <<  "Enter 7 for a POST request file with bad content length." << endl <<  "Enter 8 for a POST request file with no content header." << endl <<  "Enter 9 for a POST request file with no message body." << endl << "Enter 10 for a POST request file with mixed errors." << endl <<  "Enter 11 for a request file with an unhandled error." << endl << endl << "User input:" <<endl;

	cin >> user_input;

	switch (user_input)
	{
		case 1:
		myfile = fopen("get", "r");
		break;
		case 2:
		myfile = fopen("post", "r");
		break;
		case 3:
		myfile = fopen("badreq", "r");
		break;
		case 4:
		myfile = fopen("get1", "r");
		break;
		case 5:
		myfile = fopen("get2", "r");
		break;
		case 6:
		myfile = fopen("get3", "r");
		break;
		case 7:
		myfile = fopen("post1", "r");
		break;
		case 8:
		myfile = fopen("post2", "r");
		break;
		case 9:
		myfile = fopen("post3", "r");
		break;
		case 10:
		myfile = fopen("post4", "r");
		break;
		case 11:
		myfile = fopen("un_err", "r");
		break;
		default:
		cout << "No valid choice entered." << endl;
		break;
	}
	
	if (!myfile)
	{
		cout << "File not found!\n";
		return -1;
	}

	yyin = myfile;

	do
	{
		yyparse();
		if (unhandled_error == 1)
		cout << " ~ UNHANDLED ERROR: Header(s) were found after body data. Terminating." << endl;
		else
		{
		if (req_error == 0)
		cout << " ~ Extra notes:" << endl << " - Request line: " << request_line << endl << " - Message body content length: " << body_length << endl;
		else
		cout << " ~ Extra notes:" << endl << " - Message body content length: " << body_length << endl;
		}
	} while (!feof(yyin));
}

void yyerror(const char *s)
{
	if (s == "Empty line.")
	{
	for (i = empty_lines; i > 0; i--) 
	cout << " ~ Parse Error (Line Number: " << (line_number - i) + 1 << "): " << s << endl;
	empty_lines = 0;
	}
        else if (s == "Bad Request line.")
	{
	cout << " ~ Parse Error: " << s << endl;
	cout << " ~ Parse Error Token: " << yytext << endl;
	}
	else if (s == "Bad Header.")
	{
	cout << " ~ Parse Error (Line Number: " << line_number + 1 << "): " << s << endl;
	cout << " ~ Parse Error Token: " << yytext << endl;
	}
	else if (s == "No Content Header found.")
	{
	cout << s << endl << " ~ ERROR during POST method. No content header found. " << endl;
	}
	else if (s == "Bad content length.")
	{
	cout << s << endl << " ~ ERROR during POST method. Content length given (" << content_length << ") does not match actual body length. " << endl;
        }
        else if (s == "No body found.")
	{
	cout << s << endl << " ~ ERROR during POST method. No message body found. " << endl;   }
}


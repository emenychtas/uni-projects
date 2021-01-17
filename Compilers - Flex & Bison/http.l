%{
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "http.tab.h"
using namespace std;
#define YY_DECL extern "C" int yylex(void)
int line_number = 0;
int body_length = 0;
int content_length = 0;
int content_header_check = 0;
char *request_line, *method_check = (char*) malloc(4), *con_length = (char*) malloc(64);
%}

%%

(GET|HEAD|POST)" ".+" "HTTP\/1\.(1|0) { request_line = strdup(yytext); strncpy(method_check, request_line, 4); return REQUESTLINE; }
Connection:" ".+ { return CONNECTION; }
Date:" "[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9]" "[0-9][0-9]:[0-9][0-9] { return DATE; }
Transfer-Encoding:" "(gzip|chunked|deflate) { return TRANSFERENCODING; }
Accept-Charset:" ".+ { return ACCEPTCHARSET; }
Referer:" ".+ { return REFERER; }
User-Agent:" ".+ { return USERAGENT; }
Content-Length:" "[0-9]+ { strcpy(con_length, yytext+16); content_length = strtol(con_length, NULL, 10);  content_header_check = 1; return CONTENTLENGTH; }
Expires:" "[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9][0-9][0-9]" "[0-9][0-9]:[0-9][0-9]  { return EXPIRES; }
\n { ++line_number; return ENDL; }
.+ { body_length += strlen(yytext); return BODYSTRING; }
<<EOF>> { return END_OF_FILE; }

%%



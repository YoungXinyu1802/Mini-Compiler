%{
// 待补充头文件
#include <stdio.h>
#include <string>
#include <iostream>

#define SAVE_TOKEN yylval.sVal = new std::string(yytext);
%}

%option noyywrap

ANY .
COMMENT "{"{ANY}*"}" 
DIGIT [0-9]
DIGITS {DIGIT}+
LETTER [_a-zA-Z]
ID {LETTER}({LETTER}|{DIGIT})*
POINT "."{DIGITS}
EXPONENT (e|E)("+"|"-")?{DIGITS}
INTNUM {DIGITS}
REALNUM {DIGITS}({POINT})?({EXPONENT})?
STRING "\""({LETTER}|{DIGIT})*"\""

%%
"//".*                                                   ;   //comments
"/*"{ANY}*"*/"                                            ;   //comments
[ \t\n]                                                 ;
\'.\'                                                   { 
                                                            yylval.cVal = yytext[1];
                                                            return CHAR; 
                                                        }
    /* 符号部分 */
"("                                                     { print(" \n"); return LP;}
")"                                                     { print(" \n"); return RP;} 
"["                                                     { print(" \n"); return LB;}
"]"                                                     { print(" \n"); return RB; }
"{"                                                     { print(" \n"); return LCB;}
"}"                                                     { print(" \n"); return RCB;}
"."                                                     { print(" \n"); return DOT;}
","                                                     { print(" \n"); return COMMA;}
":"                                                     { print(" \n"); return COLON;}
"*"                                                     { print(" \n"); return MUL;}
"/"                                                     { print(" \n"); return DIV;} 
"~"                                                     { print(" \n"); return NOT;}
"+"                                                     { print(" \n"); return PLUS;}
"-"                                                     { print(" \n"); return MINUS;}
"!="                                                    { print(" \n"); return NOEQUAL;}
"&&"                                                    { print(" \n"); return AND;}
"||"                                                    { print(" \n"); return OR;}
">="                                                    { print(" \n"); return GE;}
">"                                                     { print(" \n"); return GT; }
"<="                                                    { print(" \n"); return LE;} 
"<"                                                     { print(" \n"); return LT;} 
"=="                                                    { print(" \n"); return EQUAL;} 
"="                                                     { print(" \n"); return ASSIGN;} 
";"                                                     { print(" \n"); return SEMI;} 
    
    /* 关键字部分 */
if                                                      { print(" \n"); return IF;}
else                                                    { print(" \n"); return ELSE;}
while                                                   { print(" \n"); return WHILE;}
signed                                                  { print(" \n"); return SIGNED;}
throw                                                   { print(" \n"); return UNION;}
this                                                    { print(" \n"); return THIS;}
unsigned                                                { print(" \n"); return UNSIGNED;}
const                                                   { print(" \n"); return CONST;}
goto                                                    { print(" \n"); return GOTO;}
virtual                                                 { print(" \n"); return VIRTUAL;}
for                                                     { print(" \n"); return FOR;}
float                                                   { print(" \n"); return FLOAT;}
break                                                   { print(" \n"); return BREAK;}
auto                                                    { print(" \n"); return AUTO;}
class                                                   { print(" \n"); return CLASS;}
operator                                                { print(" \n"); return OPERATOR;}
case                                                    { print(" \n"); return CASE;}
do                                                      { print(" \n"); return DO;}
long                                                    { print(" \n"); return LONG;}
typedef                                                 { print(" \n"); return TYPEDEF;}
static                                                  { print(" \n"); return STATIC;}
friend                                                  { print(" \n"); return FRIEND;}
template                                                { print(" \n"); return TEMPLATE;}
default                                                 { print(" \n"); return DEFAULT;}
new                                                     { print(" \n"); return NEW;}
void                                                    { print(" \n"); return VOID;}
register                                                { print(" \n"); return REGISTER;}
return                                                  { print(" \n"); return RETURN;}
enum                                                    { print(" \n"); return ENUM;}
inline                                                  { print(" \n"); return INLINE;}
try                                                     { print(" \n"); return TRY;}
short                                                   { print(" \n"); return SHORT;}
continue                                                { print(" \n"); return CONTINUE;}
sizeof                                                  { print(" \n"); return SIZEOF;}
switch                                                  { print(" \n"); return SWITCH;}
private                                                 { print(" \n"); return PRIVATE;}
protected                                               { print(" \n"); return PROTECTED;}
asm                                                     { print(" \n"); return ASM;}
while                                                   { print(" \n"); return WHILE;}
catch                                                   { print(" \n"); return CATCH;}
delete                                                  { print(" \n"); return DELETE;}
public                                                  { print(" \n"); return PUBLIC;}
volatile                                                { print(" \n"); return VOLATILE;}
struct                                                  { print(" \n"); return STRUCT;}
printf                                                  { print(" \n"); return PRINTF;}
scanf                                                   { print(" \n"); return SCANF;}
main                                                    { print(" \n"); return MAIN;}



"int"|"char"|"double"|"boolean"                         SAVE_TOKEN; return SYS_TYPE;  
"false"|"true"                                          SAVE_TOKEN; return SYS_BOOL;                                               


 /* 数字，变量名，字符和字符串 */
{ID}                                                    SAVE_TOKEN; return IDENTIFIER;
{DIGITS}\.{DIGITS}                                      SAVE_TOKEN; yylval.dVal=atof(yylval.sVal->c_str()); return REAL; 
{DIGITS}                                                SAVE_TOKEN; yylval.iVal=atoi(yylval.sVal->c_str()); return INTEGER;
{STRING}                                                SAVE_TOKEN; yylval.sVal=atoi(yylval.sVal->c_str()); return STRING;

%%
%{
// 待补充头文件
#include "ast.hh"
#include <string>
#include <iostream>
#include "compiler.tab.h"

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
"("                                                     {return LP;}
")"                                                     {return RP;} 
"["                                                     {return LB;}
"]"                                                     {return RB; }
"{"                                                     {return LCB;}
"}"                                                     {return RCB;}
"."                                                     {return DOT;}
","                                                     {return COMMA;}
":"                                                     {return COLON;}
"*"                                                     {return MUL;}
"/"                                                     {return DIV;} 
"~"                                                     {return NOT;}
"+"                                                     {return ADD;}
"-"                                                     {return SUB;}
"!="                                                    {return NOEQUAL;}
"&&"                                                    {return AND;}
"||"                                                    {return OR;}
">="                                                    {return GE;}
">"                                                     {return GT; }
"<="                                                    {return LE;} 
"<"                                                     {return LT;} 
"=="                                                    {return EQUAL;} 
"="                                                     {return ASSIGN;} 
";"                                                     {return SEMI;} 
"<<"                                                    {return LD;}
">>"                                                    {return RD;}    
"%"                                                     {return MOD;}
    /* 关键字部分 */
if                                                      {return IF;}
else                                                    {return ELSE;}
while                                                   {return WHILE;}
signed                                                  {return SIGNED;}
throw                                                   {return UNION;}
this                                                    {return THIS;}
unsigned                                                {return UNSIGNED;}
const                                                   {return CONST;}
goto                                                    {return GOTO;}
virtual                                                 {return VIRTUAL;}
for                                                     {return FOR;}
float                                                   {return FLOAT;}
break                                                   {return BREAK;}
auto                                                    {return AUTO;}
class                                                   {return CLASS;}
operator                                                {return OPERATOR;}
case                                                    {return CASE;}
do                                                      {return DO;}
long                                                    {return LONG;}
typedef                                                 {return TYPEDEF;}
static                                                  {return STATIC;}
friend                                                  {return FRIEND;}
template                                                {return TEMPLATE;}
default                                                 {return DEFAULT;}
new                                                     {return NEW;}
void                                                    {return VOID;}
register                                                {return REGISTER;}
return                                                  {return RETURN;}
enum                                                    {return ENUM;}
inline                                                  {return INLINE;}
try                                                     {return TRY;}
short                                                   {return SHORT;}
continue                                                {return CONTINUE;}
sizeof                                                  {return SIZEOF;}
switch                                                  {return SWITCH;}
private                                                 {return PRIVATE;}
protected                                               {return PROTECTED;}
asm                                                     {return ASM;}
catch                                                   {return CATCH;}
delete                                                  {return DELETE;}
public                                                  {return PUBLIC;}
volatile                                                {return VOLATILE;}
struct                                                  {return STRUCT;}
printf                                                  {return PRINTF;}
scanf                                                   {return SCANF;}
main                                                    {return MAIN;}
cin                                                     {return CIN;}
cout                                                    {return COUT;}



"int"|"char"|"double"|"boolean"                         SAVE_TOKEN; return SYS_TYPE;  
"false"|"true"                                          SAVE_TOKEN; return SYS_BOOL;                                               


 /* 数字，变量名，字符和字符串 */
{ID}                                                    SAVE_TOKEN; return IDENTIFIER;
{DIGITS}\.{DIGITS}                                      SAVE_TOKEN; yylval.floatVal=atof(yylval.sVal->c_str()); return REAL; 
{DIGITS}                                                SAVE_TOKEN; yylval.intVal=atoi(yylval.sVal->c_str()); return INTEGER;
{STRING}                                                SAVE_TOKEN; yylval.sVal=yylval.sVal; return STRING;

%%
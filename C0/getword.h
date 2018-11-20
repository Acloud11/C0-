#pragma once
#include<stdio.h>

#define Max_Len 999			//单个单词最长	
#define	KeyNum 12			//保留字个数

typedef char symbol[15];

typedef enum {		//单词种类		关键字从0到11		分界符从12到30
	CONSTSY = 1,		
	INTSY,
	CHARSY,
	VOIDSY,
	IFSY,
	ELSESY,
	WHILESY,
	FORSY,
	MAINSY,
	SCANFSY,
	PRINTFSY,
	RETURNSY,
	COMMASY,
	SEMISY,
	EQUALSY,
	ASSIGNSY,
	PLUSSY,
	MINUSSY,
	LPARENTHESSY,
	RPARENTHESSY,
	STARSY,
	SLASHST,
	UNEQLSY,
	LESSSY,
	UNLAGERSY,
	LAGERSY,
	UNLESSSY,
	LSQUBRACKETSY,
	RSQUBRACKETSY,
	LCURLYBRACESY,
	RCURLYBRACKSY,
	CONINTSY,
	CONCHARSY,
	CONSTRSY,
	IDENSY
}types;



FILE *fp ;
char word[Max_Len];
types word_type;


int isBet(char c);
//int isPeriod(char c);
int isSpace(char c);
void getword();
int isNum(char c);
int isDelimiter(char c);
int isLetter(char c);
int isSemi(char c);
int isComma(char c);
//int isColon(char c);
int isPlus(char c);
int isMinus(char c);
int isStar(char c);
int isSlashes(char c);
int isLParentheses(char c);
int isRParentheses(char c);
int isLCurlyBraces(char c);
int isRCurlyBraces(char c);
int isSingQuo(char c);
int isDouQuo(char c);
int isRSquBracket(char c);
int isLSquBracket(char c);
int isExclamationMark(char c);
int isRCurlyBrace(char c);
int isLCurlyBrace(char c);
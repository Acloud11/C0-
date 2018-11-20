#include"getword.h"
#include<stdio.h>
#include<string.h>
char type_name[35][30] = {
	"Const",
	"Int",
	"Char",
	"Void",
	"If",
	"Else",
	"While",
	"For",
	"Main",
	"Scanf",
	"Printf",
	"Return" ,
	"Comma",
	"Semi",
	"Bequal",
	"Assign",
	"Plus",
	"Minus",
	"LParentheses",
	"RParentheses",
	"Star",
	"Slashes",
	"UnEql",
	"Less",
	"UnLarger",
	"Larger",
	"UnLess",
	"LSquBracket",
	"RSquBracket",
	"LCurlyBrace",
	"RCurlyBrace",
	"IntCon",
	"CharCon",
	"StrCon",
	"Iden" };
char identifiers[300][50];
int t = 0;

symbol keyword[KeyNum] = { "const","int","char","void","if","else","while","for","main","scanf","printf","return" };
symbol keyword_sta[KeyNum] = { "Const","Int","Char","Void","If","Else","While","For","Main","Scanf","Printf","Return" };


char delimiters[19][3] = { ",",";","==","=","+","-","(",")","*","/","!=","<","<=",">",">=","[","]","{","}" };
symbol delimiters_sta[19] = { "Comma","Semi","Bequal","Assign","Plus","Minus","LParentheses","RParentheses","Star","Slashes","UnEql","Less","UnLarger","Larger","UnLess","LSquBracket","RSquBracket","LCurlyBrace","RCurlyBrace" };


symbol con[3] = { "IntCON","CharCON","StrCON" };

int lineBeg = 0;
/*
int main() {
	fp = fopen("16061046_test.txt","r");
	getword();
	getchar();
}*/

//空白符号处理 
int isSpace(char c) {
	if (c == '\t' || c == ' ' || c == '\n') {
		return 1;
	}
	else return 0;
}

void getword() {
	int num = 0;
	int i = 0;
	char c;
	int state = 0;
	int cc = 0;					//单词计数器 
	int got = 0;

	while ((c = fgetc(fp)) != EOF) {
		if (got == 1) break;
		switch (state) {
		case 0:
			if (isLetter(c)) {
				state = 1;
				word[i++] = c;
			}
			else if (isNum(c)) {
				state = 3;
				num = c - '0';
			}
			else if (isSpace(c)) {
				state = 0;
			}
			else if (isDelimiter(c)) {
				if (c == '}') {
					state = 0;
					strcpy(word, "}");
			//		strcpy(word_type, "RCurlyBrace");
					word_type = RCURLYBRACKSY;
					i = 0;
					cc++;
					printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
					memset(word, 0, sizeof(word));
					got = 1;
				}
				else {
					state = 4;
					word[i++] = c;
				}
			}
			else if (isSingQuo(c)) {
				state = 5;
			}
			else if (isDouQuo(c)) {
				state = 6;
			}
			else {
				state = 0;
				printf("词法错误\n");
				memset(word, 0, sizeof(word));
				i = 0;
				while (c != EOF && c != ' ') {
					c = fgetc(fp);
				}
				fseek(fp, -1, SEEK_CUR);
			}
			break;
		case 1:
			if (isLetter(c)) {
				state = 1;
				word[i++] = c;
			}
			else if (isNum(c)) {
				state = 2;
				word[i++] = c;
			}
			else if (!isLetter(c) && !isNum(c)) {
				fseek(fp, -1, SEEK_CUR);
				word[i++] = '\0';
				state = 0;
				int j = 0;
				int judge = 0;
				for (; j < KeyNum; j++) {
					if (strcmp(word, keyword[j]) == 0) {
						//		sym = Key;
						//strcpy(word_type, keyword_sta[j]);
						word_type = j+1;	//枚举从1开始
						judge = 1;
						cc++;
						printf("%d,%s,%s\n", cc, type_name[word_type-1] , word);
						got = 1;
						memset(word, 0, sizeof(word));
						i = 0;
						break;
					}
				}
				if (judge != 1) {
					//	sym = Identifier;
				//	strcpy(word_type, IDEN);
					word_type = IDENSY;
				//	strcpy(identifiers[t], word);		加入标识符表
					cc++;
					printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
					got = 1;
					memset(word, 0, sizeof(word));
					i = 0;
				}
			}
			break;
		case 2:
			if (isNum(c) || isLetter(c)) {
				state = 2;
				word[i++] = c;
			}
			else if (!isLetter(c) && !isNum(c)) {
				fseek(fp, -1, SEEK_CUR);
				word[i++] = '\0';
				state = 0;
				//	sym = Identifier;
			//	strcpy(word_type, IDEN);
				word_type = IDENSY;
			//	strcpy(identifiers[t], word);	加入标识符表
				cc++;
				printf("%d,%s,%s\n", cc,type_name[word_type-1], word);
				got = 1;
				memset(word, 0, sizeof(word));
				i = 0;
			}
			break;
		case 3:
			if (isNum(c)) {
				state = 3;
				num = 10 * num + (c - '0');
			}
			else if (!isNum(c)) {
				fseek(fp, -1, SEEK_CUR);
				state = 0;
				//	sym = Num;
				cc++;
			//	strcpy(word_type, "IntCON");
				word_type = CONINTSY;
				printf("%d,IntCON,%d\n", cc, num);
				got = 1;
			}
			break;
		case 4:
			if (word[0] == '=' && c == '=') {
				state = 0;
				word[i++] = c;
				word[i] = '\0';
				//	sym = Demarcation;
			//	strcpy(word_type, "Bequal");
				word_type = EQUALSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				memset(word, 0, sizeof(word));
				i = 0;
			}
			else if (word[0] == '!' && c == '=') {
				state = 0;
				word[i++] = c;
				word[i] = '\0';
				//	sym = Demarcation;
			//	strcpy(word_type, "UnEql");
				word_type = UNEQLSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				memset(word, 0, sizeof(word));
				i = 0;
			}
			else if (word[0] == '<' && c == '=') {
				state = 0;
				word[i++] = c;
				word[i] = '\0';
				//	sym = Demarcation;
				//strcpy(word_type, "UnLarger");
				word_type = UNLAGERSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				memset(word, 0, sizeof(word));
				i = 0;
			}
			else if (word[0] == '>' && c == '=') {
				state = 0;
				word[i++] = c;
				word[i] = '\0';
				//	sym = Demarcation;
				//strcpy(word_type, "UnLess");
				word_type = UNLESSSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				memset(word, 0, sizeof(word));
				i = 0;
			}
			else if (word[0] == '!' && c != '=') {
				printf("词法错误\n");
				state = 0;
				fseek(fp, -1, SEEK_CUR);	//??
				i = 0;
				memset(word, 0, sizeof(word));
			}
			else {
				fseek(fp, -1, SEEK_CUR);
				state = 0;
				word[i++] = '\0';
				int k = 0;
				for (; k < 17; k++) {
					if (strcmp(word, delimiters[k]) == 0) {
						//strcpy(word_type, delimiters_sta[k]);
						word_type = k + 13;
						break;
					}
				}
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				i = 0;
				memset(word, 0, sizeof(word));
			}
			break;
		case 5:
			if (isPlus(c) || isMinus(c) || isStar(c) || isSlashes(c) || isNum(c) || isLetter(c)) {
				word[i++] = c;
				state = 7;
			}
			else if (c == '\'') {
				printf("词法错误，字符不能为空\n");
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
				fseek(fp, -1, SEEK_CUR);	//??
			}
			else if (!isPlus(c) && !isMinus(c) && !isStar(c) && !isSlashes(c) && !isNum(c) && !isLetter(c)) {
				printf("词法错误，字符类型有误\n");
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
				fseek(fp, -1, SEEK_CUR);	//??
			}
			break;
		case 6:
			if (c <= 126 && c >= 32 && c != 34) {
				state = 8;
				word[i++] = c;
			}
			else {
				printf("词法错误，字符串类型有误\n");
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
				fseek(fp, -1, SEEK_CUR);	//??
			}
			break;
		case 7:
			if (c == '\'') {
				word[i] = '\0';
				//strcpy(word_type, "CharCON");
				word_type = CONCHARSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
			}
			else {
				printf("词法错误，字符只能有一个字符\n");
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
				fseek(fp, -1, SEEK_CUR);
			}
			break;
		case 8:
			if (c <= 126 && c >= 32 && c != 34) {
				state = 8;
				word[i++] = c;
			}
			else if (c == '\"') {
				word[i] = '\0';
				//strcpy(word_type, "StrCON");
				word_type = CONSTRSY;
				cc++;
				printf("%d,%s,%s\n", cc, type_name[word_type-1], word);
				got = 1;
				state = 0;
				i = 0;
				memset(word, 0, sizeof(word));
			}

		}

	}

}
//是否是字母 
int isLetter(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') return 1;
	else return 0;
}
//是否是数字 
int isNum(char c) {
	if (c >= '0' && c <= '9') return 1;
	else return 0;
}
//是否是分界符 
int isDelimiter(char c) {
	if (isComma(c) || isSemi(c) || isBet(c) /*||isColon(c)*/ || isPlus(c) || isMinus(c) || isStar(c) || isSlashes(c) || isLParentheses(c) || isRParentheses(c) || isLCurlyBraces(c) || isRCurlyBraces(c)
		|| isLSquBracket(c) || isRSquBracket(c) || isExclamationMark(c) || isRCurlyBrace(c) || isLCurlyBrace(c)/*||isPeriod(c)*/) {
		return 1;
	}
	else return 0;
}
//是否是等号
int isBet(char c) {
	if (c == '=') {
		return 1;
	}
	else return 0;
}

/*ÊÇ·ñÊÇ¾äºÅ
int isPeriod(char c){
	if(c == '.'){
		return 1;
	}
	else return 0;
}*/

//是否是逗号 
int isComma(char c) {
	if (c == ',') {
		return 1;
	}
	else return 0;
}
//是否是分号
int isSemi(char c) {
	if (c == ';') {
		return 1;
	}
	else return 0;
}
/*ÊÇ·ñÊÇÃ°ºÅ
int isColon(char c){
	if(c == ':'){
		return 1;
	}
	else return 0;
} */
//是否是加号
int isPlus(char c) {
	if (c == '+') {
		return 1;
	}
	else return 0;
}
//是否是减号
int isMinus(char c) {
	if (c == '-') {
		return 1;
	}
	else return 0;
}
//是否是星号
int isStar(char c) {
	if (c == '*') {
		return 1;
	}
	else return 0;
}
//是否是斜杠
int isSlashes(char c) {
	if (c == '/') {
		return 1;
	}
	else return 0;
}
//是否是左圆括号
int isLParentheses(char c) {
	if (c == '(') {
		return 1;
	}
	else return 0;
}
//是否是右圆括号
int isRParentheses(char c) {
	if (c == ')') {
		return 1;
	}
	else return 0;
}
//左尖括号
int isLCurlyBraces(char c) {
	if (c == '<') {
		return 1;
	}
	else return 0;
}
//右尖括号
int isRCurlyBraces(char c) {
	if (c == '>') {
		return 1;
	}
	else return 0;
}
//单引号
int isSingQuo(char c) {
	if (c == '\'') {
		return 1;
	}
	else return 0;
}
//双引号
int isDouQuo(char c) {
	if (c == '\"') {
		return 1;
	}
	else return 0;
}
//左方括号
int isLSquBracket(char c) {
	if (c == '[') {
		return 1;
	}
	else return 0;
}
//右方括号
int isRSquBracket(char c) {
	if (c == ']') {
		return 1;
	}
	else return 0;
}
//感叹号
int isExclamationMark(char c) {
	if (c == '!') {
		return 1;
	}
	else return 0;
}
//左大括号
int isLCurlyBrace(char c) {
	if (c == '{') {
		return 1;
	}
	else return 0;
}
//右大括号
int isRCurlyBrace(char c) {
	if (c == '}') {
		return 1;
	}
	else return 0;
}

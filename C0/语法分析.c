#include"getword.h"
#include<stdio.h>
#include<string.h>
/**	语法分析子程序，事先预读一位，
	在退出分析程序前预读下一位
*/

#define fsys [")",";"]


void conDescripe();//常量说明
void conDefine(); //常量定义
void varDescripe();	//变量说明
void varDefine();	//变量定义



int main() {

	int cc = 0;					//单词计数器 
	fp = fopen("语法test.txt", "r");
	getword();
	conDescripe();

	getchar();
}
/*


*/







void toCommaOrSemi() {		//跳读直到逗号或分号
	while (word_type != COMMASY && word_type != SEMISY) {
		getword();
	}
}


void conDescripe() {	//常量说明		const 常量定义；{const 常量定义;}
	while (word_type == CONSTSY) {			//每次循环对应一条常数说明语句
		getword();
		//conDefine();
		if (word_type != INTSY && word_type != CHARSY) {		//常量定义	int(char) 标识符 = 整数{,标识符 = 整数}
			getword();
			//error();		//ERROR_NOT_TYPE
			printf("ERROR_NOT_TYPE");
			while (word_type != SEMISY) getword();
			getword();
			continue;
		}
		getword();
		while (1) {		//标识符 = 整数{,标识符 = 整数}
			int sign = 0;
			if (word_type != IDENSY) {
				getword();
				//error();		//ERROR_NOT_NAME
				printf("ERROR_NOT_NAME");
				toCommaOrSemi();
			}
			else {
				getword();
				if (word_type != ASSIGNSY) {
					printf("ERROR_NOT_ASSIGN");
					toCommaOrSemi();
				}
				else {
					getword();
					if (word_type == PLUSSY) {
						getword();
						sign = 1;
					}
					else if (word_type == MINUSSY) {
						getword();
						sign = -1;
					}
					if (word_type == INTSY) {
						getword();
					}
					else if (word_type == CHARSY) {
						if (sign != 0) {
							printf("ERROR_CHAR_WITH_SIGN");
							toCommaOrSemi();
						}
						else getword();
					}
				}
			}
			if (word_type == SEMISY) {		// 遇到分号当前语句结束
				getword();
				break;
			}
			if (word_type != COMMASY) {
				printf("ERROR_NOT_COMMA");
				while (word_type != SEMISY) {
					getword();
				}
				getword();
			}
		}
	}
}
/*
void conDefine() {
	if (word_type == INTSY || word_type == CHARSY) {
		do {
			getword();
			isIden();
			if (word_type != ASSIGNSY) {
				error();
			}
			else {
				getword();
				isInt();
				getword();
				if (word_type == SEMISY) {
					getword();
				}
				else {
					error();
				}
			}
		} while (word_type == COMMASY);
	}
	else {
		error();
	}
}*/


void varDescripe() {
	varDefine();
}
void varDefine() {

}
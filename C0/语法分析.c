#include"getword.h"
#include<stdio.h>
#include<string.h>
/**	�﷨�����ӳ�������Ԥ��һλ��
	���˳���������ǰԤ����һλ
*/

#define fsys [")",";"]


void conDescripe();//����˵��
void conDefine(); //��������
void varDescripe();	//����˵��
void varDefine();	//��������



int main() {

	int cc = 0;					//���ʼ����� 
	fp = fopen("�﷨test.txt", "r");
	getword();
	conDescripe();

	getchar();
}
/*


*/







void toCommaOrSemi() {		//����ֱ�����Ż�ֺ�
	while (word_type != COMMASY && word_type != SEMISY) {
		getword();
	}
}


void conDescripe() {	//����˵��		const �������壻{const ��������;}
	while (word_type == CONSTSY) {			//ÿ��ѭ����Ӧһ������˵�����
		getword();
		//conDefine();
		if (word_type != INTSY && word_type != CHARSY) {		//��������	int(char) ��ʶ�� = ����{,��ʶ�� = ����}
			getword();
			//error();		//ERROR_NOT_TYPE
			printf("ERROR_NOT_TYPE");
			while (word_type != SEMISY) getword();
			getword();
			continue;
		}
		getword();
		while (1) {		//��ʶ�� = ����{,��ʶ�� = ����}
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
			if (word_type == SEMISY) {		// �����ֺŵ�ǰ������
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
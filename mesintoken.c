/*
	NIM					: 13517099
    Nama				: Asif Hummam Rais
    Tanggal				: 27 September 2018
    Topik praktikum		: Mesin Karakter, Mesin Kata
    Deskripsi			: Mesin Token
*/
/* File: mesintoken.c */

#include<stdio.h>
#include "mesintoken.h"

boolean EndToken;
Token CToken;
char CC;

void ADV(){
	scanf("%c", &CC);
}

void IgnoreBlank(){
	while ((CC == BLANK) && (CC != MARK))
		ADV();
}

void STARTTOKEN(){
	ADV();
	IgnoreBlank();
	if (CC == MARK)
		EndToken = true;
	else {
		EndToken = false;
		SalinToken();
	}
}

void ADVTOKEN(){
	IgnoreBlank();
	if (CC == MARK)
		EndToken = true;
	else {
		SalinToken();
	}
}

boolean isSymbol(char c){
	return (CC == '+' || CC == '-' || CC == '*' || CC == '/' || CC == '^' || CC == '(' || CC == ')');
}

void SalinToken(){
	int i = 1;
	if (isSymbol(CC)){
		
		CToken.symbol = CC;
		CToken.value = -1;
		ADV();
		
	} else {
		
		boolean STOP;
		boolean comma = false;
		CToken.symbol = 'b';
		CToken.value = 0;
		
		do {
			CToken.value *= 10;
			CToken.value += (int) CC - '0';
			ADV();
			STOP = ((CC == MARK) || (CC == BLANK) || (i == NMax) || (CC == '.') || (isSymbol(CC)));
			if (!STOP)
				i++;
		} while (!STOP);
		
		if (CC == '.'){
			STOP = true;
			float comma_param = 0.1;
			ADV();
			do {
				CToken.value += comma_param * ((int)CC-'0');
				comma_param *= 0.1;
				ADV();
				STOP = ((CC == MARK) || (CC == BLANK) || (i == NMax) || (isSymbol(CC)));
				if (!STOP)
					i++;
			} while (!STOP);
		}
		
	}

}

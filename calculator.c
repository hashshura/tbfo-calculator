#include <math.h>
#include <stdio.h>
#include "mesintoken.h"
#include "stackt.h"

Stack S, S_Reversed;
infotype P;

float parse_expression(Stack *tok);
float parse_term(Stack *tok);
float parse_factor(Stack *tok);
float parse_item(Stack *tok);

float parse_expression(Stack *tok){
	float result = parse_term(tok);
	infotype t = InfoTop(*tok);
	while ((t.symbol ==  '+') || (t.symbol == '-')){
		Pop(tok);
		float rhs = parse_term(tok);
		if (t.symbol == '+') result = result + rhs;	
			else result = result - rhs;
		t = InfoTop(*tok);
	}
	return result;
}

float parse_term(Stack *tok){
	float result = parse_factor(tok);
	infotype t = InfoTop(*tok);
	while ((t.symbol ==  '*') || (t.symbol == '/')){
		Pop(tok);
		float rhs = parse_factor(tok);
		if (t.symbol == '*') result = result * rhs;	
			else result = result / rhs;
		t = InfoTop(*tok);
	}
	return result;
}

float parse_factor(Stack *tok){
	infotype t = InfoTop(*tok);
	if((t.symbol == '+') || (t.symbol == '-'))
		Pop(tok);
	float result = parse_item(tok);
	if(t.symbol == '-'){
		result *= -1;
	}
	t = InfoTop(*tok);
	if(t.symbol == '^'){
		Pop(tok);
		result = pow(result, parse_factor(tok));
	}
	return result;
}

float parse_item(Stack *tok){
	infotype t = InfoTop(*tok);
	float result;
	if(t.symbol == 'b'){
		result = t.value;
		Pop(tok);
	} else if(t.symbol == '('){
		Pop(tok);
		result = parse_expression(tok);
		Pop(tok);
	}
	return result;
}

int main(){
	
	CreateEmpty(&S);
	STARTTOKEN();
	while (!EndToken){
		P.symbol = CToken.symbol;
		P.value = CToken.value;
		Push(&S, P);
		ADVTOKEN();
	}
	
	CreateEmpty(&S_Reversed);
	while (!IsEmpty(S)){
		Push(&S_Reversed, InfoTop(S));
		Pop(&S);
	}
	
	printf("%f\n", parse_expression(&S_Reversed));
	
}
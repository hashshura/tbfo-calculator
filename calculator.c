#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define BLANK ' '
#define ENDL '\n'
#define POINT '.'

int top_idx;
char s[1000005];

char InfoTop(){
	return s[top_idx];
}

void Pop(){
	do {
		top_idx++;
	} while (InfoTop() == BLANK);
}

void readln(char * s){
	
	char c;
	int idx = 0;
	do {
		scanf("%c", &c);
		s[idx] = c;
		idx++;
	} while (c != ENDL);
	
}

bool is_number(char x){
	return (x >= '0' && x <= '9');
}

bool is_symbol(char x){
	return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')');
}

double parse_expression();
double parse_term();
double parse_factor();
double parse_item();
double parse_number();

double parse_expression(){
	double result = parse_term();
	char t = InfoTop();
	while ((t ==  '+') || (t == '-')){
		Pop();
		double rhs = parse_term();
		if (t == '+') result = result + rhs;	
			else result = result - rhs;
		t = InfoTop();
	}
	return result;
}

double parse_term(){
	double result = parse_factor();
	char t = InfoTop();
	while ((t ==  '*') || (t == '/')){
		Pop();
		double rhs = parse_factor();
		if (t == '*') result = result * rhs;	
			else result = result / rhs;
		t = InfoTop();
	}
	return result;
}

double parse_factor(){
	char t = InfoTop();
	if ((t == '+') || (t == '-'))
		Pop();
	double result = parse_item();
	if (t == '-')
		result *= -1;
	t = InfoTop();
	if (t == '^'){
		Pop();
		result = pow(result, parse_factor());
	}
	return result;
}

double parse_item(){
	char t = InfoTop();
	double result;
	if (is_number(t)){
		result = parse_number();
	} else if (t == '('){
		Pop();
		result = parse_expression();
		if (InfoTop() == ')')
			Pop();
	}
	return result;
}

double parse_number(){
	bool comma = false;
	bool stop = false;
	double result = 0;
	do {
		result *= 10;
		result += (int) InfoTop() - '0';
		Pop();
		stop = ((InfoTop() == ENDL) || (InfoTop() == BLANK) || (InfoTop() == POINT) || (is_symbol(InfoTop())));
	} while (!stop);
	
	if (InfoTop() == '.'){
		stop = true;
		double comma_param = 0.1;
		Pop();
		do {
			result += comma_param * ((int) InfoTop() - '0');
			comma_param *= 0.1;
			Pop();
			stop = ((InfoTop() == ENDL) || (InfoTop() == BLANK) || (is_symbol(InfoTop())));
		} while (!stop);
	}
	
	return result;
}

int main(){
	
	readln(s);
	top_idx = 0;
	if (InfoTop() == ' ')
		Pop();
	printf("%lf\n", parse_expression());
	
}
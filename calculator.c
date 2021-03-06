#include <stdio.h>
#include <stdbool.h>
#include <complex.h>

#define BLANK ' '
#define ENDL 0
#define POINT '.'
#define IMAG 'i'

bool err;
int top_idx;
char s[1000005];

char InfoTop(){
	return s[top_idx];
}

void Pop(){
	do 
		top_idx++;
	while (InfoTop() == BLANK);
}

void read_expression(){
	
	char c;
	int idx = 0;
	do {
		scanf("%c", &c);
		if (c == '\n') c = 0;
		s[idx] = c;
		idx++;
	} while (c != ENDL);
	
}

bool is_number(char x){
	return (x >= '0' && x <= '9');
}

bool is_symbol(char x){
	return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')' || x == ' ' || x == BLANK || x == ENDL || x == POINT || x == IMAG);
}

double complex syntax_error(char * expected){
	
	for (int i = 0; i < top_idx + 3; i++)
		printf(" ");
	printf("^\n");
	printf("[!] SYNTAX ERROR: Expected %s, found '%c'.\n", expected, s[top_idx]);
	err = true;
	return 0;
	
}

double complex math_error(char * msg){
	
	for (int i = 0; i < top_idx + 3; i++)
		printf(" ");
	printf("^\n");
	printf("[!] MATH ERROR: %s.\n", msg);
	err = true;
	return 0;
	
}

double complex parse_expression();
double complex parse_term();
double complex parse_factor();
double complex parse_item();
double complex parse_number();

double complex parse_expression(){
	double complex result = parse_term();
	if (err) return 0;
	char t = InfoTop();
	while ((t ==  '+') || (t == '-')){
		Pop();
		double complex rhs = parse_term();
		if (err) return 0;
		if (t == '+') result = result + rhs;	
			else result = result - rhs;
		t = InfoTop();
	}
	return result;
}

double complex parse_term(){
	double complex result = parse_factor();
	if (err) return 0;
	char t = InfoTop();
	while ((t ==  '*') || (t == '/')){
		Pop();
		int top_idx_tmp = top_idx;
		double complex rhs = parse_factor();
		if (err) return 0;
		if (t == '*') result = result * rhs;	
			else {
				result = result / rhs;
				if (rhs == 0){
					top_idx = top_idx_tmp;
					return math_error("Divide by zero");
				}
			}
		t = InfoTop();
	}
	return result;
}

double complex parse_factor(){
	char t = InfoTop();
	if (t == '-')
		Pop();
	double complex result = parse_item();
	if (err) return 0;
	if (t == '-')
		result *= -1;
	t = InfoTop();
	if (t == '^'){
		Pop();
		int top_idx_tmp = top_idx;
		double complex rhs = parse_factor();
		if (result == 0 && rhs == 0){
			top_idx = top_idx_tmp;
			return math_error("Zero to the power of zero");
		}
		result = cpowl(result, rhs);
		if (err) return 0;
	}
	return result;
}

double complex parse_item(){
	char t = InfoTop();
	double complex result;
	if (is_number(t) || t == IMAG){
		result = parse_number();
		if (err) return 0;
	} else if (t == '('){
		Pop();
		result = parse_expression();
		if (err) return 0;
		if (InfoTop() == ')')
			Pop();
		else 
			return syntax_error("')'");
	} else
		return syntax_error("number or expression");
	return result;
}

double complex parse_number(){
	double complex result = 0;
	if (InfoTop() == IMAG){
		Pop();
		return 1*I;
	}
	
	do {
		if (!is_number(InfoTop()))
			return syntax_error("operator, '.', or 'i'");
		result *= 10;
		result += (int) InfoTop() - '0';
		Pop();
	} while (!is_symbol(InfoTop()));
	
	if (InfoTop() == '.'){
		double complex comma_param = 0.1;
		Pop();
		do {
			if (!is_number(InfoTop())){
				if (is_symbol(InfoTop())) return syntax_error("number");
					else return syntax_error("operator or 'i'");
			}
			result += comma_param * ((int) InfoTop() - '0');
			comma_param *= 0.1;
			Pop();
		} while (!is_symbol(InfoTop()));
	}
	
	if (InfoTop() == 'i'){
		result *= I;
		Pop();
	}
	
	return result;
}

int main(){
	
	printf("Welcome to Calculator!\n");
	printf("\n");
	printf("Type an expression after \">>\".\n");
	printf("ENTER to evaluate the expression.\n");
	printf("CTRL + C to exit the program.\n");
	
	while (true){
		err = false;
		printf("\n>> ");
		read_expression();
		top_idx = 0;
		if (InfoTop() == ' ')
			Pop();
		double complex result = parse_expression();
		if (!err && s[top_idx] != ENDL){
			syntax_error("end of expression");
		} else if (!err) {
			printf("%s = ", s);
			printf("%lf", creal(result));
			if (cimag(result) < 0)
				printf(" - %lfi", -cimag(result));
			else if (cimag(result) > 0)
				printf(" + %lfi", cimag(result));
			printf("\n");
		}
	}
	
}

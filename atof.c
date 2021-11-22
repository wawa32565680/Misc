#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void to_pos(char*,char*);
void strins(char*,char*,size_t);
double count(char*);
double cal(char,double,double);
double fac(double);
int prio(char);
int is_num(char);
int main(){
	char in[100] = {'\0'};
	char pos[100] = {'\0'};
	gets(in);
	printf("=%g", count(in));
}


void to_pos(char *in,char *out){
	int i, j, top;
	char stack[100] = {'\0'};
	for (i = 0, j = 0, top = 0 ; in[i] != '\0' ; i++){
		switch (in[i]){
			case '(':
				stack[++top] = in[i];
				break;
			case '+':	case '-':	case '*':	case '/':	case '^': case '!': case '@':
				if (in[i] == '-' && (!is_num(in[i - 1]) && in[i - 1] != ')') || i == 0)
					in[i] = '#';
				while (prio(stack[top]) >= prio(in[i])){
					out[j++] = stack[top--];
					out[j++] = ' ';
				}
				stack[++top] = in[i];
				break;
			case ')':
				while (stack[top] != '('){
					out[j++] = stack[top--];
					out[j++] = ' ';
				}
				top--;
				break;
			case 'x':
			default:
				out[j++] = in[i];
				if (!is_num(in[i + 1]) && in[i + 1] != 'x')
					out[j++] = ' ';
				
		}
	}
	while (top > 0){
		out[j++] = stack[top--];
		out[j++] = ' ';
	}
}

int prio(char op){
	switch (op){
		case '#':							return 4;
		case '^':	case '@':	case '!':	return 3;
		case '*':	case '/':				return 2;
		case '+':	case '-':				return 1;
		default:							return 0;
	}
}

double cal(char op,double a,double b){
	switch (op){
		case '+':	return a + b;
		case '-':	return a - b;
		case '*':	return a * b;
		case '/':	return a / b;
		case '^':	return pow(a,b);
	}
}

double count(char *in){
	int i, j, k, top;
	char pos[100] = {'\0'};
	char opnd[100] = {'\0'};
	double stack[100] = {0.0};
	to_pos(in, pos);
	puts(pos);
	for (i = 0, top = 0, k = 0 ; pos[i] != '\0' ; i++){
		switch (pos[i]){
			case '#':
				stack[top] *= -1.0;
				break;
			case '!':
				stack[top] = fac(stack[top]);
				break;
			case '@':
				stack[top] = sqrt(stack[top]);
				break;
			case '+': case '-': case '*': case '/': case '^':
				stack[top - 1] = cal(pos[i], stack[top - 1], stack[top]);
				top--;
				break;
			case ' ':
				for (j = 0 ; j < 50 ; j++)
					opnd[j] = '\0';
				k = 0;
				break;
			default:
				opnd[k++] = pos[i];
				if (!is_num(pos[i + 1]))
					stack[++top] = atof(opnd);
		}
	}
	return stack[top];
}

int is_num(char c){
	return (c >= '0' && c <= '9');
}

double fac(double x){
	if (x == 0 || x == 1)
		return 1;
	else
		return x * fac(x - 1);
}

void strins(char *str,char *in,size_t p){
	int i, top;
	char to[100] = {"\0"};
	strncpy(to,str,p);
	strcat(to,in);
	top = strlen(to);
	for (i = p ; i < strlen(str) ; i++)
		to[top++] = str[i];
	strcpy(str,to);
}


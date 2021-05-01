#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200


void to_pos(char*,char*);
void clear(char*,int);
int priority(char);
int is_number(char);
double count(char*);
double cal(char,double,double);

int main(){
	char str[MAX] = {'\0'};
	//char pos[MAX] = {'\0'};
	int i;
	double x;
	gets(str);
	printf("\n%g", count(str));
}



int priority(char op){
	switch (op){
		case '*':	case '/':	return 2;
		case '+':	case '-':	return 1;
		default:				return 0;
	}
}

void to_pos(char *in,char *out){
	int i, j, top;
	char stack[MAX] = {'\0'};
	for (i = 0, j = 0, top = 0 ; in[i] != '\0' ; i++){
		switch (in[i]){
			case '(':
				stack[++top] = in[i];
				break;
			case '+': case '-': case '*': case '/':
				out[j++] = ' ';
				while (priority(stack[top]) >= priority(in[i])){
					out[j++] = stack[top--];
					out[j++] = ' ';
				}
				stack[++top] = in[i];
				break;
			case ')':
				while(stack[top] != '('){
					out[j++] = ' ';
					out[j++] = stack[top--];
				}
				top--;
				break;
			default:
				out[j++] = in[i];
		}
	}
	while (top > 0){
		out[j++] = ' ';
		out[j++] = stack[top--];
	}

}

int is_number(char c){
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

double count(char *in){
	int i, j, top, k;
	char pos[MAX] = {'\0'};
	char opnd[10] = {'\0'};
	double stack[MAX] = {0.0};
	to_pos(in,pos);
	puts(pos);
	for (i = 0, top = 0, k = 0; pos[i] != '\0' ; i++){
		switch (pos[i]){
			case '+': case '-': case '*': case '/':
				stack[top - 1] = cal(pos[i], stack[top - 1], stack[top]);
				top--;
				break;
			case ' ':
				clear(opnd,10);	
				k = 0;
				break;
			default:
				opnd[k++] = pos[i];
				if (!is_number(pos[i + 1])){
					stack[++top] = atof(opnd);
					//printf("%g ", stack[top]);
				}
				break;
		}
	}
	//for (i = 0 ; i <= top ; i++)
		//printf("\n%g", stack[i]);
	return stack[top];
}

double cal(char op,double a,double b){
	switch (op){
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
}

void clear(char *str,int lenth){
	int i;
	for (i = 0 ; i < lenth ; i++)
		str[i] = '\0';
}


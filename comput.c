#include <stdio.h>
#include <stdlib.h>

typedef char STR[100];
typedef float (*COUNT)(float,float);
typedef struct formula{
	float num;
	int is_counted;
	char op;
}formula;
int select_oper(char);
float add(float,float);
float sub(float,float);
float mul(float,float);
float dive(float,float);
float ori(float,float);

int main(){
	formula f[30];
	COUNT oper[5] = {add, sub, mul, dive, ori};
	STR str;
	int i = 0, j = 0, k;
	do{
		scanf("%f%c", &f[i].num, &f[i].op);
		f[i].is_counted = 0;
		i++;
	}while (!(f[i - 1].op == '\n' || f[i - 1].op == '='));
	k = i;
	for (i = 0 ; i < k ; i++)
		if (f[i].op == '\n')
			printf("%.0f=", f[i].num);
		else
			printf("%.0f%c", f[i].num, f[i].op);
	for (i = 0 ; i < k - 1 ; i++){
		for (j = i + 1 ; j < k ; j++){
			if (f[j].is_counted == 0 && (f[i].op == '*' || f[i].op == '/')){
				f[j].is_counted = 1;
				f[i].num = oper[select_oper(f[i].op)](f[i].num,f[j].num);
				f[i].op = f[j].op;
			}
		}
	}
	for (i = 0 ; i < k - 1 ; i++){
		for (j = i + 1 ; j < k ; j++){
			if (f[j].is_counted == 0 && (f[i].op == '+' || f[i].op == '-')){
				f[j].is_counted = 1;
				f[i].num = oper[select_oper(f[i].op)](f[i].num, f[j].num);
				f[i].op = f[j].op;
			}
		}
	}
	printf("%.2f", f[0].num);
	/*
	for (i = 0 ; i < k ; i++)
		if (!f[i].is_counted)
			printf("%.0f%c", f[i].num, f[i].op);
	*/
}

float add(float a,float b){
	return a + b;
}

float sub(float a,float b){
	return a - b;
}

float mul(float a,float b){
	return a * b;
}

float dive(float a,float b){
	return a / b;
}

float ori(float a,float b){
	return a;
}

int select_oper(char op){
	switch (op){
		case '+':
			return 0;
		case '-':
			return 1;
		case '*':
			return 2;
		case '/':
			return 3;
		default:
			return 4;
	}
}


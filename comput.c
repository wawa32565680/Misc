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
void compute(formula*,int,COUNT*);


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
	compute(f,k,oper);
	printf("%.0f", f[0].num);
}

void compute(formula *f,int lenth,COUNT *oper){
	int i, j;
	for (i = 0 ; i < lenth ; i++){
		if (f[i].is_counted == 1)
			continue;
		for (j = i + 1 ; j < lenth ; j++){
			if (f[j].is_counted == 0){
				if (f[i].op == '*' || f[i].op == '/'){
					f[i].num = oper[select_oper(f[i].op)](f[i].num, f[j].num);
					f[i].op = f[j].op;
					f[j].is_counted = 1;
				}
				else
					break;
			}
		}
	}
	for (i = 0 ; i < lenth ; i++){
		if (f[i].is_counted == 1)
			continue;
		for (j = i + 1 ; j < lenth ; j++){
			if (f[j].is_counted == 0){
				if (f[i].op == '+' || f[i].op == '-'){
					f[i].num = oper[select_oper(f[i].op)](f[i].num, f[j].num);
					f[i].op = f[j].op;
					f[j].is_counted = 1;
				}
				else
					break;
			}
		}
	}
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


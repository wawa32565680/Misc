/*
廢棄的程式
廢棄的程式
廢棄的程式
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char STR[100];
typedef float (*COUNT)(float,float);
typedef struct formula{
	float num;
	int is_counted, priority;
	char op;
}formula;
int select_oper(char);
int is_op(char);
int is_count_able(formula*,int,const int);
float add(float,float);
float sub(float,float);
float mul(float,float);
float dive(float,float);
float ori(float,float);
void compute(formula*,int,COUNT*,const int prio);


int main(){
	formula f[100];
	COUNT oper[5] = {add, sub, mul, dive, ori};
	STR str;
	int i = 0, j = 0, k, max = 0;
	/*
	do{
		scanf("%f%c", &f[i].num, &f[i].op);
		f[i].is_counted = 0;
		i++;
	}while (!(f[i - 1].op == '\n' || f[i - 1].op == '='));
	*/
	//f[0].num = 0.00000000000000000000000000000000000;
	fgets(str,100,stdin);
	for (i = 0 ; i < 100 ; i++){
		f[i].num = 0;
		f[i].priority = 0;
		f[i].is_counted = 0;
	}
	for (i = 0 ; i < strlen(str) ; i++){
		if (str[i] >= '0' && str[i] <= '9'){
			f[j].priority = k;
			f[j].num = f[j].num * 10 + (str[i] - '0');
		}
		else if (str[i] == '('){
			k++;
			continue;
		}
		else if (str[i] == ')'){
			k--;
			continue;
		}
		else if (is_op(str[i])){
			f[j].op = str[i];
			j++;
		}
	}
	k = j;
	/*
	for (i = 0 ; i < k ; i++)
		if (f[i].op == '\n')
			printf("%.0f=", f[i].num);
		else
			printf("%.0f%c", f[i].num, f[i].op);
	*/
	for (i = 0 ; i < k ; i++){
		if (f[i].priority > max)
			max = f[i].priority;
	}
	for (i = 0 ; i < k ; i++)
		printf("%g%c", f[i].num, f[i].op);
	for (max ; max >= 0 ; max--)
		compute(f,k,oper,max);
	for (i = 0 ; i < k ; i++)
		if (f[i].is_counted == 0)
			printf("%g ", f[i].num);
}

void compute(formula *f,int lenth,COUNT *oper,const int prio){
	int i, j;
	for (i = 0 ; i < lenth ; i++){
		if (f[i].is_counted == 1 || f[i].priority != prio)
			continue;
		for (j = i + 1 ; j < lenth ; j++){
			if (f[j].is_counted == 0 && f[j].priority == prio && f[i].priority == prio){
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
	//====================================================================================
	for (i = 0 ; i < lenth ; i++){
		if (f[i].is_counted == 1 || f[i].priority != prio)
			continue;
		for (j = i + 1 ; j < lenth ; j++){
			if (f[j].is_counted == 0 && f[j].priority == prio && f[i].priority == prio){
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
	
	for (i = 0 ; i < lenth ; i++){
		if (f[i].priority == prio)
			f[i].priority--;
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

int is_op(char c){
	int i;
	const char op[5] = {'+', '-' ,'*' ,'/', '='};
	for (i = 0 ; i < 5 ; i++)
		if (c == op[i]);
			return 1;
	return 0;
}



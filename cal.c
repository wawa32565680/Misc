#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calFun.h" //�֤� 

int main(){
	char str[MAX] = {'\0'};
	int i;
	double x;
	gets(str);
	printf("\n%g", count(str));
}

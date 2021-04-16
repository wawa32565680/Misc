#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
int box[4][4] = {
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0} 
};

char map[20][20];

void turn_angle(int[4][4]);
void left_test(int[4][4]);//¥ª±À 
void down_test(int[4][4]);
int is_down(int[4][4]);
int is_wall(int[4][4]);//¬O§_¸IÀð 
void fix(int[4][4]);
void re_fresh();
int main(){
	int t, is = 0;
	char c;
	re_fresh();
	while (!is){
		t = 20000;
		while (t > 0){
			if (kbhit()){
				c = getch();
				if (c == ' '){
					turn_angle(box);
					fix(box);
					re_fresh();
				}
				else if (c == 'Q' || c == 'q'){
					is = 1;
					break;
				}
			}
			t--;
		}
		re_fresh();
	}
	
}
void re_fresh(){
	system("CLS");
	int i, j;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ;  j < 4 ; j++)
			if (box[i][j])
				printf("#");
			else
				printf(" ");
		printf("\n");
	}
			
}

void turn_angle(int arr[4][4]){
	int i, j;
	int brr[4][4];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			brr[i][j] = arr[3-j][i];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			arr[i][j] = brr[i][j];
}
void left_test(int arr[4][4]){
	int i, j;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 3 ; j++){
			arr[i][j] = arr[i][j + 1];
		}
	}
	for (i = 0 ; i < 4 ; i++)
		box[i][3] = 0;
}

void down_test(int arr[4][4]){
	int i, j;
	for (i = 3 ; i > 0 ; i--){
		for (j = 0 ; j < 4 ; j++){
			arr[i][j] = arr[i - 1][j];
		}
	}
	for (i = 0 ; i < 4 ; i++)
		box[0][i] = 0;
}

int is_wall(int arr[4][4]){
	int i;
	for (i = 0 ; i < 4 ; i++)
		if (arr[i][0] == 1)
			break;
	return (i == 4);
}

int is_down(int arr[4][4]){
	int i;
	for (i = 0 ; i < 4 ; i++){
		if (arr[3][i] == 1)
			break;
	}
	return (i == 4);
}

void fix(int arr[4][4]){
	while (is_wall(arr))
		left_test(arr);
	while (is_down(arr))
		down_test(arr);
}

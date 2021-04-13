#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

char map[20][8]; //map[y][x]
int start_x = 0, start_y = 3;
char blocks = '#';
void re_fresh();
void blocks_check();
void down_fill(int);
void blocks_fall();
void blocks_move(char,int,int);
int main(){
	char c;
	int i, j, t, game_over = 0;
	for (i = 0 ; i < 20 ; i++)
		for (j = 0;  j < 8 ; j++)
			map[i][j] = ' ';
	re_fresh();
	while (game_over != 1){
		t = 20000;
		while (t > 0){
			if (kbhit()){
				c = getch();
				///////
				re_fresh();
			}
			t--;
		}
	}
}

void re_fresh(){
	system("CLS");
	int i, j;
	for (i = 0 ; i < 20 ; i++){
		for (j = 0 ; j < 8 ; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void blocks_check(){
	int i, j, count;
	for (i = 0 ; i < 20 ; i++){
		for (j = 0 ; j < 8 ; j++){
			if (map[i][j] == ' ')
				break;
		}
		if (j == 8){
			down_fill(i);
		}
	}
}

void down_fill(int pai){
	int i, j;
	for (i = pai ; i > 0 ; i--){
		for (j = 0 ; j < 8 ; j++){
			map[i][j] = map[i - 1][j];
		}
	}
}

void blocks_move(char way,int x,int y){
	switch (way){
		case 'A':
		case 'a':
			if (map[y][x - 1] == ' '){
				map[y][x - 1] = map[y][x];
				map[y][x] = ' ';
			}
			break;
		case 'D':
		case 'd':
			if (map[y][x + 1] == ' '){
				map[y][x + 1] = map[y][x];
				map[y][x] = ' ';
			}
		case 'S':
		case 's':
			if (map[y + 1][x] == ' '){
				map[y + 1][x] = map[y][x];
				map[y][x] = ' ';
			}
	}
}

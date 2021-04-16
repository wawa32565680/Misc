#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

char map[20][20]; //map[y][x]
const int start_x = 4, start_y = 0, max_x = 10, max_y = 20;
int con_x, con_y, is_stop;
char blocks = '#';

// 0:方形 1:長條 2:L型 3:ㄣ 型 4:T型 

int box[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{1,1,0,0},
	{1,1,0,0}
};

int long_type[4][4] = {
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

int l_type[4][4] = {
	
};

char to_block(int);//整數陣列轉圖形 
void re_fresh();//刷新畫面 
void blocks_check(); //判斷橫行是否填滿消除 
void down_fill(int); //消除後向下填滿  
void blocks_fall(); //方塊自然落下 
void blocks_move(char); //移動方塊 
void blocks_type(int);//繪製不同圖型 
void rotate(int[4][4]);
void ending();

int main(){
	srand(time(0));
	char c;
	int i, j, t, game_over = 0, type_id;
	for (i = 0 ; i < max_y ; i++)
		for (j = 0;  j < max_x ; j++)
			map[i][j] = ' ';
	while (!game_over){
		if (map[start_y][start_x] != ' ')
			break;
		//type_id = rand() % 5;
		con_x = start_x;
		con_y = start_y + 4;
		//map[con_y][con_x] = blocks;
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 4 ; j++){
				map[con_y - i][con_x + j] = to_block(long_type[i][j]);
			}
		}
		re_fresh();
		t = 10000;
		is_stop = 0;
		while (!is_stop && !game_over){
			t = 20000;
			while (t > 0){
				if (kbhit()){
					c = getch();
					if (c == 'Q' || c == 'q'){
						game_over = 1;
						break;
					}
					blocks_move(c);
					re_fresh();
					
				}
				
				t--;
			}
			blocks_fall();
		}
		blocks_check();
	}
	ending();
}

void re_fresh(){
	system("CLS");
	int i, j;
	for (i = 0 ; i < max_y ; i++){
		for (j = 0 ; j < max_x ; j++){
			printf("%c", map[i][j]);
		}
		printf("|");
		printf("\n");
	}
	for (i = 0 ; i < max_x ; i++)
		printf("=");
	printf("=\n");
}

void blocks_check(){
	int i, j;
	for (i = 0 ; i < max_y ; i++){
		for (j = 0 ; j < max_x ; j++){
			if (map[i][j] == ' ')
				break;
		}
		if (j == max_x){
			down_fill(i);
		}
	}
}

void down_fill(int pai){
	int i, j;
	for (i = pai ; i > 0 ; i--){
		for (j = 0 ; j < max_x ; j++){
			map[i][j] = map[i - 1][j];
		}
	}
}

void blocks_move(char way){
	int i, j;
	switch (way){
		case 'A':
		case 'a':
			/*
			if (map[con_y][con_x - 1] == ' ' && con_x > 0){
				map[con_y][con_x - 1] = map[con_y][con_x];
				map[con_y][con_x] = ' ';
				con_x--;
			}
			*/
			if (map[con_y][con_x - 1] == ' ' && con_x > 0){
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i][con_x + j] = ' ';
					}
				}
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i][con_x + j - 1] = to_block(long_type[i][j]);
					}
				}
				con_x--;
			}
			break;
		case 'D':
		case 'd':
			/*
			if (map[con_y][con_x + 1] == ' ' && con_x < max_x - 1){
				map[con_y][con_x + 1] = map[con_y][con_x];
				map[con_y][con_x] = ' ';
				con_x++;
			}
			*/
			if (map[con_y][con_x + 1] == ' ' && con_x < max_x - 1){
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i][con_x + j] = ' ';
					}
				}
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i][con_x + j + 1] = to_block(long_type[i][j]);
					}
				}
				con_x++;
			}
			break;
		case 'S':
		case 's':
			/*
			if (map[con_y + 1][con_x] == ' ' && con_y < max_y){
				map[con_y + 1][con_x] = map[con_y][con_x];
				map[con_y][con_x] = ' ';
				con_y++;
			}
			*/
			if (map[con_y + 1][con_x] == ' ' && con_y < max_y){
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i][con_x + j] = ' ';
					}
				}
				for (i = 0 ; i < 4 ; i++){
					for (j = 0 ; j < 4 ; j++){
						if (long_type[i][j] == 1)
							map[con_y - i + 1][con_x + j] = to_block(long_type[i][j]);
					}
				}
				con_y++;
			}
			break;
		case 'W':
		case 'w':
			
			break;
	}
}
//方塊自然落下 
void blocks_fall(){
	int i, j;
	if (map[con_y + 1][con_x] == ' '){
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 4 ; j++){
				if (long_type[i][j] == 1){
					map[con_y - i][con_x + j] = ' ';
				}
			}
		}
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 4 ; j++){
				if (long_type[i][j] == 1)
					map[con_y - i + 1][con_x + j] = to_block(long_type[i][j]);
			}
		}
		con_y++;
	}
	else
		is_stop = 1;
	/*
	if (map[con_y + 1][con_x] == ' '){
		map[con_y + 1][con_x] = map[con_y][con_x];
		map[con_y][con_x] = ' ';
		con_y++;
		
	}
	else
		is_stop = 1;
	re_fresh();
	*/
	re_fresh();
}

void ending(){
	system("CLS");
	printf("~~GAME OVER~~\n");
}

void blocks_type(int type){
	int i, j;
	switch (type){
		case 0:{
			
			break;
		}
	}
}

void rotete(int arr[4][4]){
	int i, j;
	int brr[4][4];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			brr[i][j] = arr[3-j][i];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			arr[i][j] = brr[i][j];
}

char to_block(int x){
	if (x)
		printf("%c", blocks);
	else
		printf(" ");
}

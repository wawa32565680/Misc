#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

char map[20][20]; //map[y][x]
const int start_x = 4, start_y = 3, max_x = 10, max_y = 20;
int con_x, con_y, is_stop, type_id[2], first = 0;
char blocks = 'O';
int line = 0, score = 0;
// 0:方形 1:長條 2:L型 3:ㄣ 型 4:T型 

const int shape[7][4][4] = {
	{
		{1,1,0,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0}
	},
	{
		{1,1,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{0,0,0,0}
	},
	{
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{1,0,0,0},
		{1,1,0,0},
		{1,0,0,0},
		{0,0,0,0}
	},
	{
		{1,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{1,1,0,0},
		{0,1,1,0},
		{0,0,0,0},
		{0,0,0,0}
	}
};

int long_type[4][4];


int is_touch_down(); //判斷是否碰觸下方方塊 
int is_touch_wall(char); //判斷是否碰觸左右方塊 
int is_gameover();//判斷是否遊戲結束 
int is_draw_able(int);//判斷起始點是否能畫方塊 
char to_block(int); //整數陣列轉圖形 
void re_fresh(); //刷新畫面 
void blocks_check(); //判斷橫行是否填滿消除 
void down_fill(int); //消除後向下填滿  
void blocks_fall(); //方塊自然落下 
void blocks_move(char); //移動方塊 
void new_blocks_move(char); // 新版移動方塊 
void move_set(char); //移動方塊(函數) 
void rotate(int[4][4]);//轉向
void fix_place();//轉向後校正位置 
void set_blocks(int);//設定顯示方塊 
void clear_old_blocks();//清除舊方塊 
void draw_blocks(int,int);
void ending();

//======== 轉向輔助 
int is_wall(int[4][4]);//是否貼齊左
int is_top(int[4][4]); 
int is_rotate_able(); 
//======== 轉向輔助

int main(){
	srand(time(0));
	char c;
	int i, j, t, game_over = 0;
	for (i = 0 ; i < max_y ; i++)
		for (j = 0;  j < max_x ; j++)
			map[i][j] = ' ';
	while (!game_over){
		if (is_gameover())
			break;
		if (!first){
			type_id[0] = rand() % 7;
			type_id[1] = rand() % 7;
			first = !first;
		}
		else{
			type_id[0] = type_id[1];
			type_id[1] = rand() % 7;
		}
		con_y = start_y;
		if (!is_draw_able(start_x)){
			for (i = 0 ; i < max_x ; i++){
				if (is_draw_able(i)){
					con_x = i;
					break;
				}
			}
			if (i == max_x)
				break;
		}
		else
			con_x = start_x;
		
		set_blocks(type_id[0]);
		draw_blocks(0,0);
		re_fresh();
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
					new_blocks_move(c);
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

int is_gameover(){
	int i, j;
	for (i = 0 ; i < max_x ; i++){
		if (map[0][i] != ' ')
			return 1;
	}
	return 0;
}

int is_draw_able(int x){
	int i, j;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (long_type[i][j] == 1 && map[3 - i][j + x] != ' ')
				return 0;
		}
	}
	return 1;
}

void re_fresh(){
	system("CLS");
	int i, j, k, z = 0;
	for (i = 0 ; i < max_y ; i++){
		for (j = 0 ; j < max_x ; j++){
			printf("%c", map[i][j]);
		}
		printf("|");
		if (i == 1)
			printf("     下一個方塊是:");
		else if (i == 2 || i == 3 || i == 4 || i == 5){
			printf("     ");
			for (k = 0 ; k < 4 ; k++){
				to_block(shape[type_id[1]][3 - z][k]);
			}
			z++;
		}
		else if (i == 8)
			printf("     你以削除%d條線", line);
		else if (i == 9)
			printf("     得分:%d分", score);
		else if (i == 11)
			printf("     W:掉落至最底部");
		else if (i == 12)
			printf("     A:左移  S:下移  D:右移");
		else if (i == 13)
			printf("     空白鍵:旋轉");
		printf("\n");
	}
	for (i = 0 ; i < max_x ; i++)
		printf("=");
	printf("=\n");
}

void blocks_check(){
	int i, j, ct = 0;
	for (i = 0 ; i < max_y ; i++){
		for (j = 0 ; j < max_x ; j++){
			if (map[i][j] == ' ')
				break;
		}
		if (j == max_x){
			down_fill(i);
			line++;
			ct++;
		}
	}
	switch (ct){
		case 1:{
			score += 40;
			break;
		}
		case 2:{
			score += 100;
			break;
		}
		case 3:{
			score += 300;
			break;
		}
		case 4:{
			score += 1200;
			break;
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
//控制移動方塊
void new_blocks_move(char way){
	switch (way){
		case 'A':
		case 'a':
			if (is_touch_wall('l') && con_x > 0)
				move_set('l');
				break;
		case 'D':
		case 'd':
			if (is_touch_wall('r') && con_x < max_x - 1)
				move_set('r');
				break;
		case 'S':
		case 's':
			if (is_touch_down() && con_y < max_y)
				move_set('s');
				break;
		case ' ':
			clear_old_blocks();
			if (is_rotate_able()){
				rotate(long_type);
				fix_place(long_type);
				draw_blocks(0,0);
				re_fresh();
			}
			else{
				draw_blocks(0,0);
				re_fresh();
			}
			break;
		case 'W':
		case 'w':
			while(!is_stop)
				blocks_fall();
			re_fresh();
			break;
	}
}
//方塊自然落下 
void blocks_fall(){
	int i, j;
	//if (map[con_y + 1][con_x] == ' '){
	if (is_touch_down() && con_y < max_y){
		clear_old_blocks();
		draw_blocks(1,0);
		con_y++;
	}
	else
		is_stop = 1;
	re_fresh();
}

void ending(){
	system("CLS");
	printf("~~GAME OVER~~\n你總共消除了%d條線\n總分為%d分", line, score);
}


//轉向 
void rotate(int arr[4][4]){
	int i, j;
	int brr[4][4];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			brr[i][j] = arr[3-j][i];
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			arr[i][j] = brr[i][j];
}
//轉向後校正位置 
void fix_place(){
	int i, j;
	while (is_wall(long_type)){	
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 3 ; j++){
				long_type[i][j] = long_type[i][j + 1];
			}
		}
		for (i = 0 ; i < 4 ; i++)
			long_type[i][3] = 0;
	}
	/*
	while (is_top(long_type)){
		for (i = 0 ; i < 3 ; i++){
			for (j = 0 ; j < 4 ; j++){
				long_type[i][j] = long_type[i + 1][j];
			}
		}
		for (i = 0 ; i < 4 ; i++)
			long_type[3][i] = 0;
	}
	*/
}
//是否能夠旋轉 
int is_rotate_able(){
	int i, j;
	int arr[4][4];
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			arr[i][j] = long_type[3-j][i];
		}
	}
	//=====================
	while (is_wall(arr)){
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 3 ; j++){
				arr[i][j] = arr[i][j + 1];
			}
		}
		for (i = 0 ; i < 4 ; i++)
			arr[i][3] = 0;
	}
	//========================
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (arr[i][j] == 1 && map[con_y - i][con_x + j] != ' ')
				return 0;
		}
	}
	return 1;
}

int is_wall(int arr[4][4]){
	int i;
	for (i = 0 ; i < 4 ; i++)
		if (arr[i][0] == 1)
			break;
	return (i == 4);
}

int is_top(int arr[4][4]){
	int i;
	for (i = 0 ; i < 4 ; i++){
		if (arr[0][i] == 1)
			return 0;
	return 1;
	}
}

//是否碰觸下方方塊 
int is_touch_down(){
	int i, j;
	int is_compare[4] = {0,0,0,0};
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (is_compare[j])
				continue;
			if (long_type[i][j] == 1){
				if (map[con_y - i + 1][con_x + j] != ' ')
					return 0;
				else
					is_compare[j] = 1;
			}
		}
	}
	return 1;
}
//是否碰觸左右方塊 
int is_touch_wall(char way){
	int i, j, x;
	int is_compare[4] = {0,0,0,0};
	if (way == 'L' || way == 'l')
		x = -1;
	else if (way == 'R' || way == 'r')
		x = 1;
		
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (long_type[i][j] == 1 && long_type[i][j + x] == 0){
				if (map[con_y - i][con_x + j + x] != ' ')
					return 0;
			}
		}
	}
	return 1;
	
	/*
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (is_compare[j])
				continue;
			if (long_type[i][j] == 1){
				if (map[con_y][con_x + x] != ' ')
					return 0;
				else
					is_compare[j] = 1;
			}
		}
	}
	return 1;
	*/
}
//移動函數 
void move_set(char way){
	int x, i, j;
	if (way == 'L' || way == 'l' || way == 'R' || way == 'r'){
		if (way == 'L' || way == 'l')
			x = -1;
		else
			x = 1;
		clear_old_blocks();
		/*
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 4 ; j++){
				if (long_type[i][j] == 1)
					map[con_y - i][con_x + j + x] = to_block(long_type[i][j]);
			}
		}
		*/
		draw_blocks(0,x);
			con_x = con_x + x;
	}
	else if (way == 'S' || way == 's'){
		clear_old_blocks();
		/*
		for (i = 0 ; i < 4 ; i++){
			for (j = 0 ; j < 4 ; j++){
				if (long_type[i][j] == 1)
					map[con_y - i + 1][con_x + j] = to_block(long_type[i][j]);
			}
		}
		*/
		draw_blocks(1,0);
		con_y++;
	}
}
//設定方塊種類 
void set_blocks(int type){
	int i, j;
	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			long_type[i][j] = shape[type][i][j];
}
//清除舊方塊 
void clear_old_blocks(){
	int i, j;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (long_type[i][j] == 1)
				map[con_y - i][con_x + j] = ' ';
		}
	}
}
//畫方塊 
void draw_blocks(int y,int x){
	int i, j;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			if (long_type[i][j] == 1){
				map[con_y - i + y][con_x + j + x] = to_block(long_type[i][j]);
			}
		}
	}
}

//陣列中整數轉字元 
char to_block(int x){
	if (x)
		printf("%c", blocks);
	else
		printf(" ");
}

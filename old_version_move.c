//控制移動方塊(捨棄的舊版) 
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
			if (is_touch_wall('l') && con_x > 0){
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
			//if (map[con_y][con_x + 1] == ' ' && con_x < max_x - 1){
			if (is_touch_wall('r') && con_x < max_x - 1){
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
			//if (map[con_y + 1][con_x] == ' ' && con_y < max_y){
			if (is_touch_down() && con_y < max_y){
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
		case ' ':
			
			break;
	}
	
}

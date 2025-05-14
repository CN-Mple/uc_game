#include "uc_2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char vram_point = 0;
char memory_window[16 + (6 + 1) * 4 * 4];

volatile struct Game_vram screen = {
	.title_text = {
		"hello world"
	},
	.tile_map = {
		{ 0, 0,  0, 0,},
		{ 0, 0,  2, 0,},
		{ 0, 0,  0, 0,},
		{ 4, 0,  0, 0,},
	}
};
volatile struct Game_input pad __attribute__((used));

void rest_game(void);

void handle_up(void *arg);
void handle_down(void *arg);
void handle_left(void *arg);
void handle_right(void *arg);
void handle_a(void *arg);
void handle_b(void *arg);
void handle_menu(void *arg);

void place_new_tile(void);
void updata_display(void);

void game_loop_2048(void)
{
	enum Event {
		NO_PUSH = 0,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		A,
		B,
		MENU,		
	}e;
	rest_game();
	while(1) {
		if(pad.UP) {
			pad.UP = 0;
			e = UP;
		} else if(pad.DOWN) {
			pad.DOWN = 0;
			e = DOWN;
		} else if(pad.LEFT) {
			pad.LEFT = 0;
			e = LEFT;
		} else if(pad.RIGHT) {
			pad.RIGHT = 0;
			e = RIGHT;
		} else if(pad.A) {
			pad.A = 0;
			e = A;
		} else if(pad.B) {
			pad.B = 0;
			e = B;
		} else if(pad.MENU) {
			pad.MENU = 0;
			e = MENU;
		} else {
			e = NO_PUSH;
		}
		
		switch (e) {
		case NO_PUSH:
			
		break;
		case UP:
			handle_up(0);
		break;
		case DOWN:
			handle_down(0);
		break;
		case LEFT:
			handle_left(0);
		break;
		case RIGHT:
			handle_right(0);
		break;
		case A:
			
		break;
		case B:
			
		break;
		case MENU:
			rest_game();
		break;
		default:
			
		break;
		}
		if (UP == e || DOWN == e || LEFT == e || RIGHT == e) {
			place_new_tile();
		}
		updata_display();
	}
}

void handle_up(void *arg)
{
	(void)arg;
	for (int x = 0; x < 4; ++x) {
		for (int i = 0; i < (4 - 1); ++i) {
			int point1 = 0;
			int point2 = 0;
			for (int y = 0; y < 4; ++y) {
				if (screen.tile_map[y][x] != 0) {
					screen.tile_map[point1++][x] = screen.tile_map[y][x];
				}
			}
			for (int y = point1; y < 4; ++y) {
				screen.tile_map[y][x] = 0;
			}
			
			point1 = 0;
			point2 = 1;
			while (point1 < 3 && point2 < 3) {
				if(screen.tile_map[point1][x] == 0)
					break;
				if (screen.tile_map[point1][x] == screen.tile_map[point2][x]) {
					screen.tile_map[point1][x] <<= 1;
					screen.tile_map[point2][x] = 0;
				} else {
					unsigned int tmp = screen.tile_map[point2][x];
					if (screen.tile_map[point1 + 1][x] == 0) {
						screen.tile_map[point2][x] = 0;
					}
					screen.tile_map[point1 + 1][x] = tmp;
					
					point1++;
				}
				point2++;
			}
		}
	}
}

void handle_down(void *arg)
{
	(void)arg;
	for (int x = 0; x < 4; ++x) {
		for (int i = 0; i < (4 - 1); ++i) {
			int point1 = 3;
			int point2 = 0;
			for (int y = 3; y >= 0; --y) {
				if (screen.tile_map[y][x] != 0) {
					screen.tile_map[point1--][x] = screen.tile_map[y][x];
				}
			}
			for (int y = point1; y >= 0; --y) {
				screen.tile_map[y][x] = 0;
			}
			
			point1 = 3;
			point2 = 2;
			while (point1 > 0 && point2 > 0) {
				if(screen.tile_map[point1][x] == 0)
					break;
				if (screen.tile_map[point1][x] == screen.tile_map[point2][x]) {
					screen.tile_map[point1][x] <<= 1;
					screen.tile_map[point2][x] = 0;
				} else {
					unsigned int tmp = screen.tile_map[point2][x];
					if (screen.tile_map[point1 - 1][x] == 0) {
						screen.tile_map[point2][x] = 0;
					}
					screen.tile_map[point1 - 1][x] = tmp;
					point1--;
				}
				point2--;
			}
		}
	}
}

void handle_left(void *arg)
{
	(void)arg;
	for (int y = 0; y < 4; ++y) {
		for (int i = 0; i < (4 - 1); ++i) {
			int point1 = 0;
			int point2 = 0;
			for (int x = 0; x < 4; ++x) {
				if (screen.tile_map[y][x] != 0) {
					screen.tile_map[y][point1++] = screen.tile_map[y][x];
				}
			}
			for (int x = point1; x < 4; ++x) {
				screen.tile_map[y][x] = 0;
			}
			
			point1 = 0;
			point2 = 1;
			while (point1 < 3 && point2 < 3) {
				if(screen.tile_map[y][point1] == 0)
					break;
				if (screen.tile_map[y][point1] == screen.tile_map[y][point2]) {
					screen.tile_map[y][point1] <<= 1;
					screen.tile_map[y][point2] = 0;
				} else {
					unsigned int tmp = screen.tile_map[y][point2];
					if (screen.tile_map[y][point1 + 1] == 0) {
						screen.tile_map[y][point2] = 0;
					}
					screen.tile_map[y][point1 + 1] = tmp;
					point1++;
				}
				point2++;
			}
		}
	}
}

void handle_right(void *arg)
{
	(void)arg;
	for (int y = 0; y < 4; ++y) {
		for (int i = 0; i < (4 - 1); ++i) {
			int point1 = 3;
			int point2 = 0;
			for (int x = 3; x >= 0; --x) {
				if (screen.tile_map[y][x] != 0) {
					screen.tile_map[y][point1--] = screen.tile_map[y][x];
				}
			}
			for (int x = point1; x >= 0; --x) {
				screen.tile_map[y][x] = 0;
			}
			
			point1 = 3;
			point2 = 2;
			while (point1 > 0 && point2 > 0) {
				if(screen.tile_map[y][point1] == 0)
					break;
				if (screen.tile_map[y][point1] == screen.tile_map[y][point2]) {
					screen.tile_map[y][point1] <<= 1;
					screen.tile_map[y][point2] = 0;
				} else {
					unsigned int tmp = screen.tile_map[y][point2];
					if (screen.tile_map[y][point1 - 1] == 0) {
						screen.tile_map[y][point2] = 0;
					}
					screen.tile_map[y][point1 - 1] = tmp;
					point1--;
				}
				point2--;
			}
		}
	}
}

void handle_a(void *arg)
{
	(void)arg;
}

void handle_b(void *arg)
{
	(void)arg;
}

void handle_menu(void *arg)
{
	(void)arg;
}

void rest_game(void)
{
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			screen.tile_map[y][x] = 0;
		}
	}
	for (int i = 0; i < 2; ++i) {
		place_new_tile();
	}
}

void place_new_tile(void)
{
	unsigned char pos;
	do {
		pos = rand() % 50;
	}while(pos == 0);
	unsigned char zero_sum = 0;
	do {
		zero_sum = 0;
		for (int y = 0; y < 4; ++y) {
			for (int x = 0; x < 4; ++x) {
				if(screen.tile_map[y][x] == 0) {
					--pos;
					++zero_sum;
					if(0 == pos) {
						screen.tile_map[y][x] = (rand() % 2) ? 2 : 4;
						break;
					}
				}
			}
			if(0 == pos)
				break;
		}
		if (0 == zero_sum || 0 == pos)
			break;
	}while(1);
}

void updata_display(void)
{
	char buffer[7];
	sprintf((char*)&memory_window[vram_point], "%s", (char*)&screen.title_text[0]);	
	vram_point += 6 * 4;
	
	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {
			sprintf(buffer, " %-4d ", (int)screen.tile_map[y][x]);
			memcpy(&memory_window[vram_point], buffer, 6);
			vram_point += 6;
		}
	}
	vram_point = 0;
}
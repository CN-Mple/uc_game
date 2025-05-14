

#ifndef __UC_2048_H
#define __UC_2048_H

struct Game_vram {
	char title_text[16];
	unsigned int tile_map[4][4];
};

struct Game_input {
	unsigned int UP    :1;
	unsigned int DOWN  :1;
	unsigned int LEFT  :1;
	unsigned int RIGHT :1;
	unsigned int A     :1;
	unsigned int B     :1;
	unsigned int MENU  :1;
};

void game_loop_2048(void);

#endif /* __UC_2048_H */

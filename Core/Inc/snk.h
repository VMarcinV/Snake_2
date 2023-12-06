#include "lcd.h"
#include <stdlib.h>
#include <time.h>
#include <stm32l4xx_hal.h>


#define PLACE_WIDTH	20
#define PLACE_HEIGHT	16

void square(int x_pos ,int y_pos, uint16_t color);
void apple();
void snk_start_pos();
void snk_draw();
void snkStart();
void snk_move(int dir);
void snk_eat();
void game_over();
void game_over_mess();
int getScore();

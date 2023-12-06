#include "snk.h"
#include "hagl.h"
#include "font6x9.h"
#include "rgb565.h"

static int snk_pos[2][104];
static int snk_leng=4;

static int appleX=0;
static int appleY=0;

void square(int x_pos ,int y_pos, uint16_t color)
{

	for (int y = y_pos*8; y < (y_pos*8)+8; y++) {
		      for (int x = x_pos*8; x < (x_pos*8)+8; x++) {
		        lcd_put_pixel(x, y,color);
		      }
		    }

}


void apple()
{

	appleX=((HAL_GetTick()+3)%(PLACE_WIDTH-3))+1;
	appleY=((HAL_GetTick()+3)%(PLACE_HEIGHT-3))+1;

	for(int i=0;i<=snk_leng;i++)
	{
		if(snk_pos[0][i]==appleX && snk_pos[1][i]==appleY)
		{
			appleX=((HAL_GetTick()+3)%(PLACE_WIDTH-3))+1;
			appleY=((HAL_GetTick()+3)%(PLACE_HEIGHT-3))+1;
			i=-1;
		}
	}
	square(appleX, appleY, RED);
	lcd_copy();
}



void snk_start_pos()
{
	for(int le=0;le<snk_leng-1;le++)
	{
		snk_pos[0][le]=4-le;
		snk_pos[1][le]=8;
	}
}
void snk_draw()
{
	for (int len = 0; len<=snk_leng; len++) {
		square(snk_pos[0][len],snk_pos[1][len] ,GREEN );
	}
	lcd_copy();

}


void snkStart()
{
	lcd_init();

		for(int x=0;x<PLACE_WIDTH;x++)
		{
			square(x, 0, BLACK);
			square(x, 15, BLACK);
		}
		for(int y=1;y<PLACE_HEIGHT-1;y++)
		{
			square(0,y,BLACK);
			square(19,y,BLACK);
		}
		for(int x=1;x<PLACE_WIDTH-1;x++)
		{
			for(int y=1;y<PLACE_HEIGHT-1;y++)
			{
				square(x,y,WHITE);
			}
		}

	lcd_copy();
	snk_start_pos();
	snk_draw();
	apple();

}
void snk_move(int dir)
{

	switch(dir)
	{
	case 1:

		square(snk_pos[0][snk_leng-1], snk_pos[1][snk_leng-1], WHITE);

		for(int p=snk_leng-1;p>0;p--)
		{
			snk_pos[0][p]=snk_pos[0][p-1];
			snk_pos[1][p]=snk_pos[1][p-1];
		}
		snk_pos[1][0]--;

	break;

	case 2:

			square(snk_pos[0][snk_leng-1], snk_pos[1][snk_leng-1], WHITE);

			for(int p=snk_leng-1;p>0;p--)
			{
				snk_pos[0][p]=snk_pos[0][p-1];
				snk_pos[1][p]=snk_pos[1][p-1];
			}
				snk_pos[0][0]++;
	break;

	case 3:

			square(snk_pos[0][snk_leng-1], snk_pos[1][snk_leng-1], WHITE);

			for(int p=snk_leng-1;p>0;p--)
			{
				snk_pos[0][p]=snk_pos[0][p-1];
				snk_pos[1][p]=snk_pos[1][p-1];
			}
			snk_pos[1][0]++;
	break;

	case 4:

			square(snk_pos[0][snk_leng-1], snk_pos[1][snk_leng-1], WHITE);
			for(int p=snk_leng-1;p>0;p--)
			{
				snk_pos[0][p]=snk_pos[0][p-1];
				snk_pos[1][p]=snk_pos[1][p-1];
			}
			snk_pos[0][0]--;
	break;
	}
}
void snk_eat()
{
	if(snk_pos[0][0]==appleX && snk_pos[1][0]==appleY)
	{
		snk_leng++;
		apple();
	}
}
void game_over_mess()
{
	hagl_put_text(L"GAME OVER", 45, 50, YELLOW, font6x9);
	lcd_copy();
}
void game_over()
{
	if(snk_pos[0][0]<1 || snk_pos[0][0]>PLACE_WIDTH-2)
	{
		game_over_mess();
		while (1)
			{
			}
	}
	if(snk_pos[1][0]<1 || snk_pos[1][0]>PLACE_HEIGHT-2)
	{
		game_over_mess();
		while (1)
			{
			}
	}

	for  (int a=1;a<snk_leng;a++) {
		if(snk_pos[0][a]==snk_pos[0][0] && snk_pos[1][a]==snk_pos[1][0])
		{
			game_over_mess();
			while (1)
				{
				}
		}
	}

}
int getScore()
{
	return snk_leng-4;
}

#include "ADC.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h"
#include "DAC.h"
#include "Timer0.h"
#include "movement.h"
#include "Globals.h"
#include "Images.h"
#include "Random.h"
#include "Sound.h"

void bullet_movement(void);
void alien_bullets(void);

struct shipBullet {
	uint32_t x;
	uint32_t y;
};
struct shipBullet bullet_l[1]={
	{0,0}
};

struct alienBullet {
	uint32_t x;
	uint32_t y;
	uint32_t loaded;
};
struct alienBullet bullet_t[6]={
	{52,70,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
	{0,0,0},
};
const unsigned short bullets[]={
 0x0000, 0x079f, 0x079f, 0x079f, 0x079f, 0x079f, 0x079f, 0x079f, 0x079f,0x0000
};

struct invaders{
	uint32_t x;
	uint32_t y;
	uint8_t dead;
	const unsigned short *pic;
};

typedef struct invaders invade_s;

invade_s matrix [36]={
{0,9,0,SmallEnemy30pointA},{20,9,0,SmallEnemy30pointA},{40,9,0,SmallEnemy30pointA},{60,9,0,SmallEnemy30pointA},{80,9,0,SmallEnemy30pointA},{100,9,0,SmallEnemy30pointA},
{0,20,0,SmallEnemy30pointB},{20,20,0,SmallEnemy30pointB},{40,20,0,SmallEnemy30pointB},{60,20,0,SmallEnemy30pointB},{80,20,0,SmallEnemy30pointB},{100,20,0,SmallEnemy30pointB},
{0,31,0,SmallEnemy20pointA},{20,31,0,SmallEnemy20pointA},{40,31,0,SmallEnemy20pointA},{60,31,0,SmallEnemy20pointA},{80,31,0,SmallEnemy20pointA},{100,31,0,SmallEnemy20pointA},
{0,42,0,SmallEnemy20pointB},{20,42,0,SmallEnemy20pointB},{40,42,0,SmallEnemy20pointB},{60,42,0,SmallEnemy20pointB},{80,42,0,SmallEnemy20pointB},{100,42,0,SmallEnemy20pointB},
{0,53,0,SmallEnemy10pointA},{20,53,0,SmallEnemy10pointA},{40,53,0,SmallEnemy10pointA},{60,53,0,SmallEnemy10pointA},{80,53,0,SmallEnemy10pointA},{100,53,0,SmallEnemy10pointA},
{0,64,0,SmallEnemy10pointB},{20,64,0,SmallEnemy10pointB},{40,64,0,SmallEnemy10pointB},{60,64,0,SmallEnemy10pointB},{80,64,0,SmallEnemy10pointB},{100,64,0,SmallEnemy10pointB},
};

void generateShip(void){
	ST7735_DrawBitmap(52, 159, PlayerShip0, 18,8); // player ship middle bottom
	ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
}

void generateBullet(int x, int y){
	//ST7735_DrawPixel(x+8, y-8, 0xFFFF);
	bullet_l[0].x = x+8;
	bullet_l[0].y = y-8;
}

void generateBunkers(void){
	ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
	ST7735_DrawBitmap(0, 151, Bunker0, 18,5);
	ST7735_DrawBitmap(91, 151, Bunker0, 18,5);
}

void generateAliens(void){
  ST7735_DrawBitmap(0, 9, SmallEnemy30pointA, 16,10);
	ST7735_DrawBitmap(20, 9, SmallEnemy30pointA, 16,10);
	ST7735_DrawBitmap(40, 9, SmallEnemy30pointA, 16,10);
	ST7735_DrawBitmap(60, 9, SmallEnemy30pointA, 16,10);
	ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);
	ST7735_DrawBitmap(100, 9, SmallEnemy30pointA, 16,10);
  
	ST7735_DrawBitmap(0,20, SmallEnemy30pointB, 16,10);
	ST7735_DrawBitmap(20,20, SmallEnemy30pointB, 16,10);
	ST7735_DrawBitmap(40,20, SmallEnemy30pointB, 16,10);
	ST7735_DrawBitmap(60,20, SmallEnemy30pointB, 16,10);
	ST7735_DrawBitmap(80,20, SmallEnemy30pointB, 16,10);
	ST7735_DrawBitmap(100,20, SmallEnemy30pointB, 16,10);

	
  ST7735_DrawBitmap(0, 31, SmallEnemy20pointA, 16,10);
	ST7735_DrawBitmap(20, 31, SmallEnemy20pointA, 16,10);
	ST7735_DrawBitmap(40, 31, SmallEnemy20pointA, 16,10);
	ST7735_DrawBitmap(60, 31, SmallEnemy20pointA, 16,10);
	ST7735_DrawBitmap(80, 31, SmallEnemy20pointA, 16,10);
	ST7735_DrawBitmap(100,31, SmallEnemy20pointA, 16,10);
  
	ST7735_DrawBitmap(0, 42, SmallEnemy20pointB, 16,10);
	ST7735_DrawBitmap(20, 42, SmallEnemy20pointB, 16,10);
	ST7735_DrawBitmap(40, 42, SmallEnemy20pointB, 16,10);
	ST7735_DrawBitmap(60, 42, SmallEnemy20pointB, 16,10);
	ST7735_DrawBitmap(80, 42, SmallEnemy20pointB, 16,10);
	ST7735_DrawBitmap(100, 42, SmallEnemy20pointB, 16,10);
	
  ST7735_DrawBitmap(0, 53, SmallEnemy10pointA, 16,10);
	ST7735_DrawBitmap(20, 53, SmallEnemy10pointA, 16,10);
	ST7735_DrawBitmap(40, 53, SmallEnemy10pointA, 16,10);
	ST7735_DrawBitmap(60, 53, SmallEnemy10pointA, 16,10);
	ST7735_DrawBitmap(80, 53, SmallEnemy10pointA, 16,10);
	ST7735_DrawBitmap(100, 53, SmallEnemy10pointA, 16,10);
	
  ST7735_DrawBitmap(0, 64, SmallEnemy10pointB, 16,10);
	ST7735_DrawBitmap(20, 64, SmallEnemy10pointB, 16,10);
	ST7735_DrawBitmap(40, 64, SmallEnemy10pointB, 16,10);
	ST7735_DrawBitmap(60, 64, SmallEnemy10pointB, 16,10);
	ST7735_DrawBitmap(80, 64, SmallEnemy10pointB, 16,10);
	ST7735_DrawBitmap(100, 64, SmallEnemy10pointB, 16,10);
}





void generateShip(void);
void alien_movement(void);
void generateAliens(void);
void rightShift(void);

void startEngine(void){
	generateShip();
	generateAliens();
	generateBunkers();
	while(1){
		alien_movement();	
	}
}

void alien_movement (void){
	uint32_t flag=0;
	//right shift
	shipMovement();
	while(matrix[35].x<109){
		for(int i=35;i>=0;i--){
			for(int j=35;j>=0;j--){
			if(((bullet_l[0].x<matrix[j].x+16)&&bullet_l[0].x>matrix[j].x)&&((bullet_l[0].y>matrix[j].y-10)&&bullet_l[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
					shotFired_ticks = 0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					
					if(flag==0){
						//Sound_Init();
						//Sound_Killed();
						ST7735_FillRect(bullet_l[0].x,bullet_l[0].y,3,11,0x0000);
						NVIC_ST_CTRL_R =0;
					}
				}
			}
			
				matrix[i].x+=1;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, matrix[i].pic, 16,10);
				}
				alien_bullets();
				shipMovement();
		
			}
		}
	

//drop down
	shipMovement();
	for(int i=35;i>=0;i--){
			for(int j=35;j>=0;j--){
			if(((bullet_l[0].x<matrix[j].x+16)&&bullet_l[0].x>matrix[j].x)&&((bullet_l[0].y>matrix[j].y-10)&&bullet_l[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
					shotFired_ticks = 0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					
					if(flag==0){
						//Sound_Init();
						//Sound_Killed();
						//shotFired_ticks = 0;
						ST7735_FillRect(bullet_l[0].x,bullet_l[0].y,3,11,0x0000);
						NVIC_ST_CTRL_R=0;
					}
			}
		}
				matrix[i].y+=5;
				if(matrix[i].y>=151){
					return; 
				}
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, matrix[i].pic, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
	
				shipMovement();
	
}
	


//	left shift
	shipMovement();
	while(matrix[0].x>0){

		for(int i=0;i<=35;i++){
			for(int j=0;j<=35;j++){
			if(((bullet_l[0].x<matrix[j].x+16)&&bullet_l[0].x>matrix[j].x)&&((bullet_l[0].y>matrix[j].y-10)&&bullet_l[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
					shotFired_ticks = 0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					if(flag==0){
						//Sound_Init();
						//Sound_Killed();
						//shotFired_ticks = 0;
						ST7735_FillRect(bullet_l[0].x,bullet_l[0].y,3,11,0x0000);
						NVIC_ST_CTRL_R=0;
					}
				}
			}
			
				matrix[i].x-=1;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, matrix[i].pic, 16,10);
				}
		
				alien_bullets();
				shipMovement();
			}
	}
	
	//drop down 
	shipMovement();
	for(int i=35;i>=0;i--){
			for(int j=35;j>=0;j--){
			if(((bullet_l[0].x<matrix[j].x+16)&&bullet_l[0].x>matrix[j].x)&&((bullet_l[0].y>matrix[j].y-10)&&bullet_l[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
					shotFired_ticks = 0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					
					if(flag==0){
						//Sound_Init();
						//Sound_Killed();
						//shotFired_ticks = 0;
						ST7735_FillRect(bullet_l[0].x,bullet_l[0].y,3,11,0x0000);
						NVIC_ST_CTRL_R=0;
					}
			}
		}
				matrix[i].y+=5;
				if(matrix[i].y>=151){
					return; 
				}
				if(matrix[i].dead==1){
					//ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, matrix[i].pic, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
	
				shipMovement();
	}
}



void moveBullet(void){
	bullet_l[0].y--;
	ST7735_FillRect(bullet_l[0].x,bullet_l[0].y,3,11,0xFFFF);
	ST7735_FillRect(bullet_l[0].x,bullet_l[0].y+1,3,11,0x0000);
}
		




void alien_bullets (void){
	uint32_t z=100;
	uint32_t w;
	uint32_t rando;
	rando=(Random()&0x000000FF);
	rando=(Random()&0x000000FF);
	if(rando<=35){
		z=rando;
	}
	Timer0_Init(bullet_movement, 80000);
	if(((matrix[z+6].dead==1)&&(z<=29))||(z<=35&&z>=30)){
		for(int j=0;j<6;j++){
			if(bullet_t[j].loaded==0){
				w=j;
				bullet_t[w].x = matrix[z].x+8;
				bullet_t[w].y = matrix[z].y+15;
				bullet_t[w].loaded=1;
				break;
			}
		}
		
	}
}

void bullet_movement (void){
	for(int j=0;j<6;j++){
		if(bullet_t[j].loaded==1){
			bullet_t[j].y+=5;
			ST7735_DrawBitmap(bullet_t[j].x, bullet_t[j].y, bullets, 1,10);
			ST7735_FillRect(bullet_t[j].x,bullet_t[j].y-15,1,5,0x0000);
			if(bullet_t[j].y>=159){
				bullet_t[j].loaded=0;
				ST7735_FillRect(bullet_t[j].x,148,1,15,0x0000);
			}
			if((bullet_t[j].y==151)&&(bullet_t[j].x<71||bullet_t[j].x>53)){
				ST7735_FillRect(bullet_t[j].x,bullet_t[j].y,1,15,0x0000);
			}
		
		}
	}
}
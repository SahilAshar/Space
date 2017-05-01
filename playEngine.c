#include "ADC.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h"
#include "movement.h"
#include "Globals.h"
#include "Images.h"

struct bullet {
	uint32_t x;
	uint32_t y;
};
struct bullet bullet_t[1]={
	{52,70}
};
const unsigned short bullets[]={
0x0000,0x0000,0x0000, 0x0000, 0x0000, 0x079f, 0x079f, 0x079f, 0x079f, 0x079f, 0x0000
};

struct invaders{
	uint32_t x;
	uint32_t y;
	uint8_t dead;
};

typedef struct invaders invade_s;

invade_s matrix [36]={
{0,9,0},{20,9,0},{40,9,0},{60,9,0},{80,9,0},{100,9,0},
{0,20,0},{20,20,0},{40,20,0},{60,20,0},{80,20,0},{100,20,0},
{0,31,0},{20,31,0},{40,31,0},{60,31,0},{80,31,0},{100,31,0},
{0,42,0},{20,42,0},{40,42,0},{60,42,0},{80,42,0},{100,42,0},
{0,53,0},{20,53,0},{40,53,0},{60,53,0},{80,53,0},{100,53,0},
{0,64,0},{20,64,0},{40,64,0},{60,64,0},{80,64,0},{100,64,0},
};

void generateShip(void){
	ST7735_DrawBitmap(52, 159, PlayerShip0, 18,8); // player ship middle bottom
	ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
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

void startEngine(void){
	generateShip();
	generateAliens();
	while(1){
		alien_movement();
	}
}

	

void alien_movement (void){
	uint32_t flag=0;
	//right shifting all aliens right until they reach screen end.
	shipMovement();
	while(matrix[35].x<109){
		for(int i=35;i>29;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=35;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					if(flag==0){
						ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
					}
				}
			}
			
				matrix[i].x+=1;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointB, 16,10);
				}
			
		}
		shipMovement();
		for(int i=29;i>23;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=29;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=29;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			matrix[i].x+=1;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointA, 16,10);
			}
		}
		shipMovement();
		for(int i=23;i>17;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=23;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=23;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			matrix[i].x+=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointB, 16,10);
			}
		}
		shipMovement();
		for(int i=17;i>11;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=17;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=17;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x+=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointA, 16,10);
			}
		}
		shipMovement();
		for(int i=11;i>5;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=11;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=11;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x+=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointB, 16,10);
			}
		}
		shipMovement();
		for(int i=5;i>=0;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=5;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=5;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x+=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointA, 16,10);
			}
		}
	}

	//drop down
	shipMovement();
	for(int i=35;i>29;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=35;j>29;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].y+=5;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
}
	shipMovement();
	for(int i=29;i>23;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=29;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=29;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
	}
	shipMovement();
	for(int i=23;i>17;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=23;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=23;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
	}
	shipMovement();
	for(int i=17;i>11;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=17;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=17;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
		}
		shipMovement();
		for(int i=11;i>5;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=11;j>5;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=11;k>5;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
		}
		shipMovement();
		for(int i=5;i>=0;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=5;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=5;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{	
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
		}
	
	


//	left shift
	while(matrix[30].x>0){
		shipMovement();
		for(int i=30;i<=35;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=30;j<35;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				if(matrix[j].dead==1){
					flag=1;
				}
				else{
					matrix[j].dead=1;
					flag=0;
				}
			}
		}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					if(flag==0){
						ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
					}
				}
			}
			
				matrix[i].x-=1;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointB, 16,10);
				}
			
		}
		shipMovement();
		for(int i=24;i<=29;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=24;j<=29;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			matrix[i].x-=1;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointA, 16,10);
			}
		}
		shipMovement();
		for(int i=18;i<=23;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=18;j<=23;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			matrix[i].x-=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointB, 16,10);
			}
		}
		shipMovement();
		for(int i=12;i<=17;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=12;j<=17;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x-=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointA, 16,10);
			}
		}
		shipMovement();
		for(int i=6;i<=11;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=5;j<11;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x-=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointB, 16,10);
			}
		}
		shipMovement();
		for(int i=0;i<=5;i++){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=0;j<=5;j++){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].x-=1;
				if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
			else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointA, 16,10);
			}
		}
	}
	shipMovement();
	for(int i=35;i>29;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=35;j>29;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=35;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
			
				matrix[i].y+=5;
				if(matrix[i].dead==1){
					ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
				}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
}
	shipMovement();
	for(int i=29;i>23;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=29;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=29;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy10pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
	}
	shipMovement();
	for(int i=23;i>17;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=23;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=23;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
	}
	shipMovement();
	for(int i=17;i>11;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=17;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=17;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy20pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
		}
		shipMovement();
		for(int i=11;i>5;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=11;j>5;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=11;k>5;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}
				else{
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointB, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
				}
		}
		shipMovement();
		for(int i=5;i>=0;i--){
//			bullet_t[0].y-=5;
			ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0xFFFF);
			for(int j=5;j>=0;j--){
			if(((bullet_t[0].x<matrix[j].x+16)&&bullet_t[0].x>matrix[j].x)&&((bullet_t[0].y>matrix[j].y-10)&&bullet_t[0].y<matrix[j].y)){
				matrix[j].dead=1;
				}
			}
			for(int k=5;k>=0;k--){
				if(matrix[k].dead==1){
					ST7735_DrawBitmap(matrix[k].x, matrix[k].y, black, 16,10);
					ST7735_FillRect(bullet_t[0].x,bullet_t[0].y,3,11,0x0000);
				}
			}
				matrix[i].y+=5;
			if(matrix[i].dead==1){
				ST7735_DrawBitmap(matrix[i].x, matrix[i].y, black, 16,10);
			}	
			else{	
			ST7735_DrawBitmap(matrix[i].x, matrix[i].y, SmallEnemy30pointA, 16,10);
				ST7735_FillRect(matrix[i].x, matrix[i].y-13, 16, 4, 0x0000);
			}
		}
}


#include "ADC.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "ST7735.h"
#include "Globals.h"
#include "Images.h"





void shipMovement(void){
	if((left_right<1500)&&(hori>0)){
		hori-=2;
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		Delay50ms(1);
	}
	else if(left_right>3500 /*&&(hori<109) */){
		hori+=2;
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		Delay50ms(1);
	}
	else if((up_down<3500)||(ADCvalue[0]>1500)){
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		Delay50ms(1);
	}
	
	if((up_down<1500)&&(verti<159)){
		verti++;
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		Delay50ms(1);
	}
	else if(up_down>3500&&(verti>8)){
		verti--;
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		ST7735_DrawBitmap(hori, verti+1, black, 16,1);
		Delay50ms(1);
	}
	else if((up_down<3500)||(left_right>1500)){
		ST7735_DrawBitmap(hori, verti, PlayerShip0, 18,8);
		Delay50ms(1);
	}
}






	



#include "ADC.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Globals.h"

#define menu_play 0
#define menu_diff 1
#define menu_high 2

char playMenuString[] = "PLAY";
char diffiMenuString[] = "DIFFICULTY";
char highscoreMenuString[] = "HIGH SCORES";	


#define diffi_easy 0
#define diffi_med 1
#define diffi_hard 2
#define diffi_back 2

char diffiEasy[] = "EASY";
char diffiMed[] = "MEDIUM";
char diffiHard[] = "HARD";
char diffiBack[] = "BACK";

void ADC_In89(int data[2]);

//int size33;
//size = ADCvalue[0];

void generateMenu(void){
	
	screen_num = 0;
	int menu_num = 0;
	
	ST7735_FillScreen(0x0000); 
	ST7735_DrawString(3, 4, playMenuString, 0xFFE0);	//PLAY STRING
	ST7735_DrawString(3, 6, diffiMenuString, 0xFFE0);	//DIFFI STRING
	ST7735_DrawString(3, 8, highscoreMenuString, 0xFFE0);	//HIGH SCORE STRING
	
	while(1){		
			
			if(menu_num == menu_play && up_down<1500){
				menu_num = menu_diff;
				while(up_down<1500);
			}
			
			if(menu_num == menu_diff && up_down<1500){
				menu_num = menu_high;
				while(up_down<1500);
			}
						
			
			if(menu_num == menu_diff && up_down>3500){
				menu_num = menu_play;
				while(up_down>3500);
			}
			
			
			if(menu_num == menu_high && up_down>3500){
				menu_num = menu_diff;
				while(up_down>3500);
			} 
			
			if(screen_num == menu_screen && menu_num == menu_play && (up_down>2000 && up_down<2100)){
				//draw black box
				//draw play pic
				ST7735_DrawString(3, 4, playMenuString, 0x0000);	//PLAY STRING
				Delay100ms(5);
				ST7735_DrawString(3, 4, playMenuString, 0xFFE0);	//PLAY STRING
				Delay100ms(5);
				if((buttonPress>>4)==1){
					screen_num = 3;
					checkSN();
				}

			} 
			if(screen_num == menu_screen && menu_num == menu_diff && (up_down>2000 && up_down<2100)){
				//draw black box
				//draw difficulty pic
				ST7735_DrawString(3, 6, diffiMenuString, 0x0000);	//DIFFI STRING
				Delay100ms(5);
				ST7735_DrawString(3, 6, diffiMenuString, 0xFFE0);	//DIFFI STRING
				Delay100ms(5);
				if((buttonPress>>4)==1){
					screen_num = 1;
					checkSN();
				}
			}
			if(screen_num == menu_screen && menu_num == menu_high && (up_down>2000 && up_down<2100)){
				//draw black box
				//draw highscore pic
				ST7735_DrawString(3, 8, highscoreMenuString, 0x0000);	//HIGH SCORE STRING
				Delay100ms(5);
				ST7735_DrawString(3, 8, highscoreMenuString, 0xFFE0);	//HIGH SCORE STRING
				Delay100ms(5);
				if((buttonPress>>4)==1){
					screen_num = 2;
					checkSN();
				}
			}
	}
}

void generateDiffi(void){
	screen_num = 1;
	int diffi_num = 0;
	
	ST7735_FillScreen(0x0000); 
	ST7735_DrawString(3, 4, diffiEasy, 0xFFE0);	//EASY STRING
	ST7735_DrawString(3, 6, diffiMed, 0xFFE0);	//MED STRING
	ST7735_DrawString(3, 8, diffiHard, 0xFFE0);	//HARD STRING
	ST7735_DrawString(3, 10, diffiBack, 0xFFE0);	//BACK STRING
	
	while(1){

		if(diffi_num == 0 && up_down<1500){
				diffi_num = 1;
				while(up_down<1500);
			}
		if(diffi_num == 1 && up_down<1500){
			diffi_num = 2;
			while(up_down<1500);
		}
		if(diffi_num == 1 && up_down>3500){
			diffi_num = 0;
			while(up_down>3500);
		}
		if(diffi_num == 2 && up_down<1500){
			diffi_num = 3;
			while(up_down<1500);
		}
		if(diffi_num == 2 && up_down>3500){
			diffi_num = 1;
			while(up_down>3500);
		}
		if(diffi_num == 3 && up_down>3500){
			diffi_num = 2;
			while(up_down>3500);
		}
		

		if(diffi_num == 0 && (up_down>2000 && up_down<2100)){
		//draw black box
		//draw play pic
		ST7735_DrawString(3, 4, diffiEasy, 0x0000);	//EASY STRING
		Delay100ms(5);
		ST7735_DrawString(3, 4, diffiEasy, 0xFFE0);	//EASY STRING
		Delay100ms(5);

		}
		if(diffi_num == 1 && (up_down>2000 && up_down<2100)){
			//draw black box
			//draw difficulty pic
			ST7735_DrawString(3, 6, diffiMed, 0x0000);	//MED STRING
			Delay100ms(5);
			ST7735_DrawString(3, 6, diffiMed, 0xFFE0);	//MED STRING
			Delay100ms(5);
		}
		if(diffi_num == 2 && (up_down>2000 && up_down<2100)){
			//draw black box
			//draw highscore pic
			ST7735_DrawString(3, 8, diffiHard, 0x0000);	//HARD STRING
			Delay100ms(5);
			ST7735_DrawString(3, 8, diffiHard, 0xFFE0);	//HARD STRING
			Delay100ms(5);
		}
		if(diffi_num == 3 && (up_down>2000 && up_down<2100)){
			//draw black box
			//draw highscore pic
			ST7735_DrawString(3, 10, diffiBack, 0x0000);	//BACK STRING
			Delay100ms(5);
			ST7735_DrawString(3, 10, diffiBack, 0xFFE0);	//BACK STRING
			Delay100ms(5);
			if((buttonPress>>4)==1){
					screen_num = 0;
					checkSN();
				}
		}
	}
}

void generateHS(void){
	
}

void generatePlay(void){
	
	ST7735_FillScreen(0x0000);
	EdgeInterrupt_Init();
	startEngine();
	
}


void checkSN(void){
	
	if(screen_num == menu_screen){
		generateMenu();
	}
	else if(screen_num == diff_screen){
		generateDiffi();
	}
	else if(screen_num == highscore_screen){
		generateHS();
	}
	else if(screen_num == play_screen){
		generatePlay();
	}
}
	


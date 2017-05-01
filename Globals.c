//extern int ADCvalue[2];

//int up_down = 0;

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "DAC.h"
#include "Sound.h"

/* ------------DELAY FUNCTIONS-------*/
void Delay50ms(int count){
	int volatile time;
  while(count>0){
    time = 300000;  // 0.05sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void Delay75ms(int count){
	int volatile time;
  while(count>0){
    time = 545430;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void Delay100ms(int count){
	int volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}
/*-----------------------------------*/

int playerShip_x = 52;
int ADCvalue[2]  = {0,0};
int screen_num = 0;

int up_down;
long buttonPress;
int testC = 0;

int hori=52;
int verti=159;

void init_All(void){
	TExaS_Init();  // set system clock to 80 MHz
  Random_Init(1);
  Output_Init();
	DAC_Init();
	ADC_Init89();
	SysTick_Init();
}

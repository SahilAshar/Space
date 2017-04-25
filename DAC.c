#include <stdint.h>
#include "tm4c123gh6pm.h"

void DAC_Init(void){
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_AFSEL_R = 0;
}


void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;
}


















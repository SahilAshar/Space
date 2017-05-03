#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "movement.h"
#include "ADC.h"
#include "Globals.h"
uint32_t idk=0;
uint32_t done;
uint8_t data;
uint32_t sound_flag;

void Sound_Play(const uint8_t *pt, uint32_t count){
	data=pt[idk];
	GPIO_PORTB_DATA_R=data;
	idk++;
	if(idk==count){
		done=1;
		idk=0;
	
	}
	sound_flag=1;
};


void ADC_Init89(void){ 
  volatile uint32_t delay;                         
//  SYSCTL_RCGC0_R |= 0x00010000; // 1) activate ADC0 (legacy code)
  SYSCTL_RCGCADC_R |= 0x00000001; // 1) activate ADC0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // 1) activate clock for Port E
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
  delay = SYSCTL_RCGCGPIO_R;      // 2) allow time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTC_DIR_R &= ~0x10;
	GPIO_PORTC_DEN_R |= 0xFF;
	GPIO_PORTC_AFSEL_R = 0;
  GPIO_PORTE_DIR_R &= ~0x30;      // 3) make PE3 PE4 PE5 input
  GPIO_PORTE_AFSEL_R |= 0x30;     // 4) enable alternate function on PE4 PE5
  GPIO_PORTE_DEN_R &= ~0x30;      // 5) disable digital I/O on PE4 PE5/Enable on PE3
                                  // 5a) configure PE4 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R&0xFF00FFFF;
  GPIO_PORTE_AMSEL_R |= 0x30;     // 6) enable analog functionality on PE4 PE5
  ADC0_PC_R &= ~0xF;              // 8) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3012;          // 9) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0004;        // 10) disable sample sequencer 2
  ADC0_EMUX_R &= ~0x0F00;         // 11) seq2 is software trigger
  ADC0_SSMUX2_R = 0x0089;         // 12) set channels for SS2
  ADC0_SSCTL2_R = 0x0060;         // 13) no TS0 D0 IE0 END0 TS1 D1, yes IE1 END1
  ADC0_IM_R &= ~0x0004;           // 14) disable SS2 interrupts
  ADC0_ACTSS_R |= 0x0004;         // 15) enable sample sequencer 2
}

//------------ADC_In89------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: two 12-bit result of ADC conversions
// Samples ADC8 and ADC9 
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// data[0] is ADC8 (PE5) 0 to 4095
// data[1] is ADC9 (PE4) 0 to 4095
void ADC_In89(int data[2]){ 
  ADC0_PSSI_R = 0x0004;            // 1) initiate SS2
  while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done
  data[1] = ADC0_SSFIFO2_R&0xFFF;  // 3A) read first result
  data[0] = ADC0_SSFIFO2_R&0xFFF;  // 3B) read second result
  ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = 2666666-1;// reload value  
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF) | 0x40000000; //sets priority level 2
	NVIC_ST_CTRL_R = 0x07; //enables interrupts
}

void SysTick_Handler(void){
//	if(screen_num == 0 || screen_num == 1){
//		getADCInfo();
//		buttonPress = GPIO_PORTC_DATA_R&0x10;
//	}
//	frameFlag = 1;
		getADCInfo();
		buttonPress = GPIO_PORTC_DATA_R&0x10;
	
}

void getADCInfo(void){
	ADC_In89(ADCvalue);
	up_down = ADCvalue[1]; 
	left_right = ADCvalue[0];
}


void EdgeInterrupt_Init(void){
	GPIO_PORTC_AMSEL_R &= ~0x10;	//disable analog function on PC4
	GPIO_PORTC_PCTL_R &= ~0x000F0000;	//set PC4 as GPIO
	GPIO_PORTC_DIR_R &= ~0x10;	//PC4 is an input
	GPIO_PORTC_AFSEL_R &= ~0x10;	//disable alt function on PC4
	GPIO_PORTC_DEN_R |= 0x10;	//enable digital I/O on PC4
	GPIO_PORTC_IS_R &= ~0x10;	//PC4 is edge sensitive
	GPIO_PORTC_IBE_R &= ~0x10;	//PC4 is not both edges
	GPIO_PORTC_IEV_R |= 0x10;	//PC4 is a rising edge event
	GPIO_PORTC_ICR_R = 0x10;	//clear flag4
	GPIO_PORTC_IM_R |= 0x10;	//enable interrupt on PC4
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFF00FFFF) | 0x00400000;	//priority 2
	NVIC_EN0_R = 0x00000004;	//enable interrupts 2 in NVIC
}

void GPIOPortC_Handler(void){
	GPIO_PORTC_ICR_R = 0x10;	//acknowledge flag4
	shotFired_flag = 1;
	if(shotFired_ticks>0 && shotFired_ticks != 160){
	
	}
	else{
		shotFired_ticks = 160;
	}
	
}

void Timer3_Init(void){
	SYSCTL_RCGCTIMER_R |= 0x0008;	// 0) activate timer3
	TIMER3_CTL_R = 0x00000000;		// 1) disable timer3 during setup
	TIMER3_CFG_R = 0x00000000;		// 2) configure 32 bit timer mode
	TIMER3_TAMR_R = 0x00000002;		// 3) configure for periodic mode
	TIMER3_TAILR_R = 2000000-1;		// 4) reload value
	TIMER3_TAPR_R = 0;						// 5) 12.5ns timer3
	TIMER3_ICR_R = 0x00000001;		// 6) clear timer3 timeout flag
	TIMER3_IMR_R |= 0x00000001;		// 7) arm timeout interrupt
	NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF) | 0x40000000;	// 8) priority 2
	NVIC_EN1_R = 1<<(35-32);			// 9) enable IRQ 35 in NVIC
	TIMER3_CTL_R |= 0x00000001;		// 10) enable timer3
}

void Timer3A_Handler(void){
	TIMER3_ICR_R = 0x00000001;
	if(shotFired_flag == 1 && shotFired_ticks==160){
		generateBullet(hori, verti);
		testC++;
	}
	if(shotFired_flag == 1 && shotFired_ticks>0){
		moveBullet();
		shotFired_ticks--;
	}
	if(shotFired_flag == 1 && shotFired_ticks == 0){
		shotFired_flag = 0;
	}
}


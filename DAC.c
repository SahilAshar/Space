#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#define DSharpHi 1004
#define FSharpHi 845
#define GSharp 	1505
#define DSharp	2009
#define B				1265
#define ASharp	1341
#define FSharp	1689
#define CSharp	2255
#define E				1896
#define CSharpHi	1127
#define DSharpHi	1004
#define EHi			948
uint32_t i=0;
uint32_t cs=0;
uint32_t flag=0;
void (*PeriodicTask)(void);
void tempointerrupt (void);
void noteinterrupt (void);
void WaitForInterrupt(void);
void play_menu_music(void);
uint8_t dac_wave[64]={127, 139, 152, 164, 176, 187, 198, 208, 217, 225, 233, 239, 244, 249, 252, 253,
254, 253, 252, 249, 244, 239, 233, 225, 217, 208, 198, 187, 176, 164, 152, 139,
127, 115, 102, 90, 78, 67, 56, 46, 37, 29, 21, 15, 10, 5, 2, 1,
0, 1, 2, 5, 10, 15, 21, 29, 37, 46, 56, 67, 78, 90, 102, 115};




void DAC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	uint32_t cycle=0;
	cycle=1;
	cycle=2;
	cycle=3;
	GPIO_PORTB_DEN_R |= 0xFF;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_AFSEL_R = 0;
}


void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;
}
struct music {
	uint32_t note;
	uint32_t tempo;
};

struct music menu_song[34]={
{DSharpHi,20000000},
{FSharpHi,20000000},
{GSharp,20000000},	
{B,20000000},
{ASharp,20000000},
{FSharp,20000000},
{CSharp,20000000},
{DSharp,20000000},
{E,20000000},
{GSharp,20000000},
{CSharpHi,20000000},
{DSharpHi,20000000},
{EHi,20000000},
{DSharpHi,20000000},
{B,20000000},
{ASharp,20000000},
{GSharp,20000000},
{DSharp,20000000},
{GSharp,20000000},
{B,20000000},
{ASharp,20000000},
{FSharp,20000000},
{CSharp,20000000},
{DSharp,20000000},
{E,20000000},
{GSharp,20000000},
{B,20000000},
{CSharp,20000000},
{DSharp,20000000},
{FSharp,20000000},
{B,20000000},
{ASharp,20000000}};

void Timer0_Init(void(*task)(void), uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0         // user function
	PeriodicTask = task;
	TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = period-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5 bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
}
void noteinterrupt (void){
if(cs+1==34){
		cs=0;
	}
		DAC_Out(dac_wave[i]);
		i += 1;
		if (i == 64){
			i = 0;
	}
	Timer0_Init(noteinterrupt, menu_song[cs].note);
}
void Timer0A_Handler(void){
	(*PeriodicTask)();
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER0A timeout
}

void Timer1_Init(void(*task)(void),uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1         // user function
	PeriodicTask=task;
	TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00004000; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}
void tempointerrupt (void){
	if(cs+1==34){
		cs=0;
	}
	else{
		cs++;
	}
	flag=1;

}
void Timer1A_Handler(void){
	(*PeriodicTask)();
	TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
              // execute user task
	
}

void play_menu_music (void){
	if(cs+1==34){
		cs=0;
	}
	flag=0;
	Timer0_Init(noteinterrupt, menu_song[cs].note);
	Timer1_Init(tempointerrupt, menu_song[cs].tempo);
	while(flag==0){
		WaitForInterrupt();
	}
}

















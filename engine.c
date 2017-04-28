#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
 
uint32_t choose_diff (void);
void play_game (uint32_t diff);
uint32_t display_hi (uint32_t hi_score);



//void menu (void){
//	uint32_t position;
//	uint32_t diff_number;
//	if(position==choose_level){
//		level_number=choose_diff();
//	}
//	if(position==play){
//		play_game(diff_number);
//	}
//	if(position==high_score){
//		display_screen=display_hi(hi_score);
//	}

//void play_game(uint32_t diff){
//	
//}


//}
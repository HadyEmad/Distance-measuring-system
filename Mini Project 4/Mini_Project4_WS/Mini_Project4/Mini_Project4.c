 /******************************************************************************
 *
 * File Name: Mini_Project4.h
 *
 * Description: Main source file for the project
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "lcd.h"
#include <avr\io.h>

int main(void){
	LCD_init();
	SREG |= (1<<7);
	ULTRASONIC_init();
	LCD_displayString("Distance = ");
	while(1){
		LCD_moveCursor(0,11);
		LCD_intgerToString(ULTRASONIC_readDistance());
		LCD_displayString("cm ");
	}
}

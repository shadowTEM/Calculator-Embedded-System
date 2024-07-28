
/*
 *  Created on: JUly 28,2024
 *      Author: Youssef
 */

#include "DATA_TYPE.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "Calculator.c"
#include <string.h>
#include "DIO.h"
#include "LCD.h"
#include "KPD.h"


/* defines */
#define MAX_buffer_LENGTH 100
#define F_CPU 8000000UL
int main(void)
{
	DIO_voidInit();
	LCD_voidInit();
	LCD_voidSendString("Youssef salah");
	_delay_ms(6000);
	LCD_voidSendCmnd(lcd_Clear);
	LCD_voidGotoxy(1, 1);
	LCD_voidSendString("Cal ready");
	_delay_ms(6000);
	LCD_voidSendCmnd(lcd_Clear);
	u8 key, flagClear = 0, buffer_position = 0;

	u8 buffer[MAX_buffer_LENGTH]; //array to store the whole buffer

	while (1)
	{

		KPD_u8GetKeyState(&key);
		if (key != KPD_u8_KEY_NOT_PRESSED
				&& (   key == '1' || key == '2' || key == '3' || key == '4'
					|| key == '5' || key == '6' || key == '7' || key == '8'
					|| key == '9' || key == '0' || key == '+' || key == '-'
					|| key == '*' || key == '/'))
		{

			if (flagClear == 1)
			{
				LCD_voidSendCmnd(lcd_Clear);                          //clearing the LCD
				flagClear = 0;
			}
			if (buffer_position < MAX_buffer_LENGTH - 1)
				buffer[buffer_position++] = key;                     //store the characters in the array

			LCD_voidSendChar(key);                                   //printing every character
		}
		else if (key == '=')
		{
			flagClear = 1;                                           //flag is up after every process

			buffer[buffer_position] = '\0';                          // terminate the string

			f64 result = evaluate(buffer);                           //calling the evaluate function to calculate the buffer

			if (flagZero == 1)                                       //when divide by zero flag is up
			{
				LCD_voidGotoxy(2, 1);
				LCD_voidSendString("error div by 0");
				flagZero = 0;

			}
			else if (flagSyntax == 1)                               //when divide by zero flag is up
			{
				LCD_voidGotoxy(2, 1);
				LCD_voidSendString("Syntax error");
				flagSyntax = 0;
			}
			else {
				LCD_voidGotoxy(2, 1);
				LCD_voidSendChar('=');
				LCD_voidSendFloat(result);
			}
			buffer_position = 0;

			memset(buffer, 0, sizeof(buffer));                     //to clear the buffer
		}
		else if (key == 'C')                                       //clearing the LCD
		{
			buffer_position = 0;
			memset(buffer, 0, sizeof(buffer));
			LCD_voidSendCmnd(lcd_Clear);

		}
	};
	return 0;
}


/*
 *  Created on: JUly 28,2024
 *      Author: Youssef
 */


#include "DATA_TYPE.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include "util/delay.h"
#include "DIO.h"
#include "LCD.h"
#include "LCD_cfg.h"
#include "LCD_register.h"

void LCD_voidInit(void) {
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(35);

	/* Return Home  */
	LCD_voidSendCmnd(lcd_Home);
	_delay_ms(1);

	/* Function Set  */
	LCD_voidSendCmnd(lcd_FunctionSet8bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_voidSendCmnd(lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */
	LCD_voidSendCmnd(lcd_Clear);
	_delay_ms(1);

	/* Entry Mode Set  */
	LCD_voidSendCmnd(lcd_EntryMode);
	_delay_ms(2);

#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(35);

	/* Return Home  */
	LCD_voidSendCmnd(lcd_Home);
	_delay_ms(1);

	/* Function Set  */
	LCD_voidSendCmnd(lcd_FunctionSet4bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_voidSendCmnd(lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */
	LCD_voidSendCmnd(lcd_Clear);
	_delay_ms(1);

	/* Entry Mode Set  */
	LCD_voidSendCmnd(lcd_EntryMode);
	_delay_ms(2);
#endif
}

void LCD_voidSendCmnd(u8 Copy_u8Cmnd) {

#if LCD_u8_MODE == LCD_u8_MODE_8_BIT

	/* Set RS to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);

	/* Set R/W to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);

	/* Set E to DIO_u8_HIGH  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);

#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT

	/* Set RS to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);

	/* Set R/W to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);

	/* Set E to DIO_u8_HIGH  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);

	/*write the rest of the command */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd << 4);

	/* Set E to DIO_u8_HIGH  */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
#endif

}

void LCD_voidSendChar(u8 Copy_u8Data) {

#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	/* Set RS to HIG */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);

	/* Set R/W to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Set E to DIO_u8_HIGH */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Data);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_HIGH */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Delay to let the LCD Display the character */
	_delay_ms(2);

#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	/* Set RS to HIG */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);

	/* Set R/W to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	/* Set E to DIO_u8_HIGH */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Load Command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Data);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_HIGH */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/*Load the rest of the command on Data bus */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Data << 4);

	/* Set E to DIO_u8_LOW */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);

	/* Wait for E to settle */
	_delay_ms(2);

	/* Set E to DIO_u8_HIGH */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);

	/* Delay to let the LCD Display the character */
	_delay_ms(2);

#endif

}

void LCD_voidSendString(u8 *Copy_pu8String) {

	//	/* Local loop index */
	//	u8 u8Index = 0;
	u8 iteration = 0;
	//	while (pu8StringCpy[u8Index] != '\0')
	for (iteration = 0; Copy_pu8String[iteration] != '\0'; iteration++) {
		/* Write Character on LCD */
		LCD_voidSendChar(Copy_pu8String[iteration]);

	}
}

void LCD_voidSendIntger(s32 Copy_s32Data) {
	u32 str[10];

	sprintf(str, "%ld", Copy_s32Data);
	LCD_voidSendString(str);
}

void LCD_voidSendFloat(f64 Copy_f32Data) {
	s32 int_part;
	f32 frac_part;
	// separate integer and fractional parts
	int_part = (s32) Copy_f32Data;
	frac_part = Copy_f32Data - int_part;
	frac_part = (s32) (frac_part * 1000);
	LCD_voidSendIntger(int_part);
	LCD_voidSendChar('.');
	LCD_voidSendIntger(frac_part);
}

void LCD_voidGotoxy(u8 Copy_u8Y, u8 Copy_u8X) {
	if (Copy_u8X > 0 && Copy_u8X <= 16) {
		switch (Copy_u8Y) {
		case 1:
			LCD_voidSendCmnd(Copy_u8X + 127);
			break;
		case 2:
			LCD_voidSendCmnd(Copy_u8X + 191);
			break;
		default:
			break;
		}
	}
}






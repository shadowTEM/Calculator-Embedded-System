/*
 *  Created on: JUly 28,2024
 *      Author: Youssef
 */

#ifndef LCD_H
#define LCD_H
#define lcd_Clear           		 0x01
#define lcd_Home           			 0x02
#define lcd_EntryMode       	     0x06
#define lcd_DisplayOff     			 0x08
#define lcd_DisplayOn      			 0x0F
#define lcd_FunctionReset   		 0x30
#define lcd_FunctionSet8bit 		 0x38
#define lcd_FunctionSet4bit 		 0x2F
#define lcd_u8SetCursor     		 0x80



void LCD_voidInit(void);


void LCD_voidSendCmnd(u8 Copy_u8Cmnd);

void LCD_voidSendChar(u8 Copy_u8Data);

void LCD_voidSendString (u8* Copy_pu8String);

void LCD_voidSendIntger(s32 Copy_s32Data);
void LCD_voidSendFloat(f64 Copy_f32Data);

void LCD_voidGotoxy (u8 Copy_u8Y,u8 Copy_u8X);
void LCD_voidSendExtraChar (u8 Copy_u8Y,u8 Copy_u8X);


void LCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);
#endif /* LCD_H_ */

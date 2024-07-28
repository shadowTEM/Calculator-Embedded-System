/*
 *  Created on: JUly 28,2024
 *      Author: Youssef
 */

#include "DATA_TYPE.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include <string.h>
#include "DIO.h"
#include "LCD.h"
#include "KPD.h"

/* defines */
#define MAX_buffer_LENGTH 100
#define F_CPU 8000000UL
/*flags */
u8 flagClear = 0, flagZero = 0,flagSyntax=0; //to clear LCD after every process, detect dividing by 0


f64 evaluate(u8 *buffer)                            // 6*5-1/9
{
    f64 result = 0.0f;
    f32 num = 0.0f;
    s8 op = '+';
    s16 length = strlen(buffer);
    s16 i = 0;

    while (i < length)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            num = num * 10.0f + (buffer[i] - '0');
            i++;

        }
        else if (buffer[i] == '*' || buffer[i] == '/')
        {
        	if(buffer[i+1]=='*' || buffer[i+1] == '/' || buffer[i+1]=='-' || buffer[i+1] == '+' )

        		flagSyntax=1;

            s8 c = buffer[i];
            i++;
            f32 next_num = 0.0f;
            u8 flagNextNum=0;

            while (i < length && buffer[i] == ' ')
            {
                i++;
            }
            while (i < length && buffer[i] >= '0' && buffer[i] <= '9')
            {
                next_num = next_num * 10.0f + (buffer[i] - '0');
                i++;
                flagNextNum++;
            }
            while (i < length && buffer[i] == ' ')
            {
                i++;
            }

            if (c == '*')
            {
                num *= next_num;
            }
            else
            {
            	if(flagNextNum<1)
            	{
            		flagSyntax=1;
            		return flagSyntax;
            	}

            	if (next_num == 0.0f)
            	{
                	flagZero = 1;
                	return flagZero;
                }
                num /= next_num;
            }
        }
        else
        {
        	if(buffer[i+1]=='*' || buffer[i+1] == '/' || buffer[i+1]=='-' || buffer[i+1] == '+' )
        	flagSyntax=1;

            if (op == '+')
            {
                result += num;
            }
            else
            {
                result -= num;
            }
            num = 0.0f;
            op = buffer[i];
            i++;
        }
    }
    if (op == '+')
    {
        result += num;
    }
    else
    {
        result -= num;
    }
    return result;
}

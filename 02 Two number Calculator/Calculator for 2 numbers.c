#include<reg51.h>
#define lcd_dat P3

sbit R1 = P2^0;
sbit R2 = P2^1;
sbit R3 = P2^2;
sbit R4 = P2^3;
sbit C1 = P2^4;
sbit C2 = P2^5;
sbit C3 = P2^6;
sbit C4 = P2^7;

sbit rs = P1^0;
sbit rw = P1^1;
sbit e = P1^2;

void delay(int a)
{
	int i,j;
	for(i=0; i<a; i++)
	{
		for(j=0;j<500;j++)
		{
		}
	}	
}

void lcd_cmd(unsigned char cmd)
{
	lcd_dat=cmd;
	rs=0;
	rw=0;
	e=1;
	delay(10);
	e=0;
}

void lcd_data(unsigned char a)
{
	lcd_dat=a;
	rs=1;
	rw=0;
	e=1;
	delay(10);
	e=0;
}

void lcd_display_number(int num) 
{
    char buffer[10]; 												// Buffer to store the number as a string (supports up to 5 digits)
    int i = 0, j = 0;
    if (num == 0) 
		{
        lcd_data('0');
        return;
    }

    while (num > 0) 
		{
        buffer[i++] = (num % 10) + '0'; 		// Extract the least significant digit
        num /= 10;
    }
		
    for (j = i - 1; j >= 0; j--) 
		{  																			// Send digits in reverse order
        lcd_data(buffer[j]);
    }
}

void main()
{
	int current_num = 0;
	int Num1 = 0;
	int Num2 = 0;
	int flag = 0;
	int operation = 0;
	int result = 0;
	
	lcd_cmd(0x38);
	delay(10);	
	lcd_cmd(0x0F);														// turn on display
	delay(10);
	lcd_cmd(0x01);														// clear display
	delay(10);	
	lcd_cmd(0x80);														//First row first character
	delay(10);
	
	R1 = R2 = R3 = R4 = C1 = C2 = C3 = C4 = 1;
	while(1)
	{
		R1 = 0;
		R2=R3=R4=1;
		if(C1 == 0)															//number 7
		{
			lcd_data('7');
			delay(105);
			current_num = current_num*10 + 7;
		}
		else if(C2 == 0)												//number 8
		{
			lcd_data('8');
			delay(105);
			current_num = current_num*10 + 8;
		}
		else if(C3 == 0)												//number 9
		{
			lcd_data('9');
			delay(105);
			current_num = current_num*10 + 9;
		}
		else if(C4 == 0)												//divide button
		{
			delay(105);
			if(flag == 0)
			{
				Num1 = current_num;									//stores in num1
				delay(105);
				current_num = 0;
				delay(105);
				lcd_cmd(0x01);											//clear display
				flag = 1;
			}
			operation = 4;
		}	
		
		R2 = 0;
		R1=R3=R4=1;
		if(C1 == 0)
		{
			lcd_data('4');												//number 4
			delay(105);
			current_num = current_num*10 + 4;
		}
		else if(C2 == 0)												//number 5
		{
			lcd_data('5');
			delay(105);
			current_num = current_num*10 + 5;
		}
		else if(C3 == 0)												//number 6
		{
			lcd_data('6');
			delay(105);
			current_num = current_num*10 + 6;
		}
		else if(C4 == 0)												//multiply button
		{	
			delay(105);
			if(flag == 0)
			{
				Num1 = current_num;
				delay(105);
				current_num = 0;
				delay(105);
				lcd_cmd(0x01);											//clear display
				flag = 1;
			}
			operation = 3;
		}
		
		R3 = 0;
		R1=R2=R4=1;
		if(C1 == 0)
		{
			lcd_data('1');												//number 1
			delay(105);	
			current_num = current_num*10 + 1;
		}
		else if(C2 == 0)												//number 2
		{
			lcd_data('2');
			delay(105);		
			current_num = current_num*10 + 2;
		}
		else if(C3 == 0)												//number 3
		{
			lcd_data('3');
			delay(105);
			current_num = current_num*10 + 3;
		}
		else if(C4 == 0)												//subract button
		{
			delay(105);
			if(flag == 0)
			{
				Num1 = current_num;
				delay(105);
				current_num = 0;
				delay(105);
				lcd_cmd(0x01);											//clear display
				flag = 1;
			}
			operation = 2;
		}
		
		
		R4 = 0;
		R1=R2=R3=1;
		if(C1 == 0)															//ON OFF
		{
			lcd_cmd(0x01);												//clear display
			delay(20);
			lcd_cmd(0x80);												//First row first character
			delay(20);
		}
		else if(C2 == 0)												//number 0
		{
			lcd_data('0');
			delay(105);
			current_num = current_num*10 + 0;
		}
		else if(C3 == 0)												//equalto button
		{
			if(flag==1)
			{
				Num2 = current_num;									//stores in num2
				delay(105);
				lcd_cmd(0x01);											//clear display
				if(operation == 1)
				{
					result = Num1 + Num2;
				}
				else if(operation == 2)
				{
					result = Num1 - Num2;
				}
				else if(operation == 3)
				{
					result = Num1 * Num2;
				}
				else if(operation == 4)
				{
					result = Num1 / Num2;
				}
			}			
			
			lcd_display_number(result);
			
		}
		else if(C4 == 0)												//addition button
		{
			delay(105);
			if(flag == 0)
			{
				Num1 = current_num;									//stores in num1
				delay(105);
				current_num = 0;
				delay(105);
				lcd_cmd(0x01);											//clear display
				flag = 1;
			}
			operation = 1;
		}
	}
}
		
	

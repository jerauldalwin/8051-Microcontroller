#include<reg51.h>

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;
sbit C1 = P3^4;
sbit C2 = P3^5;
sbit C3 = P3^6;


void main()
{
	while(1)
	{
		R1=R2=R3=R4=C1=C2=C3=1;
	

		R1 = 0;
		R2 = R3 = 1;
		
		if(C1==0)					//number 1 - MOTOR 1 ANTI CLK WISE
		{
			P2 = 0x05;
		}
		else if(C2==0)		//number 2 - MOTOR 1 CLK WISE
		{
			P2 = 0x06;
		}
		else if(C3==0)		//number 3 - MOTOR 2 ANTI CLK WISE
		{
			P2 = 0x18;
		}
		
		R2 = 0;
		R1 = R3 = 1;
		
		if(C1==0)					//number 4 - MOTOR 2 CLK WISE
		{
			P2 = 0x28;
		}
		else if(C2==0)		//number 5 - MOTOR 1 & 2 ANTI CLK WISE
		{
			P2 = 0x1D;
		}
		else if(C3==0)		//number 6 - MOTOR 1 & 2 CLK WISE
		{
			P2 = 0x2E;
		}
			
		R4 = 0;
		R1 = R2 = R3 = 1;
		if(C2 == 0)
		{
			P2 = 0x00;			//number 0 - BOTH MOTORS OFF
		}
		
	}
}

#include "main.h"
#include "TM1637.h"

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D

const uint8_t segmentMap[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  };


#define CLK_HIGH() HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define CLK_LOW()  HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
#define DATA_HIGH() HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET)
#define DATA_LOW()  HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);


void Delay_us (int time)
{
	for (int i=0; i<time; i++)
	{
		for (int j=0; j<7; j++)
		{
			__asm__("nop");
		}
	}
}

void start (void)
{

	CLK_HIGH();
	DATA_HIGH();
	Delay_us (2);
	DATA_LOW();
}

void stop (void)
{
	CLK_LOW();
	Delay_us (2);
	DATA_LOW();
	Delay_us (2);
	CLK_HIGH();
	Delay_us (2);
	DATA_HIGH();
}

void waitforAck (void)
{
	CLK_LOW();
	Delay_us (5); // After the falling edge of the eighth clock delay 5us
	              // ACK signals the beginning of judgment
//	while (dio);  // Check the state of the Data pin
	CLK_HIGH();
	Delay_us (2);
	CLK_LOW();
}

void writeByte (uint8_t byte)
{
	int i;
	for (i = 0; i<8; i++)
	{
		CLK_LOW();
		if (byte & 0x01) // low front
		{
			DATA_HIGH();
		}
		else
		{
			DATA_LOW();
		}
		Delay_us (3);
		byte = byte >> 1;
		CLK_HIGH();
		Delay_us (3);
	}
}

void TM1637_WriteData (uint8_t Addr, uint8_t *data, int size)
{
	start();
	writeByte(0x40);
	waitforAck();
	stop();

	start();
	writeByte(Addr);
	waitforAck();
	for (int i=0; i<size; i++)
	{
		writeByte(data[i]);
		waitforAck();
	}
	stop();

	start();
	writeByte(0x8A);
	waitforAck();
	stop();
}

void TM1637_WriteNum (uint8_t Addr, int num, int colon)
{
	uint8_t buffer[4];
	int len;

	if ((num/1000) != 0) len =4;
	else if ((num/100) != 0) len =3;
	else if ((num/10) != 0) len =2;
	else len =1;

	for (int i=0; i<len; i++)
	{
		buffer[len-1-i] = segmentMap[num%10];
		num = num/10;
	}

	if (colon) buffer[1] |= 1<<7;  // turn on the colon

	TM1637_WriteData(Addr, buffer, len);
}


void TM1637_WriteTime (uint8_t *Time, int colon)
{
	static int dColon = 0;
	static int sChange = 0;
	uint8_t buffer[4];

	for (int i=0; i<4; i++)
	{
		buffer[3-i] = segmentMap[Time[i]];
	}

	if (sChange != Time[0])  // if the unit digit in the time changes
	{
		if (colon) dColon = !dColon;
		if (dColon) buffer[1] |= 1<<7;
		sChange = Time[0];  // update the sChange with current value of the unit digit
		TM1637_WriteData(0xC0, buffer, 4);
	}
}





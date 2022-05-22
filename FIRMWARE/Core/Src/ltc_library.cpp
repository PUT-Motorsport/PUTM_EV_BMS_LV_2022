/*
 * ltc_library.cpp
 *
 *  Created on: May 22, 2022
 *      Author: Maks
 */

#include <ltc_library.hpp>
#include <cstring>

uint16_t pec15Table[256];
uint16_t CRC15_POLY = 0x4599;
uint8_t ltcConfig[6] = {0xFC, (uint8_t)(1874 & 0xff), (uint8_t)((1874>>4)|(2625<<4)), (uint8_t)(2625>>4), 0, 0};

void init_PEC15_Table()
{
	uint16_t remainder;
	for (int i = 0; i < 256; i++)
	{
		remainder = i << 7;
		for (int bit = 8; bit > 0; --bit)
		{
			if (remainder & 0x4000)
			{
				remainder = ((remainder << 1));
				remainder = (remainder ^ CRC15_POLY);
			}
			else
			{
				remainder = ((remainder << 1));
			}
		}
		pec15Table[i] = remainder&0xFFFF;
	}
}

uint16_t pec15(char *data , int len)
{
	uint16_t remainder,address;
	remainder = 16;//PEC seed
	for (int i = 0; i < len; i++)
	{
		address = ((remainder >> 7) ^ data[i]) & 0xff;//calculate PEC table address
		remainder = (remainder << 8 ) ^ pec15Table[address];
	}
	return (remainder*2);//The CRC15 has a 0 in the LSB so the final value must be multiplied by 2
}

/**
 * Brief:	Send wakeup for LTC, BLOCKING MODE
 * Param:	None
 * Retval:	None
 */
void LTC_wake_up()
{
	uint8_t tab[2] = {0xFF};

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 2, 1);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}


/**
 * Brief:	Send adc config for ltc and start conversion, BLOCKING MODE
 * Param:	None
 * Retval:	None
 */
void LTC_start_cell_adc()
{
	uint8_t tab[12];
	uint16_t pec;

	uint16_t cmd = (1<<15) | 0x01;
	// configuration
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	tab[4] = ltcConfig[0];
	tab[5] = ltcConfig[1];
	tab[6] = ltcConfig[2];
	tab[7] = ltcConfig[3];
	tab[8] = ltcConfig[4];
	tab[9] = ltcConfig[5];
	pec = pec15((char*)&tab[4], 6);
	tab[10] = pec >> 8;
	tab[11] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 12, 20);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);


	// adc conversion

	memset(tab, 0, 12);

	//cmd = 0b1001100000 | (0b00 << 7); // discharge not permitted
	cmd = 0b1001110000 | (0b00 << 7); // discharge permitted
	tab[0] = cmd>>8;
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 4, 20);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}



/**
 * Brief:	Receveing adc data from ltc, BLOCKING MODE
 * Param:	None
 * Retval:	None
 */
void LTC_get_values_adc(uint16_t *cell_values)
{
	uint8_t tab[100], rx_tab[100];
	uint16_t pec;

	// read cell voltage group A
	uint16_t cmd = (1<<15) | 0b100;
	memset(tab, 0, 12);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tab, rx_tab, 12, 20);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);


	cell_values[0] = (uint16_t)rx_tab[4] | (((uint16_t)rx_tab[5])<<8);
	cell_values[1] = (uint16_t)rx_tab[6] | (((uint16_t)rx_tab[7])<<8);
	cell_values[2] = (uint16_t)rx_tab[8] | (((uint16_t)rx_tab[9])<<8);


	// read cell voltage group B
	cmd = (1<<15) | 0b110;
	memset(tab, 0, 12);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tab, rx_tab, 12, 20);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

	cell_values[3] = (uint16_t)rx_tab[4] | (((uint16_t)rx_tab[5])<<8);
	cell_values[4] = (uint16_t)rx_tab[6] | (((uint16_t)rx_tab[7])<<8);
	cell_values[5] = (uint16_t)rx_tab[8] | (((uint16_t)rx_tab[9])<<8);


}

/**
 * Brief:	Muting discharge
 * Param:	None
 * Retval:	None
 */
void mute_dis()
{
	uint8_t tab[4];
	uint16_t pec;


	uint16_t cmd = (1<<15) | 0b101000;
	memset(tab, 0, 4);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 4, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}
/**
 * Brief:	Unmuting discharge
 * Param:	None
 * Retval:	None
 */
void unmute_dis()
{
	uint8_t tab[4];
	uint16_t pec;


	uint16_t cmd = (1<<15) | 0b101001;
	memset(tab, 0, 4);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 4, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
}

/**
 * Brief:	Send discharge configuration and start the discharge, BLOCKING MODE
 * Param:	cell: number of cell wanted to be discharged
 * Retval:	None
 */
void LTC_turn_on_discharge(int cell, bool *cellDischarge)
{
	uint8_t tab[12];
	uint16_t pec;

	unmute_dis();

	uint16_t cmd = (1<<15) | 0b10100;
	memset(tab, 0, 12);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;


	tab[4] = (cellDischarge[0]) | (cellDischarge[1] << 4); // 1, 2
	tab[5] = (cellDischarge[2]) | (cellDischarge[3] << 4); // 3, 4
	tab[6] = (cellDischarge[4]) | (cellDischarge[5] << 4); // 5, 6
	tab[7] = 0;
	tab[8] = 0;
	tab[9] = 0;
	pec = pec15((char*)&tab[4], 6);
	tab[10] = pec >> 8;
	tab[11] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 12, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

	cmd = (1<<15) | 0x01;
	memset(tab, 0, 12);
	// configuration
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	tab[4] = ltcConfig[0];
	tab[5] = ltcConfig[1];
	tab[6] = ltcConfig[2];
	tab[7] = ltcConfig[3];
	if(cell<7){
		ltcConfig[4] = ltcConfig[4] | (1 << (cell));
	}
	tab[8] = ltcConfig[4];
	tab[9] = ltcConfig[5];
	pec = pec15((char*)&tab[4], 6);
	tab[10] = pec >> 8;
	tab[11] = pec;


	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 12, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);


}

/**
 * Brief:	Turn off discharge, BLOCKING MODE
 * Param:	None
 * Retval:	None
 */
void LTC_turn_off_discharge()
{

	uint8_t tab[100];
	uint16_t pec;


	uint16_t cmd = (1<<15) | 0b10100;
	memset(tab, 0, 12);
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;


	tab[4] = 0;
	tab[5] = 0;
	tab[6] = 0;
	tab[7] = 0;
	tab[8] = 0;
	tab[9] = 0;
	pec = pec15((char*)&tab[4], 6);
	tab[10] = pec >> 8;
	tab[11] = pec;

	LTC_wake_up();

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 12, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);


	cmd = (1<<15) | 0x01;
	memset(tab, 0, 12);
	// configuration
	tab[0] = (cmd>>8);
	tab[1] = cmd;
	pec = pec15((char*)tab, 2);
	tab[2] = pec >> 8;
	tab[3] = pec;

	ltcConfig[4] = 0;

	tab[4] = ltcConfig[0];
	tab[5] = ltcConfig[1];
	tab[6] = ltcConfig[2];
	tab[7] = ltcConfig[3];
	tab[8] = ltcConfig[4];
	tab[9] = ltcConfig[5];
	pec = pec15((char*)&tab[4], 6);
	tab[10] = pec >> 8;
	tab[11] = pec;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tab, 12, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

	mute_dis();
}




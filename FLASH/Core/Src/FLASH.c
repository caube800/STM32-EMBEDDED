/*
 * FLASH.c
 *
 *  Created on: Oct 14, 2024
 *      Author: Admin
 */
#include"FLASH.h"
#include"stm32f1xx.h"

void Flash_erase (uint32_t address)
{
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks = 1;
	EraseInitStruct.NbPages = 1;
	EraseInitStruct.PageAddress = address;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t pageer;
	HAL_FLASHEx_Erase (&EraseInitStruct, &pageer);
	HAL_FLASH_Lock();
}

void Flash_write_int (uint32_t address, int value)
{
	HAL_FLASH_Unlock();
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_HALFWORD,  address, value);
	HAL_FLASH_Lock();
}

void Flash_Write_Float (uint32_t address, float f)
{
	HAL_FLASH_Unlock();
	uint8_t data[4];
	*(float*)data = f;
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_WORD,  address, *(uint32_t*)data); // 4 byte!
	HAL_FLASH_Lock();
}

void Flash_write_array (uint32_t address, uint8_t *arr, uint16_t length)
{
	HAL_FLASH_Unlock();
	uint16_t *pt = (uint16_t*)arr;
	for(uint16_t i=0 ; i<(length+1)/2 ; i++)
	{
		HAL_FLASH_Program (FLASH_TYPEPROGRAM_HALFWORD,  address + 2*i, *pt); // 2*i là do mỗi lần ghi 2 byte!
		pt++;
	}
	HAL_FLASH_Lock();
}

void Flash_write_struct (uint32_t address, wifi_info data)
{
	Flash_write_array(address, (uint8_t*)&data, sizeof(data));
}

int Flash_read_int (uint32_t address)
{
	return *(__IO uint16_t *)(address); //*(__IO uint16_t *) để ép kiểu và khai báo I/O tự động thay đổi được!
}

float Flash_Read_Float (uint32_t address)
{
	uint32_t data = *(__IO uint32_t*)(address);
	return *(float*)(&data);
}

void Flash_read_array (uint32_t address,uint8_t *arr, uint16_t length)
{
	uint16_t *pt = (uint16_t*) arr;
	for(uint16_t i=0 ; i<(length+1)/2 ; i++)
	{
		*pt = *(__IO uint16_t *) (address+2*i);
		pt++;
	}
}

void Flash_read_struct (uint32_t address, wifi_info *data)
{
	Flash_read_array(address, (uint8_t*)data, sizeof(wifi_info));
}

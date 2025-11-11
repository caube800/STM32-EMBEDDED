/*
 * FLASH.h
 *
 *  Created on: Oct 14, 2024
 *      Author: Admin
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_
#include<stdint.h>
#include<string.h>

#pragma pack(1); //tránh phân mảnh bộ nhớ
typedef struct
{
	uint8_t no;
	uint8_t ssid[30];
	uint8_t pass[30];
}  wifi_info;
#pragma pack()

//................Hàm xóa................//
void Flash_erase (uint32_t address);

//.................Hàm ghi...............//
void Flash_write_int (uint32_t address, int value);
void Flash_Write_Float (uint32_t address, float f);
void Flash_write_array (uint32_t address, uint8_t *arr, uint16_t length);
void Flash_write_struct (uint32_t address, wifi_info data);

//.................Hàm đọc...............//
int Flash_read_int (uint32_t address);
float Flash_Read_Float (uint32_t address);
void Flash_read_array (uint32_t address,uint8_t *arr, uint16_t length);
void Flash_read_struct (uint32_t address, wifi_info *data);

#endif /* INC_FLASH_H_ */

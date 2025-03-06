/*
 * STprintf.c
 *
 *  Created on: Mar 5, 2025
 *      Author: Mitsu
 */

#include <stdio.h>
#include "STprintf.h"

static UART_HandleTypeDef* Huart;

void STprintf(UART_HandleTypeDef* huart){
	setbuf(stdout,NULL);
	Huart = huart;
}

int _write(int file,char *ptr,int len){
	HAL_UART_Transmit(Huart, (uint8_t*)ptr, len, 10);
	return len;
}

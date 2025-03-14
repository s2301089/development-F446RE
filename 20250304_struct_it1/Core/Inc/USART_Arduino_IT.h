/*
 * USART_Arduino_IT.h
 *
 *  Created on: Mar 4, 2025
 *      Author: Mitsu
 */

#ifndef INC_USART_ARDUINO_IT_H_
#define INC_USART_ARDUINO_IT_H_

#include "main.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct{
	uint8_t LX;
	uint8_t LY;
	uint8_t L2;
	uint8_t RX;
	uint8_t RY;
	uint8_t R2;

	bool TRIANGLE;
	bool CIRCLE;
	bool CROSS;
	bool SQUARE;
	bool UP;
	bool RIGHT;
	bool DOWN;
	bool LEFT;
	bool L1;
	bool L3;
	bool R1;
	bool R3;
	bool SHARE;
	bool OPTION;
	bool PS;
	bool TOUCHPAD;
} getdata;

#define REV_SIZE 11
#define TIMEOUT_MAX 10

int getData(UART_HandleTypeDef* huart,getdata* revdata);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
int ChSUM(void);
void AddStruct(getdata* Udata);
void StructInit(getdata* Udata);
void AllShow(getdata Udata);
void AllShowP(getdata Udata);

#endif /* INC_USART_ARDUINO_IT_H_ */

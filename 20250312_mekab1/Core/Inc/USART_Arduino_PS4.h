/*
 * USART_Arduino_PS4.h
 *
 *  Created on: Mar 5, 2025
 *      Author: Mitsu
 */

#ifndef INC_USART_ARDUINO_PS4_H_
#define INC_USART_ARDUINO_PS4_H_

// Polling Includes

// IT Includes

// All Includes
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

// Polling Typedef

// IT Typedef

// All Typedef
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
	bool OPTIONS;
	bool PS;
	bool TOUCHPAD;
} getdata;

// Polling Def
#define WAIT 10

// IT Def

// All Def
#define REV_SIZE 11
#define TIMEOUT_MAX 10

// Polling Value

// IT Value
extern getdata data;
extern bool FAF;

// All Value

// Polling Prototype
int getData(UART_HandleTypeDef* huart,getdata* revdata);
uint8_t RevAF(UART_HandleTypeDef* huart);
void AddArray(UART_HandleTypeDef* huart,uint8_t* Adata);

// IT Prototype
void getDataIT(UART_HandleTypeDef* huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

// All Prototype
uint8_t ChSUM(uint8_t* Adata);
void AddStruct(getdata* Udata,uint8_t* Adata);
void StructInit(getdata* Udata);
void AllShow(getdata Udata);
void AllShowP(getdata Udata);

#endif /* INC_USART_ARDUINO_PS4_H_ */

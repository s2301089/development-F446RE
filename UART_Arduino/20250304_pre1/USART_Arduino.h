/*
 * USART_Arduino.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Mitsu
 */

/*
 * 説明
 * 使用するUSARTを.iocで選択してコードを生成。
 * main関数などでgetdata型の構造体変数を宣言。
 * getData関数にUARTのポインタと構造体変数のポインタを渡す。
 * getDataの戻り値が0であれば正常に構造体に格納されている。
 *
 * ※使用する関数によってprintfを使用できるようにする必要があるものもある。
 *
 * 使用例
 *
 * <USART1を使用しdataという名前の構造体変数を使用する場合>
 * getdata data;
 * if(getData(%huart1,&data) == 0){
 * 	AllShowP(data);
 * }
 *
 * ※AllShowP関数とAllShow関数を使用するためにはprintfを使用できるようにする必要がある。
 *
 * s2301089:2025/03/04
*/

#ifndef INC_USART_ARDUINO_H_
#define INC_USART_ARDUINO_H_

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

int getData(UART_HandleTypeDef* huart,getdata* revdata);
uint8_t RevAF(UART_HandleTypeDef* huart);
void AddArray(UART_HandleTypeDef* huart,uint8_t* Adata);
uint8_t ChSUM(uint8_t* Adata);
void AddStruct(getdata* Udata,uint8_t* Adata);
void StructInit(getdata* Udata);
void AllShow(getdata Udata);
void AllShowP(getdata Udata);


#define REV_SIZE 11
#define WAIT 10
#define TIMEOUT_MAX 10

#endif /* INC_USART_ARDUINO_H_ */

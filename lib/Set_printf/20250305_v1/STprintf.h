/*
 * STprintf.h
 *
 *  Created on: Mar 5, 2025
 *      Author: Mitsu
 */

#ifndef INC_STPRINTF_H_
#define INC_STPRINTF_H_

#include "main.h"

void STprintf(UART_HandleTypeDef* huart);
int _write(int file,char *ptr,int len);

#endif /* INC_STPRINTF_H_ */

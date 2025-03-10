/*
 * mekanamu.h
 *
 *  Created on: Mar 10, 2025
 *      Author: Mitsu
 */

#ifndef INC_MEKANAMU_H_
#define INC_MEKANAMU_H_

#include <stdint.h>

#define TOLE_VALUE 10

signed char halfX(uint8_t X);
signed char halfY(uint8_t Y);

void Move(uint8_t *Udata,uint8_t stX,uint8_t stY);

#endif /* INC_MEKANAMU_H_ */

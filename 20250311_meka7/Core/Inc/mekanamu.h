/*
 * mekanamu.h
 *
 *  Created on: Mar 10, 2025
 *      Author: Mitsu
 */

#ifndef INC_MEKANAMU_H_
#define INC_MEKANAMU_H_

#include <stdint.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define TOLE_VALUE 10
#define RAITO 0.7

signed char halfX(uint8_t X);
signed char halfY(uint8_t Y);

void MoveST(uint8_t *Udata,uint8_t stX,uint8_t stY,uint8_t stV);
double deg(double rad);
double rad(double deg);

#endif /* INC_MEKANAMU_H_ */

/*
 * STconhalf.h
 *
 *  Created on: Mar 10, 2025
 *      Author: Mitsu
 */

#include <STconhalf.h>

signed char halfX(uint8_t X){
	if(X > 0x7f - TOLE_VALUE && X < 0x7f + TOLE_VALUE){
		return 0;
	}else {
		if(X - 0x7f < -0x7f){
			return -0x7f;
		}else if(X - 0x7f > 0x7f){
			return 0x7f;
		}else {
			return X - 0x7f;
		}
	}
}

signed char halfY(uint8_t Y){
	if(Y > 0x7f - TOLE_VALUE && Y < 0x7f + TOLE_VALUE){
		return 0;
	}else {
		if(0x7f - Y < -0x7f){
			return -0x7f;
		}else if(0x7f - Y > 0x7f){
			return 0x7f;
		}else {
			return 0x7f - Y;
		}
	}
}

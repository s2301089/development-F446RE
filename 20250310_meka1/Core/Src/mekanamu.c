/*
 * mekanamu.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Mitsu
 */

#include <mekanamu.h>
#include <math.h>
#include <stdio.h>

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

void Move(uint8_t *Udata,uint8_t stX,uint8_t stY){ // Udata[0] 左上 Udata[1] 右上 Udata[2] 左下 Udata[3] 右下
#define PLUS 45
	signed char PosX;
	signed char PosY;
	double Z;
	double theta;
	double deg;
	double theta_plus;
	PosX = halfX(stX);
	PosY = halfY(stY);
	Z = sqrt(pow(PosX,2) + pow(PosY,2));
	theta = atan2(PosY,PosX);
	theta_plus = theta + (PLUS * M_PI) / 180;
	deg = (180 * theta) / M_PI;
//	printf("(%+4d,%+4d) %f∠%f %f\r\n",PosX,PosY,Z,deg,theta);
//	printf("%f %f %f %f\r\n",deg,theta + ((M_PI * PLUS) / 180),(180 * (theta + (M_PI * PLUS) / 180) / M_PI),theta_plus);
//	printf("%f %f \r\n",Z * cos(theta_plus),Z * sin(theta_plus));
	if(Z * sin(theta_plus) < 0){
		Udata[4] = 0x7f + Z * sin(theta_plus);
		Udata[0] = 1;
	}else{
		Udata[4] = Z * sin(theta_plus);
		Udata[0] = 0;
	}
	if(Z * cos(theta_plus) < 0){
		Udata[5] = 0x7f + Z * cos(theta_plus);
		Udata[1] = 1;
	}else {
		Udata[5] = Z * sin(theta_plus);
		Udata[1] = 0;
	}
	Udata[2] = Udata[1];
	Udata[3] = Udata[0];
	Udata[6] = Udata[5];
	Udata[7] = Udata[4];
	printf("左上 %d %2X 右上 %d %2X 左下 %d %2X 右下 %d %2X\r\n",Udata[0],Udata[4],Udata[1],Udata[5],Udata[2],Udata[6],Udata[3],Udata[7]);
}

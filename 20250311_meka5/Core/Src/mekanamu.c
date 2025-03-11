/*
 * mekanamu.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Mitsu
 */

#include <mekanamu.h>
#include <stdio.h>

// L / R , UP / DOWN , DIGITAL / PWM
enum {LUD,RUD,LDD,RDD,LUP,RUP,LDP,RDP};

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

void MoveST(uint8_t *Udata,uint8_t stX,uint8_t stY,uint8_t stV){ // Udata[0] 左上 Udata[1] 右上 Udata[2] 左下 Udata[3] 右下
#define PLUS 45
	signed char PosX;
	signed char PosY;
	double Adata[8] = {0};
	double Z;
	double theta;
	double theta_plus;
	double COS;
	double SIN;

	PosX = halfX(stX);
	PosY = halfY(stY);
	if(PosX == 0 && PosY == 0){
		COS = 0;
		SIN = 0;
	}else {
		Z = sqrt(pow(PosX,2) + pow(PosY,2));
		theta = atan((double)PosY / (double)PosX);
		if(PosX < 0){
			theta += M_PI;
		}
		if(theta < 0){
			theta += 2 * M_PI;
		}
		theta_plus = theta - rad(PLUS);
		COS = Z * cos(theta_plus);
		SIN = Z * sin(theta_plus);
	}

	Adata[LUP] = COS;
	Adata[RDP] = COS;
//	if(COS < 0){
//		Udata[LUP] = (uint8_t)(0x7f + COS);
//		Udata[LUD] = 1;
//	}else {
//		Udata[LUP] = (uint8_t)COS;
//		Udata[LUD] = 0;
//	}

	Adata[RUP] = SIN;
	Adata[LDP] = SIN;
//	if(SIN < 0){
//		Udata[RUP] = (uint8_t)(0x7f + SIN);
//		Udata[RUD] = 1;
//	}else{
//		Udata[RUP] = (uint8_t)SIN;
//		Udata[RUD] = 0;
//	}

//	Udata[LDD] = Udata[RUD];
//	Udata[RDD] = Udata[LUD];
//	Adata[RDP] = Adata[LUP];
//	Adata[LDP] = Adata[RUP];

	double Vroll;
	Vroll = (double)halfY(stV) * RAITO;
	if(Vroll < 0){ //left
		Adata[LUP] += Vroll;
		Adata[LDP] += Vroll;
		Adata[RUP] -= Vroll;
		Adata[RDP] -= Vroll;
		printf("left  ");
	}else{ // right
		Adata[LUP] += Vroll;
		Adata[LDP] += Vroll;
		Adata[RUP] -= Vroll;
		Adata[RDP] -= Vroll;
		printf("right ");
	}

	for(int i = 0;i < 4;i++){
		if(Adata[i+4] < 0){
			if(Adata[i+4] < -0x7f){
				Adata[i+4] = -0x7f;
			}
			Udata[i] = 1;
			Udata[i+4] = (uint8_t)(0x7f + Adata[i+4]) * 2;
			printf("nega ");
		}else{
			if(Adata[i+4] > 0x7f){
				Adata[i+4] = 0x7f;
			}
			Udata[i] = 0;
			Udata[i+4] = (uint8_t)Adata[i+4] * 2;
			printf("posi ");
		}
	}

//	printf("左上 %d %2X 右上 %d %2X 左下 %d %2X 右下 %d %2X %f\r\n",Udata[LUD],Udata[LUP],Udata[RUD],Udata[RUP],Udata[LDD],Udata[LDP],Udata[RDD],Udata[RDP],Vroll);
//	printf("左上 %d %+4f 右上 %d %+4f 左下 %d %+4f 右下 %d %+4f %f\r\n",Udata[LUD],Adata[LUP],Udata[RUD],Adata[RUP],Udata[LDD],Adata[LDP],Udata[RDD],Adata[RDP],Vroll);
//	printf("%f %f %f %f\r\n",COS,SIN,theta,deg(theta));
}


double deg(double rad){
	return (rad * 180) / M_PI;
}

double rad(double deg){
	return (deg * M_PI) / 180;
}

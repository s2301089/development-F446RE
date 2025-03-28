/*
 * USART_Arduino.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Mitsu
 */

#include "USART_Arduino.h"
#include <string.h>
#include <stdio.h>

static uint8_t timeout = 0;

int getData(UART_HandleTypeDef* huart,getdata* revdata){
	uint8_t Rdata[REV_SIZE] = {};
	if(RevAF(huart) == 0xaf){
		AddArray(huart,Rdata);
		if(ChSUM(Rdata) == 0xed){
//			printf("chsum ed ");
			AddStruct(revdata,Rdata);
			HAL_UART_Abort(huart);
			HAL_UART_DeInit(huart);
			HAL_UART_Init(huart);
			memset(Rdata,0x00,sizeof(Rdata));
			return 0;
		}
	}else{
		return -1;
	}

//	do{
//		if(RevAF(huart) == 0xaf){
//			AddArray(huart,Rdata);
//			if(ChSUM(Rdata) == 0xed){
//				AddStruct(revdata,Rdata);
////				HAL_UART_Abort(huart);
////				memset(Rdata,0x00,sizeof(Rdata));
//				return 0;
//			}
//		}
//	} while(timeout < TIMEOUT_MAX);
//	printf("timeout\r\n");
//	timeout = 0;
//	return -1;
}

uint8_t RevAF(UART_HandleTypeDef* huart){
	uint8_t Gdata;
	HAL_StatusTypeDef status;
	status = HAL_UART_Receive(huart, &Gdata, 1, WAIT);
	if(status == HAL_OK){
		if(Gdata == 0xaf){
			return Gdata;
		}else{
//			printf("not 0xaf %02x\r\n",Gdata);
			return 0x00;
		}
	}else {
		timeout++;
//		printf("else %2d %02x\r\n",timeout,Gdata);
		if(timeout >= TIMEOUT_MAX){
			printf("timeout ");
			timeout = 0;
		}
		return 0xff;
	}
}

void AddArray(UART_HandleTypeDef* huart,uint8_t* Adata){
	uint8_t Gdata;
	HAL_StatusTypeDef status;
	Adata[0] = 0xaf;

	for(int i = 1;i < REV_SIZE;i++){
		status = HAL_UART_Receive(huart, &Gdata, 1, WAIT);
		if(status == HAL_OK){
			Adata[i] = Gdata;
		}else {
			i--;
		}
	}
//	OutPut(Adata);

	return;
}

uint8_t ChSUM(uint8_t* Adata){
	if(Adata[10] == 0xed){
		uint8_t revsum = 0;
		for(int i = 1;i < (REV_SIZE - 2);i++){
			revsum += (int)Adata[i];
		}
		if(revsum == Adata[9]){
			return 0xed;
		}else {
//			printf("sum is not true\r\n");
			return 0x00;
		}
	}else {
//		printf("not end ");
		return 0xff;
	}
}

void AddStruct(getdata* Udata,uint8_t* Adata){
	StructInit(Udata);
	Udata->LX = Adata[1];
	Udata->LY = Adata[2];
	Udata->L2 = Adata[5];
	Udata->RX = Adata[3];
	Udata->RY = Adata[4];
	Udata->R2 = Adata[6];

	if(Adata[7] & 0x01)	Udata->TRIANGLE = 1;
	if(Adata[7] & 0x02)	Udata->CIRCLE 	= 1;
	if(Adata[7] & 0x04)	Udata->CROSS 	= 1;
	if(Adata[7] & 0x08)	Udata->SQUARE 	= 1;
	if(Adata[7] & 0x10)	Udata->UP 		= 1;
	if(Adata[7] & 0x20)	Udata->RIGHT 	= 1;
	if(Adata[7] & 0x40)	Udata->DOWN 	= 1;
	if(Adata[7] & 0x80)	Udata->LEFT		= 1;

	if(Adata[8] & 0x01)	Udata->L1 		= 1;
	if(Adata[8] & 0x02)	Udata->L3		= 1;
	if(Adata[8] & 0x04)	Udata->R1		= 1;
	if(Adata[8] & 0x08)	Udata->R3		= 1;
	if(Adata[8] & 0x10)	Udata->SHARE 	= 1;
	if(Adata[8] & 0x20)	Udata->OPTION 	= 1;
	if(Adata[8] & 0x40)	Udata->PS 		= 1;
	if(Adata[8] & 0x80)	Udata->TOUCHPAD = 1;

	return;
}

void StructInit(getdata* Udata){
	Udata->LX = 0x80;
	Udata->LY = 0x80;
	Udata->L2 = 0x00;
	Udata->RX = 0x80;
	Udata->RY = 0x80;
	Udata->R2 = 0x00;

	Udata->TRIANGLE = 0;
	Udata->CIRCLE = 0;
	Udata->CROSS = 0;
	Udata->SQUARE = 0;
	Udata->UP = 0;
	Udata->RIGHT = 0;
	Udata->DOWN = 0;
	Udata->LEFT = 0;
	Udata->L1 = 0;
	Udata->L3 = 0;
	Udata->R1 = 0;
	Udata->R3 = 0;
	Udata->SHARE = 0;
	Udata->OPTION = 0;
	Udata->PS = 0;
	Udata->TOUCHPAD = 0;

	return;
}

void OutPut(uint8_t* Adata){
	for(int i = 0;i < REV_SIZE;i++){
		printf("%2d %02x ",i,Adata[i]);
	}
}

void AllShow(getdata Udata){
	printf("LX:%3d "
			"LY:%3d "
			"L2:%3d "
			"RX:%3d "
			"RY:%3d "
			"R2:%3d "
			"TRIANGLE:%d "
			"CIRCLE:%d "
			"CROSS:%d "
			"SQUARE:%d "
			"UP:%d "
			"RIGHT:%d "
			"DOWN:%d "
			"LEFT:%d "
			"L1:%d "
			"L3:%d "
			"R1:%d "
			"R3:%d "
			"SHARE:%d "
			"OPTION:%d "
			"PS:%d "
			"TOUCHPAD:%d"
			"\r\n"
			,Udata.LX
			,Udata.LY
			,Udata.L2
			,Udata.RX
			,Udata.RY
			,Udata.R2
			,Udata.TRIANGLE
			,Udata.CIRCLE
			,Udata.CROSS
			,Udata.SQUARE
			,Udata.UP
			,Udata.RIGHT
			,Udata.DOWN
			,Udata.LEFT
			,Udata.L1
			,Udata.L3
			,Udata.R1
			,Udata.R3
			,Udata.SHARE
			,Udata.OPTION
			,Udata.PS
			,Udata.TOUCHPAD
			);
}

void AllShowP(getdata Udata){
	printf(
			"LX:%3d "
			"LY:%3d "
			"RX:%3d "
			"RY:%3d "
			"L2:%3d "
			"R2:%3d "
			"Pressed Button: "
			,Udata.LX
			,Udata.LY
			,Udata.RX
			,Udata.RY
			,Udata.L2
			,Udata.R2
			);

	if(Udata.TRIANGLE	== 1) printf("TRIANGLE ");
	if(Udata.CIRCLE		== 1) printf("CIRCLE ");
	if(Udata.CROSS		== 1) printf("CROSS ");
	if(Udata.SQUARE 	== 1) printf("SQUARE ");
	if(Udata.UP 		== 1) printf("UP ");
	if(Udata.RIGHT 		== 1) printf("RIGHT ");
	if(Udata.DOWN 		== 1) printf("DOWN ");
	if(Udata.LEFT 		== 1) printf("LEFT ");
	if(Udata.L1 		== 1) printf("L1 ");
	if(Udata.L3 		== 1) printf("L3 ");
	if(Udata.R1 		== 1) printf("R1 ");
	if(Udata.R3 		== 1) printf("R3 ");
	if(Udata.SHARE 		== 1) printf("SHARE ");
	if(Udata.OPTION 	== 1) printf("OPTION ");
	if(Udata.PS 		== 1) printf("PS ");
	if(Udata.TOUCHPAD 	== 1) printf("TOUOCHPAD ");

	printf("\r\n");
}

/*
 * USART_Arduino_IT.c
 *
 *  Created on: Mar 4, 2025
 *      Author: Mitsu
 */

#include "USART_Arduino_IT.h"
#include <stdio.h>

static uint8_t Adata[REV_SIZE] = {};
static uint8_t Gdata = 0;
static bool DF = 0;
bool AFF = 0;

int getData(UART_HandleTypeDef* huart,getdata* revdata){
//	printf("getData\r\n");
	HAL_UART_Receive_IT(huart, &Gdata, 1);
	if(DF == 1){
		AddStruct(revdata);
		DF = 0;
		return 0;
	}
//	printf("snct\r\n");
	return -1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	static int Gcount;
	static int timeout;
	if(Gdata == 0xaf){
		AFF = true;
		Gcount = 0;
	}else{
		timeout++;
		if(timeout >= TIMEOUT_MAX){
			timeout = 0;
		}
	}
	if(AFF == true){
		Adata[Gcount] = Gdata;
		Gcount++;
		if(Gcount == REV_SIZE){
			AFF = 0;
			if(ChSUM() == 0){
				DF = 1;
			}else{
				DF = 0;
			}
			Gcount = 0;
		}
	}
	HAL_UART_Receive_IT(huart, &Gdata, 1);
}

int ChSUM(void){
	if(Adata[10] = 0xed){
		uint8_t revsum = 0;
		for(int i = 1;i < REV_SIZE - 2;i++){
			revsum += Adata[i];
		}
		if(revsum == Adata[9]){
			return 0;
		}else{
			return -1;
		}
	}else {
		return 1;
	}
}

void AddStruct(getdata* Udata){
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

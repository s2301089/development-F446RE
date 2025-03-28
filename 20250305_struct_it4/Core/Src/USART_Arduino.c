/*
 * USART_Arduino.c
 *
 *  Created on: Mar 5, 2025
 *      Author: Mitsu
 */

// Polling Includes
#include <string.h>

// IT Includes

// All Includes
#include <stdio.h>
#include "USART_Arduino.h"

// Polling Value

// IT Value
static uint8_t AIdata[REV_SIZE] = {};
static uint8_t GIdata = 0x00;
static bool AFF = 0;
bool FAF = 0;
getdata data;

// All Value

// Polling Function
int getData(UART_HandleTypeDef* huart,getdata* revdata){
	uint8_t Rdata[REV_SIZE] = {};
	if(RevAF(huart) == 0xaf){
		AddArray(huart,Rdata);
		if(ChSUM(Rdata) == 0xed){
			AddStruct(revdata,Rdata);
			HAL_UART_Abort(huart);
			memset(Rdata,0x00,sizeof(Rdata));
		}
		return 0;
	}else{
		return -1;
	}
}

uint8_t RevAF(UART_HandleTypeDef* huart){
	static int timeout;
	uint8_t Gdata;
	HAL_StatusTypeDef status;
	status = HAL_UART_Receive(huart, &Gdata, 1, WAIT);
	if(status == HAL_OK){
		if(Gdata == 0xaf){
			return Gdata; // 0xaf
		}else {
			return 0x00;
		}
	}else {
		timeout++;
		if(timeout >= TIMEOUT_MAX){
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
	return;
}

// IT Function
int getDataIT(UART_HandleTypeDef* huart){
//	StructInit(&data);
//	FAF = 0;
	printf("getdata %d%d",FAF,AFF);
	HAL_UART_Receive_IT(huart, &GIdata, 1);
	return FAF;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
//	data.RE = 1;
	FAF = 1;
//	if(time(NULL) - st_time > TIMEOUT_MAX){
		printf("null time ");
//	}
	static int GIcount;
	static int Itimeout;
	if(GIdata == 0xaf){
		AFF = true;
		GIcount = 0;
	}else{
		printf(" not af ");
		AFF = false;
		Itimeout++;
		if(Itimeout >= TIMEOUT_MAX){
			Itimeout = 0;
		}
	}
	printf("%02x ",GIdata);
	if(AFF == true){
		AIdata[GIcount] = GIdata;
		GIcount++;
		if(GIcount == REV_SIZE){
			AFF = false;
			if(ChSUM(AIdata) == 0xed){
				printf("Add ");
				AddStruct(&data,AIdata);
			}else{
				printf("sum is not true");
			}
			GIcount = 0;
		}
	}
	HAL_UART_Receive_IT(huart, &GIdata, 1);
}

// All Function
uint8_t ChSUM(uint8_t* Adata){
	if(Adata[10] == 0xed){
		uint8_t revsum = 0;
		for(int i = 1;i < REV_SIZE - 2;i++){
			revsum += (int)Adata[i];
		}
		if(revsum == Adata[9]){
			return 0xed;
		}else{
			return 0x00;
		}
	}else{
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
	if(Adata[8] & 0x20)	Udata->OPTIONS 	= 1;
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
	Udata->OPTIONS = 0;
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
			"OPTIONS:%d "
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
			,Udata.OPTIONS
			,Udata.PS
			,Udata.TOUCHPAD
			);

	return;
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
	if(Udata.OPTIONS 	== 1) printf("OPTIONS ");
	if(Udata.PS 		== 1) printf("PS ");
	if(Udata.TOUCHPAD 	== 1) printf("TOUOCHPAD ");

	printf("\r\n");

	return;
}


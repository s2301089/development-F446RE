/*
 * manydef.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Mitsu
 */

/*
 * 説明
 * GPIOAをPAに
 * GPIO_PIN_0をP0に
 * GPIO_PIN_ALLをPallに
*/

#ifndef INC_MANYDEF_H_
#define INC_MANYDEF_H_

#define	P0		0x00000001
#define	P1		0x00000002
#define P2		0x00000004
#define P3		0x00000008

#define P4		0x00000010
#define P5		0x00000020
#define P6		0x00000040
#define P7		0x00000080

#define P8		0x00000100
#define P9		0x00000200
#define P10		0x00000400
#define P11		0x00000800

#define P12 	0x00001000
#define P13 	0x00002000
#define P14 	0x00004000
#define P15 	0x00008000

#define Pall	0x0000ffff

#define PA		GPIOA
#define PB		GPIOB
#define PC		GPIOC
#define PD		GPIOD
#define PE		GPIOE
#define PF		GPIOF
#define PG		GPIOG
#define PH		GPIOH

#endif /* INC_MANYDEF_H_ */

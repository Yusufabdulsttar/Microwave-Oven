/* 
 * File:   keyPad.h
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 14, 2023, 2:15 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* section : Includes   */
#include "gpio.h"
/* section : Micro Declaration  */
#define KEYPAD_ROW 4
#define KEYPAD_COL 4

/* section : Micro Function Declaration  */

/* section : Data Type Declaration  */
typedef enum {
    LOW = 0,
    HIGH
}logic_t;

typedef struct {
	uint32_t port ;          /* &ref port_index_t */
	uint32_t pin ;           /* &ref pin_index_t */
}pin_t;

typedef struct {
	pin_t keypad_row [KEYPAD_ROW];
	pin_t keypad_col [KEYPAD_COL];
}keypad_t;

/* section : Function Declaration  */
void keypad_initialize (const keypad_t *keypad);
void keypad_read (const keypad_t *keypad , uint8_t *key);

#endif	/* KEYPAD_H */


/* 
 * File:   app.h
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 11, 2023, 2:12 PM
 */

#ifndef APP_H
#define	APP_H

/* section : Includes   */

#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/DC_MOTOR/ecu_motor.h"
#include "ECU_Layer/Keypad/keypad.h"
#include "ECU_Layer/LCD/Ecu_LCD.h"
#include "ECU_Layer/BUSH_BUTTON/ecu_button.h"
#include "MCAL_Layer/Timers/Timer0/mcal_timer0.h"
#include "MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/* section : Micro Declaration  */

#define PASS_LIMIT       3
#define SET              1 
#define CLEAR            0 
#define CANCEL           2 

/* section : Micro Function Declaration  */

/* section : Data Type Declaration  */

led_t led_Heater;
led_t led_Lamp;
dc_motor_t DC_Motor;
keypad_t keypad;
lcd_4bit_t lcd;
button_t Food_button;
button_t Door_button;
button_t Start_button;
button_t Stop_button;
timer0_t Timer;

uint8 Door = CLEAR;
uint8 Food_in = CLEAR;
uint8 Start = CLEAR;
uint8 Start_Flag = CLEAR;
uint8 Stop  = CLEAR;
uint8 Pause_Flage  = CLEAR;
uint8 Cancel_Flage = CLEAR;
uint8 Time_minutes = CLEAR;
uint8 Time_seconds = 60;
uint8 keypad_value = CLEAR;
uint8 Time_check = CLEAR;
uint8 Run_flag = CLEAR;
uint8 count_char = CLEAR;
uint8 char_temp = CLEAR;


/* section : Function Declaration  */

void initialization ();
uint8 Keypad_Read_Value();
void Button_State();
void Set_Time();
void Timer_ISR();
void Start_Microwave();
void Stop_Microwave();

#endif	/* APP_H */


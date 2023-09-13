/*
 * File:   app.c
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 11, 2023, 2:12 PM
 */

#include "app.h"

int main() {
    /* For initialization Drivers like (LED - KEYPAD - LCD - DC_Motor - Timer - Bush Button) */
    initialization (); 
    /* First message */
    lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");  
	while(1)
	{
        Button_State();
        /* Check if door is closed */
        if (Door == HIGH){
           led_on(&led_Lamp);
        }
        if (Door == LOW && Start_Flag == CLEAR){
          led_off(&led_Lamp);
        }
        /* Check if food is in microwave and door is closed */
		if(Food_in == HIGH && Door == LOW)
		{
			/* We want to set time only once */
			Set_Time();
            
            /* Check the state of the start button */
			if(Start_Flag == SET && Pause_Flage == CLEAR)
			{
                /* Turn on the microwave, heater, and lamb */
				Start_Microwave();
                Cancel_Flage = CLEAR;
			}
		}

        /* Check the state of the Stop button */
		if(Pause_Flage == SET)
		{
            Start_Flag = CLEAR;
            Pause_Flage = CLEAR;
            Stop_Microwave(); // stope the operation 
		}
        /* if the stop button is pressed twice, restart the program  */
        if (Cancel_Flage == CANCEL){
            Stop_Microwave();
            lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");
            Pause_Flage = CLEAR;
            Start_Flag = CLEAR;
            Time_minutes = CLEAR;
            Time_seconds = 60;
            Cancel_Flage = CLEAR;
            Time_check = CLEAR;
        }
	}
    return 0;
}

/**
 * @brief To check the condition of a push button
 * @param void
 * @return void 
 */
void Button_State(){
    /* Check if there is food in the microwave */
    button_status (&Food_button,&Food_in);
    /* Check the status of the door */
    button_status (&Door_button,&Door);
    button_status (&Start_button,&Start);
    /* Check the status of the Start */
    if (Start == BUTTON_PUSHED){
        Start_Flag = SET;
    }
    /* Check the status of the Stop */
    button_status (&Stop_button,&Stop);
    if(Stop == BUTTON_PUSHED){

        Pause_Flage++;
        Cancel_Flage++;
    }
}

/**
 * @brief To Set the time from (0 to 99)
 * @param void
 * @return void 
 */
void Set_Time(){
    if(Time_check != 2){
    /* get input key from keypad */
    keypad_value = Keypad_Read_Value();
    /* check if the input is correct */
        if(('0' <= keypad_value) && ('9' >= keypad_value))
        {
            if (keypad_value != 0){
            /* Store the time */
            Time_minutes = (Time_minutes * 10) + (keypad_value - '0');
			
            /* display time*/
            if (Time_minutes <= 9){
                char_temp = keypad_value;
                lcd_4bit_send_char_data_pos(&lcd, 2, 9, char_temp);    
            }
            else if(Time_minutes >= 10){
                lcd_4bit_send_char_data_pos(&lcd, 2, 9, keypad_value);
                lcd_4bit_send_char_data_pos(&lcd, 2, 8, char_temp);
            }
            ++Time_check;
            keypad_value = 0;
            }
        }
    }
}

/**
 * @brief Configure the timer to interrupt every 1 sec
 * @param void
 * @return void 
 */
void Timer_ISR(){
/* If the Run_flag is 1, then the user has pressed the start button and there is food in the microwave */
    
    if(Run_flag){
        /* if (Time_minutes) valid then start count the time and display it*/
        
        if(Time_minutes){
            Time_seconds--;
            /* display the minutes */
            count_char = '0' + ((Time_minutes-1) / 10);    
            lcd_4bit_send_char_data_pos(&lcd, 2, 8, count_char);
            count_char = '0' + ((Time_minutes-1) % 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 9, count_char);

            /* display the seconds */
            count_char = '0' + (Time_seconds / 10);    
            lcd_4bit_send_char_data_pos(&lcd, 2, 11, count_char);
            count_char = '0' + (Time_seconds % 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 12, count_char);      
            
            /* A minute has passed if the seconds are 0 */
            if (Time_seconds == 0){
                Time_minutes--;
                Time_seconds = 60;
            }  
        }
        /* If the minute is 0, then the time is up */
        else {
            lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");   
            Start_Flag = CLEAR;
            Stop_Microwave();
        }
    }
}

/**
 * @brief This function starts the microwave, lamp, and heater
 * @param void
 * @return void 
 */
void Start_Microwave(){
    /* start the heater */
    led_on(&led_Heater);
    /* Turn on the lamb  */
    led_on(&led_Lamp);
    /* Start the microwave  */
    dc_motor_forward(&DC_Motor); 
    /* Start the timer */
    Run_flag = 1;	
}

/**
 * @brief This function stops the microwave, lamp, and heater
 * @param void
 * @return void 
 */
void Stop_Microwave(){
    /* Stop the heater */
    led_off(&led_Heater);
    /* Turn off the lamb  */
    led_off(&led_Lamp);
    /* Stop the microwave  */
    dc_motor_off(&DC_Motor);
    /* Stop the timer */
    Run_flag = 0;   
}

/**
 * @brief This function reads the keypad
 * @param void
 * @return Keypad Value 
 */
uint8 Keypad_Read_Value()
{
    uint8 Value;
    keypad_read(&keypad, &Value);
    return Value;  
}

/**
 * @brief This function initializes the modules
 * @param void
 * @return void
 */
void initialization (){

led_Heater.port_name = PORTE_INDEX, led_Heater.pin = PIN0, led_Heater.led_status = LOW;
led_Lamp.port_name = PORTE_INDEX, led_Lamp.pin = PIN1, led_Lamp.led_status = LOW;


    Food_button.button_conec = BUTTON_ACTIVE_HIGH;
    Food_button.button_state = BUTTON_RELEASE;
    Food_button.pin_b.direction = dirc_INPUT;
    Food_button.pin_b.logic = LOW;
    Food_button.pin_b.port = PORTB_INDEX;
    Food_button.pin_b.pin = PIN3;
 
    Door_button.button_conec = BUTTON_ACTIVE_HIGH;
    Door_button.button_state = BUTTON_RELEASE;
    Door_button.pin_b.direction = dirc_INPUT;
    Door_button.pin_b.logic = LOW;
    Door_button.pin_b.port = PORTB_INDEX;
    Door_button.pin_b.pin = PIN2;
    
    Stop_button.button_conec = BUTTON_ACTIVE_HIGH;
    Stop_button.button_state = BUTTON_RELEASE;
    Stop_button.pin_b.direction = dirc_INPUT;
    Stop_button.pin_b.logic = LOW;
    Stop_button.pin_b.port = PORTB_INDEX;
    Stop_button.pin_b.pin = PIN1;
    
    Start_button.button_conec = BUTTON_ACTIVE_HIGH;
    Start_button.button_state = BUTTON_RELEASE;
    Start_button.pin_b.direction = dirc_INPUT;
    Start_button.pin_b.logic = LOW;
    Start_button.pin_b.port = PORTB_INDEX;
    Start_button.pin_b.pin = PIN0;

    
    DC_Motor.dc_motor_pin[0].port = PORTA_INDEX,
    DC_Motor.dc_motor_pin[0].pin = PIN0,
    DC_Motor.dc_motor_pin[0].direction = dirc_OUTPUT,
    DC_Motor.dc_motor_pin[0].logic = LOW,
    DC_Motor.dc_motor_pin[1].port = PORTA_INDEX,
    DC_Motor.dc_motor_pin[1].pin = PIN1,
    DC_Motor.dc_motor_pin[1].direction = dirc_OUTPUT,
    DC_Motor.dc_motor_pin[1].logic = LOW;


    keypad.keypad_row[0].port = PORTC_INDEX,
    keypad.keypad_row[0].pin = PIN0,
    keypad.keypad_row[0].direction = dirc_OUTPUT,
    keypad.keypad_row[0].logic = LOW,
    keypad.keypad_row[1].port = PORTC_INDEX,
    keypad.keypad_row[1].pin = PIN1,
    keypad.keypad_row[1].direction = dirc_OUTPUT,
    keypad.keypad_row[1].logic = LOW,
    keypad.keypad_row[2].port = PORTC_INDEX,
    keypad.keypad_row[2].pin = PIN2,
    keypad.keypad_row[2].direction = dirc_OUTPUT,
    keypad.keypad_row[2].logic = LOW,
    keypad.keypad_row[3].port = PORTC_INDEX,
    keypad.keypad_row[3].pin = PIN3,
    keypad.keypad_row[3].direction = dirc_OUTPUT,
    keypad.keypad_row[3].logic = LOW,
    
    keypad.keypad_col[0].port = PORTC_INDEX,
    keypad.keypad_col[0].pin = PIN4,
    keypad.keypad_col[0].direction = dirc_INPUT,
    keypad.keypad_col[0].logic = LOW,
    keypad.keypad_col[1].port = PORTC_INDEX,
    keypad.keypad_col[1].pin = PIN5,
    keypad.keypad_col[1].direction = dirc_INPUT,
    keypad.keypad_col[1].logic = LOW,
    keypad.keypad_col[2].port = PORTC_INDEX,
    keypad.keypad_col[2].pin = PIN6,
    keypad.keypad_col[2].direction = dirc_INPUT,
    keypad.keypad_col[2].logic = LOW;
    keypad.keypad_col[3].port = PORTC_INDEX,
    keypad.keypad_col[3].pin = PIN7,
    keypad.keypad_col[3].direction = dirc_INPUT,
    keypad.keypad_col[3].logic = LOW;


    lcd.lcd_rs.port = PORTD_INDEX,
    lcd.lcd_rs.pin = PIN0,
    lcd.lcd_rs.direction = dirc_OUTPUT,
    lcd.lcd_rs.logic = LOW,
    lcd.lcd_en.port = PORTD_INDEX,
    lcd.lcd_en.pin = PIN1,
    lcd.lcd_en.direction = dirc_OUTPUT,
    lcd.lcd_en.logic = LOW,
    
    lcd.lcd_data[0].port = PORTD_INDEX,
    lcd.lcd_data[0].pin = PIN2,
    lcd.lcd_data[0].direction = dirc_OUTPUT,
    lcd.lcd_data[0].logic = LOW,
    lcd.lcd_data[1].port = PORTD_INDEX,
    lcd.lcd_data[1].pin = PIN3,
    lcd.lcd_data[1].direction = dirc_OUTPUT,
    lcd.lcd_data[1].logic = LOW,
    lcd.lcd_data[2].port = PORTD_INDEX,
    lcd.lcd_data[2].pin = PIN4,
    lcd.lcd_data[2].direction = dirc_OUTPUT,
    lcd.lcd_data[2].logic = LOW,
    lcd.lcd_data[3].port = PORTD_INDEX,
    lcd.lcd_data[3].pin = PIN5,
    lcd.lcd_data[3].direction = dirc_OUTPUT,
    lcd.lcd_data[3].logic = LOW;
    
    
    Timer.timer_register_mode = REGISTER_16BIT;
    Timer.timer_mode = TIMER_MODE;
    Timer.timer_edge = RISE_EDGE;
    Timer.prescaler_enable = PRESCALER_ENABLE;
    Timer.prescale_value = PRESCALER_32;
    Timer.preload_value = 3036;
    Timer.EXT_INTERRUPT = Timer_ISR;
            
    
    led_initialize(&led_Heater);
    led_initialize(&led_Lamp);
 
    button_initialize (&Food_button);
    button_initialize (&Door_button);
    button_initialize (&Stop_button);
    button_initialize (&Start_button);

    dc_motor_initialize(&DC_Motor);
    
    keypad_initialize(&keypad);
    
    lcd_4bit_intialize(&lcd);
    
    timer0_init(&Timer);
}   

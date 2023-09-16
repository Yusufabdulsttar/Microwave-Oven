/* 
 * File:   LCD.c
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 14, 2023, 2:12 PM
 */
#include <LCD.h>

static void lcd_send_4bits(const lcd_4bit_t *lcd, uint8_t _data_command);
static void lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd);
static void lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t coulmn);

/**
 * 
 * @param lcd
 * @return
 */
void lcd_4bit_intialize(const lcd_4bit_t *lcd){


        HAL_Delay(20);
        lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2_LINE);
        HAL_Delay(5);
        lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2_LINE);
        HAL_Delay(5);
        lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2_LINE);

        lcd_4bit_send_command(lcd, LCD_CLEAR);
        lcd_4bit_send_command(lcd, LCD_RETURN_HOME);
        lcd_4bit_send_command(lcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_4bit_send_command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_4bit_send_command(lcd, LCD_4BIT_MODE_2_LINE);
        lcd_4bit_send_command(lcd, 0x80);

}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command){

        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
		HAL_GPIO_WritePin((lcd->lcd_rs.port), (lcd->lcd_rs.pin), GPIO_PIN_RESET);
        /* Send the Command through the (4-Pins" Data lines */
        lcd_send_4bits(lcd, command >> 4);
        /* Send the Enable Signal on the "E" Pin */
        lcd_4bit_send_enable_signal(lcd);
        /* Send the Command through the (4-Pins" Data lines */
        lcd_send_4bits(lcd, command);
        /* Send the Enable Signal on the "E" Pin */
        lcd_4bit_send_enable_signal(lcd);
}

/**
 * 
 * @param lcd Pointer to the LCD configurations
 * @param data The data that we need to send to the LCD
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8_t data){
  
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
		HAL_GPIO_WritePin((lcd->lcd_rs.port), (lcd->lcd_rs.pin), GPIO_PIN_SET);
        /* Send the Data through the (4-Pins" Data lines */
        lcd_send_4bits(lcd, data >> 4);
        /* Send the Enable Signal on the "E" Pin */
        lcd_4bit_send_enable_signal(lcd);
        /* Send the Data through the (4-Pins" Data lines */
        lcd_send_4bits(lcd, data);
        /* Send the Enable Signal on the "E" Pin */
        lcd_4bit_send_enable_signal(lcd);

}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd,uint8_t row, uint8_t column, uint8_t data){

        lcd_4bit_set_cursor(lcd, row, column);
        lcd_4bit_send_char_data(lcd, data);

}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8_t *str){

        while(*str){
            lcd_4bit_send_char_data(lcd, *str++);
		}

}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
void lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8_t row, uint8_t column, uint8_t *str){

        lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            lcd_4bit_send_char_data(lcd, *str++);
        }

}

/**
 * 
 * @param lcd
 * @param _data_command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static void lcd_send_4bits(const lcd_4bit_t *lcd, uint8_t _data_command){
	
	HAL_GPIO_WritePin((lcd->lcd_data[0].port), (lcd->lcd_data[0].pin), ((_data_command >> 0) & (uint8_t)0x01));
	HAL_GPIO_WritePin((lcd->lcd_data[1].port), (lcd->lcd_data[1].pin), ((_data_command >> 1) & (uint8_t)0x01));
	HAL_GPIO_WritePin((lcd->lcd_data[2].port), (lcd->lcd_data[2].pin), ((_data_command >> 2) & (uint8_t)0x01));
	HAL_GPIO_WritePin((lcd->lcd_data[3].port), (lcd->lcd_data[3].pin), ((_data_command >> 3) & (uint8_t)0x01));
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static void lcd_4bit_send_enable_signal(const lcd_4bit_t *lcd){
	HAL_GPIO_WritePin((lcd->lcd_en.port), (lcd->lcd_en.pin), GPIO_PIN_SET);
    HAL_Delay(5);
	HAL_GPIO_WritePin((lcd->lcd_en.port), (lcd->lcd_en.pin), GPIO_PIN_RESET);

}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static void lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8_t row, uint8_t coulmn){
    coulmn--;
    switch(row){
        case ROW1 : lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
        case ROW2 : lcd_4bit_send_command(lcd, (0xc0 + coulmn)); break;
        case ROW3 : lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
        case ROW4 : lcd_4bit_send_command(lcd, (0xd4 + coulmn)); break;
        default : ;
    }
}

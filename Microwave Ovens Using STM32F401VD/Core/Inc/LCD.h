/* 
 * File:   LCD.h
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 14, 2023, 2:16 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* ----------------- Includes -----------------*/
#include "gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define LCD_CLEAR                      0X01
#define LCD_RETURN_HOME                0x02
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define LCD_DISPLAY_SHIFT_LEFT         0x18
#define LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define LCD_8BIT_MODE_2_LINE           0x38
#define LCD_4BIT_MODE_2_LINE           0x28

#define LCD_CGRAM_START                0x40
#define LCD_DDRAM_START                0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct {
	uint32_t port ;          /* &ref port_index_t */
	uint32_t pin ;           /* &ref pin_index_t */
}pin_config_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4bit_t;


/* ----------------- Software Interfaces Declarations -----------------*/
void lcd_4bit_intialize(const lcd_4bit_t *lcd);
void lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8_t command);
void lcd_4bit_send_char_data(const lcd_4bit_t *lcd, uint8_t data);
void lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd,uint8_t row, uint8_t column, uint8_t data);
void lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8_t *str);
void lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8_t row, uint8_t column, uint8_t *str);



#endif	/* ECU_LCD_H */


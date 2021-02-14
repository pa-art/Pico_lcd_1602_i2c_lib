/**
 * Header file for lcd_1602_i2c_lib, I2C LCD driver;
 *      Feb.14, 2021    Pa@ART
 */

#ifndef __LCD_1602_I2C_LIB__

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

// Modes for lcd_send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES      2
#define MAX_CHARS      16

void i2c_write_byte(uint8_t );
void lcd_toggle_enable(uint8_t );
void lcd_send_byte(uint8_t , int );
void lcd_clear(void);
void lcd_set_cursor(int , int );
void lcd_string(const char *);
void lcd_init(void);

#define __LCD_1602_I2C_LIB__
#endif
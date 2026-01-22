#ifndef _30010_IO_H_
#define _30010_IO_H_

/* Includes ------------------------------------------------------------------*/
#include "bsp/stm32f30x_conf.h"
#include <stdio.h>
#include <stdlib.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define UART_BUFFER_LENGTH 256

/* Exported functions ------------------------------------------------------- */
/****************************/
/*** USB Serial Functions ***/
/****************************/
void uart_init(uint32_t baud);
void uart_put_char(uint8_t c);
uint8_t uart_get_char();
uint8_t uart_get_count();
void uart_clear();

/*****************************/
/*** LCD Control Functions ***/
/*****************************/
void lcd_init();
void lcd_transmit_byte(uint8_t data);
void lcd_push_buffer();
void lcd_reset();

#endif /* _30010_IO_H_ */
